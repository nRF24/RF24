/**
 * @file spi.cpp
 * @author Purinda Gunasekara <purinda@gmail.com>
 *
 * Created on 24 June 2012, 11:00 AM
 *
 * Patched for exception handling and selectable SPI SPEED by ldiaz 2018.
 *
 * Inspired from spidev test in linux kernel documentation
 * www.kernel.org/doc/Documentation/spi/spidev_test.c
 */

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "spi.h"

#define RF24_SPIDEV_BITS 8

SPI::SPI()
    : fd(-1), _spi_speed(RF24_SPI_SPEED)
{
}

void SPI::begin(int busNo, uint32_t spi_speed)
{

    if (this->spiIsInitialized) {
        return;
    }

    /* set spidev accordingly to busNo like:
     * busNo = 23 -> /dev/spidev2.3
     *
     * a bit messy but simple
     * */
    char device[] = "/dev/spidev0.0";
    device[11] += (busNo / 10) % 10;
    device[13] += busNo % 10;

    if (this->fd >= 0) // check whether spi is already open
    {
        close(this->fd);
        this->fd = -1;
    }

    this->fd = open(device, O_RDWR);
    if (this->fd < 0) {
        std::string msg = "[SPI::begin] Can't open device ";
        msg += device;
        msg += "; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    this->spiIsInitialized = true;
    init(spi_speed);
}

void SPI::init(uint32_t speed)
{
    uint8_t bits = RF24_SPIDEV_BITS;
    uint8_t mode = 0;

    int ret;
    /*
     * spi mode
     */
    ret = ioctl(this->fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1) {
        std::string msg = "[SPI::init] Can't set WR spi mode; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    ret = ioctl(this->fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1) {
        std::string msg = "[SPI::init] Can't set RD spi mode; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    /*
     * bits per word
     */
    ret = ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1) {
        std::string msg = "[SPI::init] Can't set WR bits per word; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    ret = ioctl(this->fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1) {
        std::string msg = "[SPI::init] Can't set RD bits per word; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    /*
     * max speed hz
     */
    ret = ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        std::string msg = "[SPI::init] Can't set max WR speed hz; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    ret = ioctl(this->fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        std::string msg = "[SPI::init] Can't set max RD speed hz; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    _spi_speed = speed;
}

uint8_t SPI::transfer(uint8_t tx)
{
    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf = (unsigned long)&tx;
    uint8_t rx;
    tr.rx_buf = (unsigned long)&rx;
    tr.len = sizeof(tx);
    tr.speed_hz = _spi_speed; //RF24_SPI_SPEED;
    tr.delay_usecs = 0;
    tr.bits_per_word = RF24_SPIDEV_BITS;
    tr.cs_change = 0;

    int ret;
    ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1) {
        std::string msg = "[SPI::transfer] Can't send spi message; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }

    return rx;
}

void SPI::transfernb(char* txBuf, char* rxBuf, uint32_t len)
{
    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf = (unsigned long)txBuf;
    tr.rx_buf = (unsigned long)rxBuf;
    tr.len = len;
    tr.speed_hz = _spi_speed; //RF24_SPI_SPEED;
    tr.delay_usecs = 0;
    tr.bits_per_word = RF24_SPIDEV_BITS;
    tr.cs_change = 0;

    int ret;
    ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 1) {
        std::string msg = "[SPI::transfernb] Can't send spi message; ";
        msg += strerror(errno);
        throw SPIException(msg);
    }
}

void SPI::transfern(char* buf, uint32_t len)
{
    transfernb(buf, buf, len);
}

SPI::~SPI()
{
    if (this->fd >= 0) {
        close(this->fd);
    }
}
