#include <RF24.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <driver/spi_master.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RF24_CE_PIN
    #define CE_PIN RF24_CE_PIN
#else
    #define CE_PIN 7
#endif

#ifdef RF24_CSN_PIN
    #define CSN_PIN RF24_CSN_PIN
#else
    #define CSN_PIN 8
#endif

RF24 radio = RF24(CE_PIN, CSN_PIN);

static const char* TAG = "RF24/examples_esp/getting_started";

spi_bus_config_t busConfig;

void app_main(void)
{
#ifdef RF24_DEFAULT_MOSI
    printf("using MOSI pin %d!\n", RF24_DEFAULT_MOSI);
    busConfig.mosi_io_num = RF24_DEFAULT_MOSI;
#else
    busConfig.mosi_io_num = -1; // GPIO13 on SPI2_HOST; GPIO23 on SPI3_HOST
#endif
#ifdef RF24_DEFAULT_MISO
    printf("using MISO pin %d!\n", RF24_DEFAULT_MISO);
    busConfig.miso_io_num = RF24_DEFAULT_MISO;
#else
    busConfig.miso_io_num = -1; // GPIO12 on SPI2_HOST; GPIO19 on SPI3_HOST
#endif
#ifdef RF24_DEFAULT_SCLK
    printf("using SCLK pin %d!\n", RF24_DEFAULT_SCLK);
    busConfig.sclk_io_num = RF24_DEFAULT_SCLK;
#else
    busConfig.sclk_io_num = -1; // GPIO14 on SPI2_HOST; GPIO18 on SPI3_HOST
#endif
    busConfig.quadwp_io_num = -1;
    busConfig.quadhd_io_num = -1;
    busConfig.data4_io_num = -1;
    busConfig.data5_io_num = -1;
    busConfig.data6_io_num = -1;
    busConfig.data7_io_num = -1;
    // busConfig.max_transfer_sz = 33; // RF24 lib only buffers 33 bytes for SPI transactions
    // busConfig.flags = 0;
    // busConfig.isr_cpu_id = ESP_INTR_CPU_AFFINITY_AUTO;
    // busConfig.intr_flags = 0;

    SPIClass spi;
    spi.begin(SPI2_HOST, /* RF24_SPI_SPEED */ 4000000, SPI_MODE1, &busConfig);
    printf("SPI bus configured\n");
    printf("using CE_PIN pin %d!\n", CE_PIN);
    printf("using CSN_pin pin %d!\n", CSN_PIN);
    spi.beginTransaction();
    uint8_t config_reg = spi.transfer(0);
    spi.endTransaction();
    printf("CONFIG register (before): %02x\n", config_reg);

    bool ok = radio.begin(&spi);
    printf("finished attempt to init radio\n");
    if (!ok) {
        printf("radio hardware not responding!\n");
    } else {
        printf("Success!! radio is ready to configure.\n");
    }

    spi.beginTransaction();
    config_reg = spi.transfer(0);
    spi.endTransaction();
    printf("CONFIG register (after): %02x\n", config_reg);

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

#ifdef __cplusplus
}
#endif
