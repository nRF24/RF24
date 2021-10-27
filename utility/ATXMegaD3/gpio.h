/**
 * @file gpio.h
 * Class declaration for SPI helper files
 */
#ifndef RF24_UTILITY_ATXMEGAD3_GPIO_H_
#define RF24_UTILITY_ATXMEGAD3_GPIO_H_

#include <avr/io.h>
#include "gpio_helper.h"

class GPIO
{

public:
    static const int DIRECTION_OUT = 1;
    static const int DIRECTION_IN = 0;

    static const int OUTPUT_HIGH = 1;
    static const int OUTPUT_LOW = 0;

    GPIO();

    static void open(int port, int DDR);

    static void close(int port);

    static int read(int port);

    static void write(int port, int value);

    virtual ~GPIO();
};

#endif // RF24_UTILITY_ATXMEGAD3_GPIO_H_
