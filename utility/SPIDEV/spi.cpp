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

#include <memory.h>
#include <pthread.h>
static pthread_mutex_t spiMutex;

SPI::SPI():fd(-1) {
}

void SPI::begin(int busNo){

	this->device = "/dev/spidev0.0";
    /* set spidev accordingly to busNo like:
     * busNo = 23 -> /dev/spidev2.3
     *
     * a bit messy but simple
     * */
    this->device[11] += (busNo / 10) % 10;
    this->device[13] += busNo % 10;
	this->bits = 8;
	this->speed = RF24_SPIDEV_SPEED;
	this->mode=0;
    //this->mode |= SPI_NO_CS;
	this->init();
}

void SPI::init()
{
	int ret;
    
    if (this->fd < 0)  // check whether spi is already open
    {
	  this->fd = open(this->device.c_str(), O_RDWR);

      if (this->fd < 0)
      {
        perror("can't open device");
        abort();
      }
    }

	/*
	 * spi mode
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_MODE, &this->mode);
	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();		
	}

	ret = ioctl(this->fd, SPI_IOC_RD_MODE, &this->mode);
	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();				
	}
	
	/*
	 * bits per word
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &this->bits);
	if (ret == -1)
	{
		perror("can't set bits per word");
		abort();				
	}

	ret = ioctl(this->fd, SPI_IOC_RD_BITS_PER_WORD, &this->bits);
	if (ret == -1)
	{
		perror("can't set bits per word");
		abort();						
	}
	/*
	 * max speed hz
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed);
	if (ret == -1)
	{
		perror("can't set max speed hz");
		abort();						
	}

	ret = ioctl(this->fd, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed);
	if (ret == -1)
	{
		perror("can't set max speed hz");
		abort();						
	}
}

uint8_t SPI::transfer(uint8_t tx)
{
    pthread_mutex_lock (&spiMutex);

    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf = (unsigned long)&tx;
    tr.rx_buf = (unsigned long)&tx;
    tr.len = sizeof(tx);
    tr.speed_hz = this->speed;
    tr.delay_usecs = 0;
    tr.bits_per_word = this->bits;
    tr.cs_change = 0;

	int ret;
	ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
        pthread_mutex_unlock (&spiMutex);
		perror("can't send spi message");
		abort();		
	}

    pthread_mutex_unlock (&spiMutex);
	return tx;
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len)
{
	pthread_mutex_lock (&spiMutex);

    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf = (unsigned long)tbuf;
    tr.rx_buf = (unsigned long)rbuf;
    tr.len = len;
    tr.speed_hz = this->speed;
    tr.delay_usecs = 0;
    tr.bits_per_word = this->bits;
    tr.cs_change = 0;

	int ret;
	ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
        pthread_mutex_unlock (&spiMutex);
		perror("can't send spi message");
		abort();		
	}
    pthread_mutex_unlock (&spiMutex);
}

void SPI::transfern(char* buf, uint32_t len)
{
    transfernb(buf, buf, len);
}


SPI::~SPI() {
    if (!(this->fd < 0))
	    close(this->fd);
}

