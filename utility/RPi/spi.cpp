

#include "spi.h"

SPI::SPI() {

}


void SPI::begin( int busNo ) {
    spiNoInterrupts();
	if (!bcm2835_init()){
        spiInterrupts();
		return;
	}
	
	bcm2835_spi_begin();
	spiInterrupts();
}

void SPI::end() {

}

void SPI::setBitOrder(uint8_t bit_order) {
    spiNoInterrupts();
	bcm2835_spi_setBitOrder(bit_order);
    spiInterrupts();
}

void SPI::setDataMode(uint8_t data_mode) {
  spiNoInterrupts();
  bcm2835_spi_setDataMode(data_mode);
  spiInterrupts();
}

void SPI::setClockDivider(uint16_t spi_speed) {
    spiNoInterrupts();
	bcm2835_spi_setClockDivider(spi_speed);
    spiInterrupts();
}

void SPI::chipSelect(int csn_pin){
    spiNoInterrupts();
	bcm2835_spi_chipSelect(csn_pin);
    spiInterrupts();
}

SPI::~SPI() {

}