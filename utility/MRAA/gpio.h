/**
 * @file spi.h
 * @author TMRh20 2015
 * Class declaration for GPIO helper files
 */
#ifndef RF24_UTILITY_MRAA_GPIO_H_
#define RF24_UTILITY_MRAA_GPIO_H_

#include <cstdio>
#include <stdio.h>
#include "mraa.hpp"

class GPIO
{

public:
    GPIO();

    virtual ~GPIO();

    void begin(uint8_t ce_pin, uint8_t cs_pin);

    void open(int port, int DDR);

    void close(int port);

    int read(int port);

    void write(int port, int value);

private:
    int gpio_ce_pin; /** ce_pin value of the RF24 device **/
    // int gpio_cs_pin;    /** cs_pin value of the RF24 device **/
    mraa::Gpio* gpio_0; /** gpio object for ce_pin **/
    // mraa::Gpio* gpio_1; /** gpio object for cs_pin **/
};

#endif // RF24_UTILITY_MRAA_GPIO_H_
