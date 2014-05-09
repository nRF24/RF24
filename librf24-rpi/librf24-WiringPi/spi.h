/* 
 * File:   spi.h
 * Author: Purinda Gunasekara <purinda@gmail.com>
 * 
 * Created on 24 June 2012, 11:00 AM
 */

#ifndef SPI_H
#define	SPI_H

#include <string>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <inttypes.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class SPI {
public:
	
	SPI();
	uint8_t transfer(uint8_t tx_);
	virtual ~SPI();
	void init();	
	void setdevice( string devicefile );
	void setbits( uint8_t bits );
	void setspeed( uint32_t speed );

private:

	// Default SPI device
	string device;
	// SPI Mode set 
	uint8_t mode;
	// word size
	uint8_t bits;
	// Set SPI speed
	uint32_t speed;
	int fd;

};

#endif	/* SPI_H */

