#include "spi.h"
#include <pthread.h>

static pthread_mutex_t spiMutex;

SPI::SPI() {

}


void SPI::begin( int busNo ) {
	if (!bcm2835_init()){
		return;
	}
	
	bcm2835_spi_begin();
}

void SPI::beginTransaction(int clock_divider, uint8_t csn_pin) {
	pthread_mutex_lock (&spiMutex);
	setBitOrder(RF24_BIT_ORDER);
	setDataMode(RF24_DATA_MODE);
	setClockDivider(clock_divider);
	chipSelect(csn_pin);
	delayMicroseconds(5);
}

void SPI::endTransaction() {
	pthread_mutex_unlock (&spiMutex);
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