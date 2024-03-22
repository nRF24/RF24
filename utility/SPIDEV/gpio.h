/**
 * https://github.com/mrshu/GPIOlib
 * Copyright (c) 2011, Copyright (c) 2011 mr.Shu
 * All rights reserved.
 *
 * Modified on 24 June 2012, 11:06 AM
 * @file gpio.h
 * Author: purinda (purinda@gmail.com)
 *
 * Class declaration for GPIO helper files
 */

#ifndef RF24_UTILITY_SPIDEV_GPIO_H_
#define RF24_UTILITY_SPIDEV_GPIO_H_

#include <stdexcept>
#include <cstdint>
#include "linux/gpio.h" // gpiochip_info

typedef uint16_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFFFF

#ifndef RF24_LINUX_GPIO_CHIP
    /**
     * The default GPIO chip to use.  Defaults to `/dev/gpiochip4` (for RPi5).
     * Falls back to `/dev/gpiochip0` if this value is somehow incorrect.
     */
    #define RF24_LINUX_GPIO_CHIP "/dev/gpiochip4"
#endif

/** Specific exception for GPIO errors */
class GPIOException : public std::runtime_error
{
public:
    explicit GPIOException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

/// A struct to manage the GPIO chip file descriptor.
/// This struct's destructor should close any cached GPIO pin requests' file descriptors.
struct GPIOChipCache
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
    GPIOChipCache();

    /// Should be called automatically on program exit.
    /// What we need here is to make sure that the File Descriptors used to
    /// control GPIO pins are properly closed.
    ~GPIOChipCache();
};

class GPIO
{

public:
    static const int DIRECTION_OUT = 1;
    static const int DIRECTION_IN = 0;

    static const int OUTPUT_HIGH = 1;
    static const int OUTPUT_LOW = 0;

    GPIO();

    static void open(rf24_gpio_pin_t port, int DDR);

    static void close(rf24_gpio_pin_t port);

    static int read(rf24_gpio_pin_t port);

    static void write(rf24_gpio_pin_t port, int value);

    virtual ~GPIO();

private:
};

#endif // RF24_UTILITY_SPIDEV_GPIO_H_
