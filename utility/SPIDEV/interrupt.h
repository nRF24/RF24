/*
Interrupt functions
*/
#ifndef __RF24_INTERRUPT_H__
#define __RF24_INTERRUPT_H__

#include "RF24_arch_config.h"
#include <pigpio.h>

#define INT_EDGE_SETUP   0
#define INT_EDGE_FALLING FALLING_EDGE
#define INT_EDGE_RISING  RISING_EDGE
#define INT_EDGE_BOTH    EITHER_EDGE

#ifdef __cplusplus
extern "C" {
#endif

/*
 * attachInterrupt (Original: wiringPiISR):
 *      Pi Specific.
 *      Take the details and create an interrupt handler that will do a call-
 *      back to the user supplied function.
 *********************************************************************************
 */
extern int attachInterrupt(int pin, int mode, void (*function)(void));

/*
 * detachInterrupt:
 *      Pi Specific detachInterrupt.
 *      Will cancel the interrupt thread, close the filehandle and
 *		setting wiringPi back to 'none' mode.
 *********************************************************************************
 */
extern int detachInterrupt(int pin);

/* Deprecated, no longer functional
*/
extern void rfNoInterrupts();

/* Deprecated, no longer functional
*/
extern void rfInterrupts();

#ifdef __cplusplus
}
#endif
#endif
