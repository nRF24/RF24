/*
Interrupt functions
*/

#include "interrupt.h"
#ifdef ORANGEPI
#include <wiringPi.h>
#else
#include <pigpio.h>
#endif

int attachInterrupt(int pin, int mode, void (*function)(void))
{
#ifdef ORANGEPI
    wiringPiSetup();
    return wiringPiISR(pin, mode, function);
#else
    gpioInitialise();
    return gpioSetISRFunc(pin, mode, 0, (gpioISRFunc_t)function);
#endif
}

int detachInterrupt(int pin)
{
#ifdef ORANGEPI
    return wiringPiISR(pin, 0, NULL);
#else
    return gpioSetISRFunc(pin, 0, 0, NULL);
#endif
}

void rfNoInterrupts()
{
}

void rfInterrupts()
{
}
