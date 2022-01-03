/*
Interrupts functions extruded from wiringPi library by Oitzu.

wiringPi Copyright (c) 2012 Gordon Henderson
https://projects.drogon.net/raspberry-pi/wiringpi
wiringPi is free software: GNU Lesser General Public License
see <http://www.gnu.org/licenses/>
*/

#include "interrupt.h"
#include <pigpio.h>


int attachInterrupt(int pin, int mode, void (* function)(void))
{
    gpioInitialise();
    return gpioSetISRFunc(pin,mode,0,(gpioISRFunc_t)function);
    
}

int detachInterrupt(int pin)
{
    return gpioSetISRFunc(pin,0,0,NULL);
}

void rfNoInterrupts()
{
    
}

void rfInterrupts()
{
    
}