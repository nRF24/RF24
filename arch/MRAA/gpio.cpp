/* 
 * TMRh20 2015
 * 
 */

#include "gpio.h"

GPIO::GPIO() {
}

GPIO::~GPIO() {
}

void GPIO::begin(uint8_t ce_pin, uint8_t cs_pin)
{	
	gpio_ce_pin = ce_pin;
	gpio_cs_pin = cs_pin;
	
	gpio_0 = new mraa::Gpio(ce_pin,0);
	gpio_1 = new mraa::Gpio(cs_pin,0);
	
}
void GPIO::open(int port, int DDR)
{		
	if(port == gpio_ce_pin){
		gpio_0 = new mraa::Gpio(port,0);
		gpio_0->useMmap(true);
		gpio_0->dir( (mraa::Dir)DDR);
	}else
	if(port == gpio_cs_pin){
		gpio_1 = new mraa::Gpio(port,0);
		gpio_1->useMmap(true);
		gpio_1->dir( (mraa::Dir)DDR);
	}		
}

void GPIO::close(int port)
{	
	delete gpio_0;
	delete gpio_1;
}

int GPIO::read(int port)
{	
	if(port == gpio_ce_pin){
		return gpio_0->read();
	}else
	if(port == gpio_cs_pin){
		return gpio_1->read();
	}
	return -1;
}

void GPIO::write(int port, int value){
	
	if(port == gpio_ce_pin){
		gpio_0->write( value);
	}else
	if(port == gpio_cs_pin){
		gpio_1->write( value);
	}
}
