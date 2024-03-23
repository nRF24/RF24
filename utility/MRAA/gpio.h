/**
 * @file gpio.h
 * @author TMRh20 2015
 * Class declaration for GPIO helper files
 */
#ifndef RF24_UTILITY_MRAA_GPIO_H_
#define RF24_UTILITY_MRAA_GPIO_H_

#include <stdexcept> // std::runtime_error, std::string
#include "mraa.hpp"

typedef uint16_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFFFF

/** Specific exception for GPIO errors */
class GPIOException : public std::runtime_error
{
public:
    explicit GPIOException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

class GPIO
{

public:
    GPIO();

    virtual ~GPIO();

    static void open(rf24_gpio_pin_t port, mraa::Dir DDR);

    static void close(rf24_gpio_pin_t port);

    static int read(rf24_gpio_pin_t port);

    static void write(rf24_gpio_pin_t port, int value);
};

#endif // RF24_UTILITY_MRAA_GPIO_H_
