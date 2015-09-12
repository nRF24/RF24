/*
 * TMRh20 2015
 * SPI layer for RF24 <-> BCM2835
 */
/**
 * @file spi.h
 * \cond HIDDEN_SYMBOLS
 * Class declaration for SPI helper files
 */
#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdio.h>
#include "bcm2835.h"

class SPI {
public:

  SPI();
  virtual ~SPI();
  
  inline static uint8_t transfer(uint8_t _data);
  inline static void transfernb(char* tbuf, char* rbuf, uint32_t len);
  inline static void transfern(char* buf, uint32_t len);  

  static void begin(int busNo);
  static void end();

  static void setBitOrder(uint8_t bit_order);
  static void setDataMode(uint8_t data_mode);
  static void setClockDivider(uint16_t spi_speed);
  static void chipSelect(int csn_pin);
};


uint8_t SPI::transfer(uint8_t _data) {
	return bcm2835_spi_transfer(_data);
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len){
   bcm2835_spi_transfernb( tbuf, rbuf, len);
}

void SPI::transfern(char* buf, uint32_t len)
{
    transfernb(buf, buf, len);
}
/**
 * \endcond
 */
#endif
