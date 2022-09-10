#include "spi.h"

RF24_SPI::RF24_SPI() : _hspi(nullptr)
{
}

void RF24_SPI::begin()
{
    HAL_SPI_Init(_hspi);
}

void RF24_SPI::begin(SPI_HandleTypeDef* hspi)
{
    _hspi = hspi;
    RF24_SPI::begin();
}

uint8_t RF24_SPI::transfer(uint8_t data_to_send)
{
    uint8_t rx_data;
    HAL_SPI_TransmitReceive(_hspi, &data_to_send, &rx_data, 1, HAL_MAX_DELAY);
    return rx_data;
}
