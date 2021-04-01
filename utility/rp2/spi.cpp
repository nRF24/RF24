#include "spi.h"

SPI::SPI()
{
    printf("PicoRF24: SPI::SPI\n");
}

void SPI::begin()
{
    printf("PicoRF24: SPI::begin\n");
    spi_init(spi0, 250000);
    gpio_set_function(2, GPIO_FUNC_SPI);
    gpio_set_function(3, GPIO_FUNC_SPI);
    gpio_set_function(4, GPIO_FUNC_SPI);
}

uint8_t SPI::transfer(uint8_t tx_) {
    printf("PicoRF24: SPI::transfer(uint8_t tx_: %d)\n", tx_);
    uint8_t recv = 0;
    spi_write_read_blocking(spi0, &tx_, &recv, 1);
    printf("PicoRF24: SPI::transfer(uint8_t tx_) READ: %d\n", recv);
    return recv;
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len) {
    printf("PicoRF24: SPI::transfernb(char* tbuf, char* rbuf, uint32_t len: %ld)\n", len);
    spi_write_read_blocking(spi0, (const uint8_t*)tbuf, (uint8_t*)rbuf, len);
}

void SPI::transfern(char* buf, uint32_t len) {
    printf("PicoRF24: SPI::transfern(char* buf, uint32_t len: %ld)\n", len);
    spi_write_blocking(spi0, (const uint8_t*)buf, len);
}


SPI::~SPI()
{
    printf("PicoRF24: SPI::~SPI\n");
}
