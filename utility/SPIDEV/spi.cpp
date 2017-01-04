/*
 * File:   spi.cpp
 * Author: Purinda Gunasekara <purinda@gmail.com>
 *
 * Created on 24 June 2012, 11:00 AM
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

#define RF24_SPIDEV_BITS 8

SPI::SPI():fd(-1) {
}

void SPI::begin(int busNo){

    /* set spidev accordingly to busNo like:
     * busNo = 23 -> /dev/spidev2.3
     *
     * a bit messy but simple
     * */
	char device[] = "/dev/spidev0.0";
	device[11] += (busNo / 10) % 10;
	device[13] += busNo % 10;

    if (this->fd < 0)  // check whether spi is already open
    {
	  this->fd = open(device, O_RDWR);

      if (this->fd < 0)
      {
        perror("can't open device");
        abort();
      }
    }

	init();
}

void SPI::init()
{
	uint8_t bits = RF24_SPIDEV_BITS;
	uint32_t speed = RF24_SPIDEV_SPEED;
	uint8_t mode = 0;

	int ret;
	/*
	 * spi mode
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();
	}

	ret = ioctl(this->fd, SPI_IOC_RD_MODE, &mode);
	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();
	}

	/*
	 * bits per word
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		perror("can't set bits per word");
		abort();
	}

	ret = ioctl(this->fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		perror("can't set bits per word");
		abort();
	}
	/*
	 * max speed hz
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		perror("can't set max speed hz");
		abort();
	}

	ret = ioctl(this->fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		perror("can't set max speed hz");
		abort();
	}
}

uint8_t SPI::transfer(uint8_t tx)
{
	struct spi_ioc_transfer tr;
	memset(&tr, 0, sizeof(tr));
	tr.tx_buf = (unsigned long)&tx;
	uint8_t rx;
	tr.rx_buf = (unsigned long)&rx;
	tr.len = sizeof(tx);
	tr.speed_hz = RF24_SPIDEV_SPEED;
	tr.delay_usecs = 0;
	tr.bits_per_word = RF24_SPIDEV_BITS;
	tr.cs_change = 0;

	int ret;
	ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		perror("can't send spi message");
		abort();
	}

	return rx;
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len)
{
    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf = (unsigned long)tbuf;
    tr.rx_buf = (unsigned long)rbuf;
    tr.len = len;
    tr.speed_hz = RF24_SPIDEV_SPEED;
    tr.delay_usecs = 0;
    tr.bits_per_word = RF24_SPIDEV_BITS;
    tr.cs_change = 0;

	int ret;
	ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		perror("can't send spi message");
		abort();
	}
}

SPI::~SPI() {
	if (!(this->fd < 0))
		close(this->fd);
}
