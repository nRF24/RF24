/**
 * https://github.com/mrshu/GPIOlib
 * Copyright (c) 2011, Copyright (c) 2011 mr.Shu
 * All rights reserved.
 *
 * Modified on 24 June 2012, 11:06 AM
 * @file gpio.h
 * Author: purinda (purinda@gmail.com)
 *
 * Class declaration for GPIO helper files
 */

#ifndef RF24_UTILITY_SPIDEV_GPIO_H_
#define RF24_UTILITY_SPIDEV_GPIO_H_

#include <cstdio>
#include <map>
#include <stdexcept>
#include <cstdint>

typedef uint16_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFFFF

/** Specific exception for SPI errors */
class GPIOException : public std::runtime_error
{
public:
    explicit GPIOException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

typedef int GPIOfdCache_t;

class GPIO
{

public:
    static const int DIRECTION_OUT = 1;
    static const int DIRECTION_IN = 0;

    static const int OUTPUT_HIGH = 1;
    static const int OUTPUT_LOW = 0;

    GPIO();

    static void open(rf24_gpio_pin_t port, int DDR);

    static void close(rf24_gpio_pin_t port);

    static int read(rf24_gpio_pin_t port);

    static void write(rf24_gpio_pin_t port, int value);

    virtual ~GPIO();

private:
};

#endif // RF24_UTILITY_SPIDEV_GPIO_H_
