/*
 * TMRh20 2015
 * SPI layer for RF24
 */

#ifndef RF24_UTILITY_MRAA_SPI_H_
#define RF24_UTILITY_MRAA_SPI_H_
/**
 * @file spi.h
 * Class declaration for SPI helper files
 */

#include <stdio.h>
#include "mraa.h"
#include "mraa.hpp"

#include "../../RF24_config.h" // This is cyclical and should be fixed

class SPI
{
public:
    SPI();

    virtual ~SPI();

    mraa::Spi* mspi;

    inline uint8_t transfer(uint8_t _data);

    inline void transfernb(char* tbuf, char* rbuf, uint32_t len);

    inline void transfern(char* buf, uint32_t len);

    void begin(int busNo, uint32_t spi_speed = RF24_SPI_SPEED);

    void end();

    void setBitOrder(uint8_t bit_order);

    void setDataMode(uint8_t data_mode);

    void setClockDivider(uint32_t spi_speed);

    void chipSelect(int csn_pin);
};

uint8_t SPI::transfer(uint8_t _data)
{
    return mspi->writeByte(_data);
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len)
{
    mspi->transfer((uint8_t*)tbuf, (uint8_t*)rbuf, len);
}

void SPI::transfern(char* buf, uint32_t len)
{
    transfernb(buf, buf, len);
}

#endif // RF24_UTILITY_MRAA_SPI_H_
