/*

*/

#include "interrupt.h"
#include <pigpio.h>

int attachInterrupt(int pin, int mode, void (*function)(void))
{
    gpioInitialise();
    return gpioSetISRFunc(pin, mode, 0, (gpioISRFunc_t)function);
}

int detachInterrupt(int pin)
{
    return gpioSetISRFunc(pin, 0, 0, NULL);
}

void rfNoInterrupts()
{
}

void rfInterrupts()
{
}