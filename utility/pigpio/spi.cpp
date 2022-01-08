/*
 * File:   spi.cpp
 * Author: Purinda Gunasekara <purinda@gmail.com>
 *
 * Created on 24 June 2012, 11:00 AM
 *
 * Patched for exception handling and selectable SPI SPEED by ldiaz 2018.
 *
 * Inspired from spidev test in linux kernel documentation
 * www.kernel.org/doc/Documentation/spi/spidev_test.c
 */

#include "spi.h"

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pigpio.h>

#define RF24_SPIDEV_BITS 8

SPI::SPI()
        :_spi_speed(RF24_SPI_SPEED)
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

