

#include "spi.h"

SPI::SPI() {

}


void SPI::begin( int busNo ) {
	
	if (!bcm2835_init()){
		return;
	}
	
	bcm2835_spi_begin();
	
}

void SPI::end() {

}

void SPI::setBitOrder(uint8_t bit_order) {
	bcm2835_spi_setBitOrder(bit_order);
}

void SPI::setDataMode(uint8_t data_mode) {
  bcm2835_spi_setDataMode(data_mode);
}

void SPI::setClockDivider(uint16_t spi_speed) {
	bcm2835_spi_setClockDivider(spi_speed);
}

void SPI::chipSelect(int csn_pin){
	bcm2835_spi_chipSelect(csn_pin);
}

SPI::~SPI() {

}