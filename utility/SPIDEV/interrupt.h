/**
 * Interrupt functions
 */
#ifndef __RF24_INTERRUPT_H__
#define __RF24_INTERRUPT_H__

#include <pthread.h> // pthread_t
#include "gpio.h"    // rf24_gpio_pin_t

#define INT_EDGE_SETUP   0
#define INT_EDGE_FALLING GPIO_V2_LINE_FLAG_EDGE_FALLING
#define INT_EDGE_RISING  GPIO_V2_LINE_FLAG_EDGE_RISING
#define INT_EDGE_BOTH    GPIO_V2_LINE_FLAG_EDGE_FALLING | GPIO_V2_LINE_FLAG_EDGE_RISING

#ifdef __cplusplus
extern "C" {
#endif

/** Details related to a certain pin's ISR. */
struct IrqPinCache
{
    /// The pin request's file descriptor
    int fd = 0;

    /// The posix thread ID.
    pthread_t id = 0;

    /// The user-designated ISR function (used as a callback)
    void (*function)(void) = nullptr;

    ~IrqPinCache();
};

/**
 * Take the details and create an interrupt handler that will
 * callback to the user-supplied function.
 */
int attachInterrupt(rf24_gpio_pin_t pin, int mode, void (*function)(void));

/**
 * Will cancel the interrupt thread, close the filehandle and release the pin.
 */
int detachInterrupt(rf24_gpio_pin_t pin);

/** Deprecated, no longer functional */
extern void rfNoInterrupts();

/** Deprecated, no longer functional */
extern void rfInterrupts();

#ifdef __cplusplus
}
#endif
#endif
