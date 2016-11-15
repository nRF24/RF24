#include "spi.h"
#include <pthread.h>

static pthread_mutex_t spiMutex;

SPISettings*
SPI_Settings(SPISettings * st, uint32_t clock, uint8_t bitOrder, uint8_t dataMode) 
{
        st->clck = clock;
        st->border = bitOrder;
        st->dmode = dataMode;
       
	return st; 
}

SPISettings*
SPI_Settings_default(SPISettings * st) 
{ 
        st->clck = RF24_SPI_SPEED;
        st->border = MSBFIRST;
        st->dmode = SPI_MODE0; 
	
	return st; 
}

void SPI_begin( int busNo ) {
	if (!bcm2835_init()){
		return;
	}
	
	bcm2835_spi_begin();
}

void SPI_beginTransaction(SPISettings settings){
   
	pthread_mutex_lock (&spiMutex);
	SPI_setBitOrder(settings.border);
	SPI_setDataMode(settings.dmode);
	SPI_setClockDivider(settings.clck);
}

void SPI_endTransaction() {
	pthread_mutex_unlock (&spiMutex);
}

void SPI_setBitOrder(uint8_t bit_order) {
	bcm2835_spi_setBitOrder(bit_order);
}

void SPI_setDataMode(uint8_t data_mode) {
  bcm2835_spi_setDataMode(data_mode);
}

void SPI_setClockDivider(uint16_t spi_speed) {
	bcm2835_spi_setClockDivider(spi_speed);
}

void SPI_chipSelect(int csn_pin){
	bcm2835_spi_chipSelect(csn_pin);
	delayMicroseconds(5);
}

uint8_t SPI_transfer(uint8_t _data) {
    uint8_t data = bcm2835_spi_transfer(_data);
    return data;
}

void SPI_transfernb(char* tbuf, char* rbuf, uint32_t len){
   bcm2835_spi_transfernb( tbuf, rbuf, len);
}

void SPI_transfern(char* buf, uint32_t len)
{
    SPI_transfernb(buf, buf, len);
}

