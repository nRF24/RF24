#include <RF24.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "tusb_console.h"
#include "sdkconfig.h"
#include <driver/spi_master.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_RF24_CE_PIN
    #define CE_PIN CONFIG_RF24_CE_PIN
#else
    #define CE_PIN 7
#endif

#ifdef CONFIG_RF24_CSN_PIN
    #define CSN_PIN CONFIG_RF24_CSN_PIN
#else
    #define CSN_PIN 8
#endif

RF24 radio = RF24(CE_PIN, CSN_PIN);

static const char* TAG = "RF24/examples_esp/getting_started";

spi_bus_config_t busConfig;

void setupSerialUSB(); // See definition below

void app_main(void)
{
    setupSerialUSB();

#ifdef CONFIG_RF24_DEFAULT_MOSI
    fprintf(stdout, "using MOSI pin %d!\n", CONFIG_RF24_DEFAULT_MOSI);
    busConfig.mosi_io_num = CONFIG_RF24_DEFAULT_MOSI;
#else
    busConfig.mosi_io_num = -1; // GPIO13 on SPI2_HOST; GPIO23 on SPI3_HOST
#endif
    busConfig.data0_io_num = -1;
#ifdef CONFIG_RF24_DEFAULT_MISO
    fprintf(stdout, "using MISO pin %d!\n", CONFIG_RF24_DEFAULT_MISO);
    busConfig.miso_io_num = CONFIG_RF24_DEFAULT_MISO;
#else
    busConfig.miso_io_num = -1; // GPIO12 on SPI2_HOST; GPIO19 on SPI3_HOST
#endif
    busConfig.data1_io_num = -1;
#ifdef CONFIG_RF24_DEFAULT_SCLK
    fprintf(stdout, "using SCLK pin %d!\n", CONFIG_RF24_DEFAULT_SCLK);
    busConfig.sclk_io_num = CONFIG_RF24_DEFAULT_SCLK;
#else
    busConfig.sclk_io_num = -1; // GPIO14 on SPI2_HOST; GPIO18 on SPI3_HOST
#endif
    busConfig.quadwp_io_num = -1;
    busConfig.data2_io_num = -1;
    busConfig.quadhd_io_num = -1;
    busConfig.data3_io_num = -1;
    busConfig.data4_io_num = -1;
    busConfig.data5_io_num = -1;
    busConfig.data6_io_num = -1;
    busConfig.data7_io_num = -1;
    busConfig.max_transfer_sz = 33; // RF24 lib only buffers 33 bytes for SPI transactions
    busConfig.flags = 0;
    busConfig.isr_cpu_id = ESP_INTR_CPU_AFFINITY_AUTO;
    busConfig.intr_flags = 0;

    SPIClass spi;
    spi.begin(SPI2_HOST, RF24_SPI_SPEED, SPI_MODE1, &busConfig);
    fprintf(stdout, "SPI bus configured\n");

    bool ok = radio.begin(&spi);
    fprintf(stdout, "finished attempt o init radio");
    if (!ok) {
        fprintf(stdout, "radio hardware not responding!\n");
    } else {
        fprintf(stdout, "Success!! radio is ready to configure.\n");
    }

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/** Setup TinyUSB for CDC serial communication */
void setupSerialUSB()
{
    ESP_LOGI(TAG, "USB initialization");
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL, // Use the default device descriptor specified in Menuconfig
        .string_descriptor = NULL, // Use the default string descriptors specified in Menuconfig
        .string_descriptor_count = 0,
        .external_phy = false, // Use internal USB PHY (in most cases)
#if (TUD_OPT_HIGH_SPEED)
        .fs_configuration_descriptor = NULL, // Use the default full-speed configuration descriptor according to settings in Menuconfig
        .hs_configuration_descriptor = NULL, // Use the default high-speed configuration descriptor according to settings in Menuconfig
        .qualifier_descriptor = NULL,        // Use the default qualifier descriptor, with values from default device descriptor
#else
        .configuration_descriptor = NULL, // Use the default configuration descriptor according to settings in Menuconfig
#endif // TUD_OPT_HIGH_SPEED
        .self_powered = false,
        .vbus_monitor_io = 0,
    };
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    const tinyusb_config_cdcacm_t acm_cfg = {
        .usb_dev = TINYUSB_USBDEV_0,
        .cdc_port = TINYUSB_CDC_ACM_0,
        .rx_unread_buf_sz = 64,
        .callback_rx = NULL,
        .callback_rx_wanted_char = NULL,
        .callback_line_state_changed = NULL,
        .callback_line_coding_changed = NULL};
    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));

    ESP_LOGI(TAG, "USB initialization DONE");
    esp_tusb_init_console(TINYUSB_CDC_ACM_0); // log to usb

    // the delay here isn't needed, but any `abort()` called immediately after this function would
    // prevent the OS from seeing the USB port enumerated as a CDC Serial device
    vTaskDelay(1000 / portTICK_PERIOD_MS); // remove this when lib is working properly
}

#ifdef __cplusplus
}
#endif
