/*
 * File:   spi.cpp
 * Author:
 *
 * Created on
 *
 * Inspired from spi speed test from wiringPi
 * wiringPi/examples/spiSpeed.c
 */

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "spi.h"

SPI::SPI() : fd(-1), channel(0)
{
}

void SPI::begin(int csn_pin, uint32_t spi_speed)
{
    channel = csn_pin % 10;

    // initialize the wiringPiSPI
    wiringPiSetup();
    if ((this->fd = wiringPiSPISetup(channel, spi_speed)) < 0) {
        std::string msg = "[SPI::begin] Cannot configure the SPI device!; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }
}

uint8_t SPI::transfer(uint8_t tx)
{
    memset(&xferByte, 0, sizeof(xferByte));
    memcpy(&xferByte, &tx, sizeof(tx));

    if (wiringPiSPIDataRW(channel, &xferByte, sizeof(tx)) < 0) {
        std::string msg = "[SPI::transfer] Cannot send spi message; ";
        msg += strerror(errno);
        throw SPIException(msg);
        return 0;
    }

    return xferByte;
}

void SPI::transfern(char* buf, uint32_t len)
{
    if (wiringPiSPIDataRW(channel, (uint8_t*)buf, len) < 0) {
        std::string msg = "[SPI::transfern] Cannot send spi message; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }
}

void SPI::transfernb(char* txBuf, char* rxBuf, uint32_t len)
{
    // using an auxiliary buffer to keep tx and rx different
    memset(xferBuf, 0, sizeof(xferBuf));
    memcpy(xferBuf, txBuf, len);

    if (wiringPiSPIDataRW(channel, xferBuf, len) < 0) {
        std::string msg = "[SPI::transfernb] Cannot send spi message; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    memcpy(rxBuf, xferBuf, len);
}

SPI::~SPI()
{
    if (this->fd >= 0) {
        close(this->fd);
        this->fd = -1;
    }
}
