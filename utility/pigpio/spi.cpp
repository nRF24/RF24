/*
 *
 */

#include "spi.h"
#include <pigpio.h>

SPI::SPI()
{
}

void SPI::begin(int busNo, uint32_t spi_speed)
{
    if (this->spiIsInitialized) {
        return;
    }
    spiIsInitialized = true;
    gpioInitialise();
    spiHandle = spiOpen((unsigned int)(busNo & 2), spi_speed, (unsigned int)((busNo / 10) << 7));
}

void SPI::init(uint32_t speed)
{
}

uint8_t SPI::transfer(char tx)
{
    char rbuf = 0;
    spiXfer(spiHandle, &tx, &rbuf, 1);
    return rbuf;
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len)
{
    spiXfer(spiHandle, tbuf, rbuf, len);
}

SPI::~SPI()
{
}
