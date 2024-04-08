/**
 * @file gpio.h
 * Class declaration for SPI helper files
 *
 * see also https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html#gpio-summary
 */
#ifndef RF24_UTILITY_ESP_IDF_GPIO_H_
#define RF24_UTILITY_ESP_IDF_GPIO_H_

#include <stdint.h> // uintXX_t
#include "driver/gpio.h"

typedef uint8_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFF

class GPIO
{

public:
    static const gpio_mode_t DIRECTION_OUT = GPIO_MODE_OUTPUT;
    static const gpio_mode_t DIRECTION_IN = GPIO_MODE_INPUT;

    static const int OUTPUT_HIGH = 1;
    static const int OUTPUT_LOW = 0;

    GPIO();

    static void open(rf24_gpio_pin_t port, gpio_mode_t direction);

    static void close(rf24_gpio_pin_t port);

    static int read(rf24_gpio_pin_t port);

    static void write(rf24_gpio_pin_t port, int value);

    virtual ~GPIO();
};

#endif // RF24_UTILITY_ESP_IDF_GPIO_H_
