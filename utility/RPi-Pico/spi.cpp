#include "spi.h"
#include <unistd.h>

SPI::SPI()
{
    printf("PicoRF24: SPI::SPI\n");
}

void SPI::begin()
{
    printf("PicoRF24: SPI::begin\n");
}

uint8_t SPI::transfer(uint8_t tx_) {
    printf("PicoRF24: SPI::transfer(uint8_t tx_: %d)\n", tx_);
}

void SPI::transfernb(char* tbuf, char* rbuf, uint32_t len) {
    printf("PicoRF24: SPI::transfernb(char* tbuf, char* rbuf, uint32_t len: %d)\n", len);
}

void SPI::transfern(char* buf, uint32_t len) {
    printf("PicoRF24: SPI::transfern(char* buf, uint32_t len: %d)\n", len);
}


SPI::~SPI()
{
    printf("PicoRF24: SPI::~SPI\n");
}
