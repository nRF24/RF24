

#include "spi.h"

SPI::SPI() {

}


void SPI::begin( int busNo ) {
	rfNoInterrupts();
	if (!bcm2835_init()){
		return;
	}
	
	bcm2835_spi_begin();
    rfInterrupts();
	
}

void SPI::end() {

}

void SPI::setBitOrder(uint8_t bit_order) {
    rfNoInterrupts();
	bcm2835_spi_setBitOrder(bit_order);
    rfInterrupts();
}

void SPI::setDataMode(uint8_t data_mode) {
  rfNoInterrupts();
  bcm2835_spi_setDataMode(data_mode);
  rfInterrupts();
}

void SPI::setClockDivider(uint16_t spi_speed) {
    rfNoInterrupts();
	bcm2835_spi_setClockDivider(spi_speed);
    rfInterrupts();
}

void SPI::chipSelect(int csn_pin){
    rfNoInterrupts();
	bcm2835_spi_chipSelect(csn_pin);
    rfInterrupts();
}

SPI::~SPI() {

}