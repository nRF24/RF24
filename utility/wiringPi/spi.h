/**
 * @file spi.h
 * Class declaration for SPI helper files
 */

#ifndef RF24_UTILITY_WIRINGPI_SPI_H_
#define RF24_UTILITY_WIRINGPI_SPI_H_

#include <stdio.h>
#include <inttypes.h>

#include "../../RF24_config.h" // This is cyclical and should be fixed

using namespace std;

class SPI
{

public:
    SPI();

    void begin(int csn_pin, uint32_t spi_speed = RF24_SPI_SPEED);

    uint8_t transfer(uint8_t);

    void transfernb(char*, char*, uint32_t);

    void transfern(char*, const uint32_t);

    virtual ~SPI();

private:
    int fd;
    uint8_t msg[32 + 1];
    uint8_t msgByte;
};

#endif // RF24_UTILITY_WIRINGPI_SPI_H_
