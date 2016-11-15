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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "bcm2835.h"
#include "interrupt.h"

#define SPI_HAS_TRANSACTION
#define MSBFIRST BCM2835_SPI_BIT_ORDER_MSBFIRST
#define SPI_MODE0 BCM2835_SPI_MODE0
#define RF24_SPI_SPEED BCM2835_SPI_SPEED_8MHZ


typedef struct  {
    uint32_t clck;
    uint8_t border;
    uint8_t dmode;
}SPISettings;



SPISettings*
SPI_Settings(SPISettings * st, uint32_t clock, uint8_t bitOrder, uint8_t dataMode);

SPISettings*
SPI_Settings_default(SPISettings * st) ;

  uint8_t SPI_transfer(uint8_t _data);
  void SPI_transfernb(char* tbuf, char* rbuf, uint32_t len);
  void SPI_transfern(char* buf, uint32_t len);  

  void SPI_begin(int busNo);
  void SPI_end();

  void SPI_setBitOrder(uint8_t bit_order);
  void SPI_setDataMode(uint8_t data_mode);
  void SPI_setClockDivider(uint16_t spi_speed);
  void SPI_chipSelect(int csn_pin);
  
  void SPI_beginTransaction(SPISettings settings);
  void SPI_endTransaction();
  
  


uint8_t SPI_transfer(uint8_t _data);

void SPI_transfernb(char* tbuf, char* rbuf, uint32_t len);

void SPI_transfern(char* buf, uint32_t len);

#ifdef __cplusplus
}
#endif 

#endif
