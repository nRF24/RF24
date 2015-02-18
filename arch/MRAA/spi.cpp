

#include "spi.h"
#include "mraa.h"

SPI::SPI() {
	mspi = NULL;
}


void SPI::begin(void) {
	// Prophet: this is only a suggestion, but can update begin with SPI bus number for devices with multiple SPI ports,
	// and then #define _SPI_BUS_NUMBER in config, so for non MRAA platforms it will state as SPI.beign(),
	// while for MRAA ones it will go SPI.begin(0) or any other valid bus number

	mspi = new mraa::Spi(0);

	mspi->mode(mraa::SPI_MODE0);
	mspi->bitPerWord(8);
	mspi->frequency(8000000); // Prophet: this will try to set 8MHz, however MRAA will reset to max platform speed and syslog a message of it
}

void SPI::end() {
	// Prophet: we should check for existence of mspi before deleting it
	if (mspi != NULL)
		delete mspi;
}

void SPI::setBitOrder(uint8_t bit_order) {
	if (mspi != NULL)
		mspi->lsbmode((mraa_boolean_t)bit_order); // Prophet: bit_order
}

void SPI::setDataMode(uint8_t data_mode) {
	if (mspi != NULL)
		mspi->mode((mraa::Spi_Mode)data_mode);
}

void SPI::setClockDivider(uint32_t spi_speed) {
	if (mspi != NULL)
		mspi->frequency(spi_speed);
}

void SPI::chipSelect(int csn_pin){

}

SPI::~SPI() {
	// Prophet: we should call end here to free used memory and unexport SPI interface
	this->end();
}
