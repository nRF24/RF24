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
    spiHandle = spiOpen(busNo, spi_speed, 0);
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

