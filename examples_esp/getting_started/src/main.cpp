#include <RF24.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <driver/spi_master.h>

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

extern "C" void app_main(void)
{
    SPIClass spi;
    spi.begin(SPI2_HOST);
    printf("SPI bus configured\n");
    printf("using CE_PIN pin %d!\n", CE_PIN);
    printf("using CSN_pin pin %d!\n", CSN_PIN);

    bool ok = radio.begin(&spi);
    printf("finished attempt to init radio\n");
    if (!ok) {
        printf("radio hardware not responding!\n");
    } else {
        printf("Success!! radio is ready to configure.\n");
    }

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
