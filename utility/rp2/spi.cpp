#include "spi.h"

SPI::SPI()
{
}

void SPI::begin(spi_inst_t* hw_id)
{
    begin(hw_id, PICO_DEFAULT_SPI_SCK_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_RX_PIN);
}

void SPI::begin(spi_inst_t* hw_id, uint8_t _sck, uint8_t _tx, uint8_t _rx)
{
    _hw_id = hw_id;
    gpio_set_function(_sck, GPIO_FUNC_SPI);
    gpio_set_function(_tx, GPIO_FUNC_SPI);
    gpio_set_function(_rx, GPIO_FUNC_SPI);
}

uint8_t SPI::transfer(uint8_t tx_)
{
    uint8_t recv = 0;
    spi_write_read_blocking(_hw_id, &tx_, &recv, 1);
    return recv;
}

void SPI::transfernb(const uint8_t* txBuf, uint8_t* rxBuf, uint32_t len)
{
    spi_write_read_blocking(_hw_id, txBuf, rxBuf, len);
}

void SPI::transfern(const uint8_t* buf, uint32_t len)
{
    spi_write_blocking(_hw_id, buf, len);
}

void SPI::beginTransaction(uint32_t _spi_speed)
{
    spi_init(_hw_id, _spi_speed);
    spi_set_format(_hw_id, RF24_SPI_BYTE_SIZE, RF24_SPI_CPOL, RF24_SPI_CPHA, RF24_SPI_ENDIAN);
}

void SPI::endTransaction()
{
    spi_deinit(_hw_id);
}

SPI::~SPI()
{
}
