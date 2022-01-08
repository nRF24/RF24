/*
* GPIO Functions
 */

#include "gpio.h"
#include <pigpio.h>

bool initialized = 0;

GPIO::GPIO()
{
    
}

GPIO::~GPIO()
{
    gpioTerminate();
}

void GPIO::open(int port, int DDR)
{
    if(!initialized){
        gpioInitialise();
    }
    initialized = true;
}

void GPIO::close(int port)
{
    
}

int GPIO::read(int port)
{
    return gpioRead( port );
}

void GPIO::write(int port, int value)
{
    gpioWrite(port, value);
}
