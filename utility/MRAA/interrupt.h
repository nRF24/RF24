#ifndef RF24_UTILITY_MRAA_INTERRUPT_H_
#define RF24_UTILITY_MRAA_INTERRUPT_H_

#include <stdexcept> // std::exception, std::string
#include "mraa.hpp"  // mraa::
#include "gpio.h"    // rf24_gpio_pin_t

#ifdef __cplusplus
extern "C" {
#endif

enum Edge
{
    INT_EDGE_FALLING = mraa::Edge::EDGE_FALLING,
    INT_EDGE_RISING = mraa::Edge::EDGE_RISING,
    INT_EDGE_BOTH = mraa::Edge::EDGE_BOTH,
};

/** Specific exception for IRQ errors */
class IRQException : public std::runtime_error
{
public:
    explicit IRQException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

/**
 * Take the details and create an interrupt handler that will
 * callback to the user-supplied function.
 */
int attachInterrupt(rf24_gpio_pin_t pin, uint8_t mode, void (*function)(void));

/**
 * Will cancel the interrupt thread, close the filehandle and release the pin.
 */
int detachInterrupt(rf24_gpio_pin_t pin);

#ifdef __cplusplus
}
#endif

#endif // RF24_UTILITY_MRAA_INTERRUPT_H_
