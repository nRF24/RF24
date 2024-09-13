/*
 * TMRh20 2015
 * SPI layer for RF24 <-> BCM2835
 */
/**
 * @file spi.h
 * Class declaration for SPI helper files
 */
#ifndef RF24_UTILITY_RPI_SPI_H_
#define RF24_UTILITY_RPI_SPI_H_

#include <stdio.h>
#include "bcm2835.h"
#include "../../RF24_config.h"

#define SPI_HAS_TRANSACTION
#define MSBFIRST  BCM2835_SPI_BIT_ORDER_MSBFIRST
#define SPI_MODE0 BCM2835_SPI_MODE0
//#define RF24_SPI_SPEED 10000000 //BCM2835_SPI_SPEED_4MHZ

class SPISettings
{
public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    {
        init(clock, bitOrder, dataMode);
    }

    SPISettings()
    {
        init(RF24_SPI_SPEED, MSBFIRST, SPI_MODE0);
    }

    uint32_t clock;
    uint8_t border;
    uint8_t dataMode;

private:
    void init(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    {
        clock = clock;
        border = bitOrder;
        dataMode = dataMode;
    }

    friend class SPIClass;
};

class SPI
{
public:
    SPI();

    virtual ~SPI();

    inline static uint8_t transfer(uint8_t _data);

    inline static void transfernb(char* txBuf, char* rxBuf, uint32_t len);

    inline static void transfern(char* buf, uint32_t len);

    static void begin(int busNo, uint32_t spi_speed = RF24_SPI_SPEED);

    static void end();

    static void setBitOrder(uint8_t bit_order);

    static void setDataMode(uint8_t data_mode);

    static void setClockDivider(uint32_t spi_speed);

    static void chipSelect(int csn_pin);

    static void beginTransaction(SPISettings settings);

    static void endTransaction();
};

uint8_t SPI::transfer(uint8_t _data)
{
    uint8_t data = bcm2835_spi_transfer(_data);
    return data;
}

void SPI::transfernb(char* txBuf, char* rxBuf, uint32_t len)
{
    bcm2835_spi_transfernb(txBuf, rxBuf, len);
}

void SPI::transfern(char* buf, uint32_t len)
{
    transfernb(buf, buf, len);
}

#endif // RF24_UTILITY_RPI_SPI_H_
