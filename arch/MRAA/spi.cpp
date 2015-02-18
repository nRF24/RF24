

#include "spi.h"

SPI::SPI() {

}


void SPI::begin( ) {	

	mspi = new mraa::Spi(0);

	mspi->mode(mraa::SPI_MODE0);
	mspi->bitPerWord(8);
	mspi->frequency(8000000);
}

void SPI::end() {
	delete mspi;
}

void SPI::setBitOrder(uint8_t bit_order) {
	mspi->bitPerWord(bit_order);
}

void SPI::setDataMode(uint8_t data_mode) {
	mspi->mode((mraa::Spi_Mode)data_mode);
}

void SPI::setClockDivider(uint32_t spi_speed) {
	mspi->frequency(spi_speed);
}

void SPI::chipSelect(int csn_pin){

}

SPI::~SPI() {

}