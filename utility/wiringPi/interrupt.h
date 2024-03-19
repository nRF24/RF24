/**
 * Interrupt functions wrapped from pigpio library
 */
#ifndef RF24_UTILITY_WIRINGPI_INTERRUPT_H__
#define RF24_UTILITY_WIRINGPI_INTERRUPT_H__

#include <wiringPi.h>

#define attachInterrupt wiringPiISR

// wiringPi has no detachInterrupt() implementation. Therefor, we will not define it here.
// Invoking detachInterrupt() with this wiringPi driver/wrapper should trigger compilation errors

#endif // RF24_UTILITY_WIRINGPI_INTERRUPT_H__
