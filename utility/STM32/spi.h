/**
 * @file spi.h
 * Class declaration for SPI helper files
 */

#ifndef RF24_UTILITY_STM32_SPI_H_
#define RF24_UTILITY_STM32_SPI_H_

#include <stdint.h>
#include "includes.h"

class RF24_SPI
{
public:
    RF24_SPI();
    void begin();
    void begin(SPI_HandleTypeDef* hspi);
    uint8_t transfer(uint8_t data_to_send);

private:
    SPI_HandleTypeDef* _hspi;
};

#define _SPI RF24_SPI
#define RF24_SPI_PTR

static RF24_SPI spi;

#endif // RF24_UTILITY_STM32_SPI_H_
