#include <RF24.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "tusb_console.h"
#include "sdkconfig.h"

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

void setupSerialUSB(); // See definition below

void app_main(void)
{
    setupSerialUSB();

    SPIClass spi;
    spi.begin();
    fprintf(stdout, "SPI bus configured\n");

    // if (!radio.begin(&spi)) {
    //     while (true) {
    //         fprintf(stdout, "radio hardware not responding!\n");
    //     }
    // }
    while (true) {
        fprintf(stdout, "radio is ready to configure.\n");
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
