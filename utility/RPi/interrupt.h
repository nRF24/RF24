/**
 * Interrupt functions
 */
#ifndef RF24_UTILITY_RPI_INTERRUPT_H_
#define RF24_UTILITY_RPI_INTERRUPT_H_

#include <pthread.h>          // pthread_t
#include <stdexcept>          // std::exception, std::string
#include "RF24_arch_config.h" // rf24_gpio_pin_t

#ifdef __cplusplus
extern "C" {
#endif

enum IrqEvent : uint8_t
{
    INT_EDGE_FALLING,
    INT_EDGE_RISING,
    INT_EDGE_BOTH,
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

/** Details related to a certain pin's ISR. */
struct IrqPinCache
{
    /// The pin number
    rf24_gpio_pin_t pin = 0;

    /// The posix thread ID.
    pthread_t id = 0;

    /// The user-designated ISR function (used as a callback)
    void (*function)(void) = nullptr;
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

/** Deprecated, no longer functional */
void rfNoInterrupts();

/** Deprecated, no longer functional */
void rfInterrupts();

#ifdef __cplusplus
}
#endif
#endif // RF24_UTILITY_RPI_INTERRUPT_H_
