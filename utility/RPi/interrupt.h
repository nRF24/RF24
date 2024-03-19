/**
 * Interrupt functions
 */
#ifndef RF24_UTILITY_RPI_INTERRUPT_H_
#define RF24_UTILITY_RPI_INTERRUPT_H_

#include <pthread.h> // pthread_t
#include <stdexcept>
#include <linux/gpio.h>       // GPIO_V2_LINE_FLAG_EDGE_***
#include "RF24_arch_config.h" // rf24_gpio_pin_t

#define INT_EDGE_FALLING GPIO_V2_LINE_FLAG_EDGE_FALLING
#define INT_EDGE_RISING  GPIO_V2_LINE_FLAG_EDGE_RISING
#define INT_EDGE_BOTH    GPIO_V2_LINE_FLAG_EDGE_FALLING | GPIO_V2_LINE_FLAG_EDGE_RISING

#ifdef __cplusplus
extern "C" {
#endif

/** Specific exception for IRQ errors */
class IRQException : public std::runtime_error
{
public:
    explicit IRQException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

/// A struct to manage the GPIO chip file descriptor.
/// This struct's destructor should close any cached GPIO pin requests' file descriptors.
struct IrqChipCache
{
    const char* chip = RF24_LINUX_GPIO_CHIP;
    int fd = -1;
    bool chipInitialized = false;

    /// Open the File Descriptor for the GPIO chip
    void openDevice();

    /// Close the File Descriptor for the GPIO chip
    void closeDevice();

    /// should be called automatically on program start.
    /// Here, we do some one-off configuration.
    IrqChipCache();

    /// Should be called automatically on program exit.
    /// What we need here is to make sure that the File Descriptors used to
    /// control GPIO pins are properly closed.
    ~IrqChipCache();
};

/** Details related to a certain pin's ISR. */
struct IrqPinCache
{
    /// The pin request's file descriptor
    int fd = 0;

    /// The posix thread ID.
    pthread_t id = 0;

    /// The user-designated ISR function (used as a callback)
    void (*function)(void) = nullptr;
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
void rfNoInterrupts();

/** Deprecated, no longer functional */
void rfInterrupts();

#ifdef __cplusplus
}
#endif
#endif // RF24_UTILITY_RPI_INTERRUPT_H_
