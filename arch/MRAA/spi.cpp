

#include "spi.h"

SPI::SPI() {
	mspi = NULL;
}


void SPI::begin(void) {

	mspi = new mraa::Spi(0);

	mspi->mode(mraa::SPI_MODE0);
	mspi->bitPerWord(8);
	mspi->frequency(4000000);
}

// Prophet: this is only a suggestion, but can be useful for devices with multiple SPI ports
void SPI::begin(int bus, int frequency) {
	mspi = new mraa::Spi(bus);

	mspi->mode(mraa::SPI_MODE0);
	mspi->bitPerWord(8);
	mspi->frequency(frequency);
}

void SPI::end() {
	// Prophet: we should check for existence of mspi before deleting it
	if (mspi != NULL)
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
	// Prophet: we should call end here to free used memory and unexport SPI interface
	this->end();
}
