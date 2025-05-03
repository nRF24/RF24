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
#include <map>
#include "linux/gpio.h" // gpiochip_info

typedef uint16_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFFFF

#ifndef RF24_LINUX_GPIO_CHIP
    /// The default GPIO chip to use.  Defaults to `/dev/gpiochip0`.
    #define RF24_LINUX_GPIO_CHIP "/dev/gpiochip0"
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

typedef int gpio_fd; // for readability

/// A struct to manage the GPIO chip file descriptor.
/// This struct's destructor should close any cached GPIO pin requests' file descriptors.
struct GPIOChipCache
{
    /// @brief The file descriptor used to access the GPIO chip.
    ///
    /// This is used to open/close pins exposed by the GPIO chip specified via
    /// `RF24_LINUX_GPIO_CHIP`.
    ///
    /// Because this member is static, all instances (& derivative instances) of this
    /// struct use the same file descriptor.
    static int fd;

    /// @brief The map of pin numbers to their corresponding file descriptors.
    ///
    /// Because this member is static, all instances (& derivative instances) of this
    /// struct use the same mapping.
    static std::map<rf24_gpio_pin_t, gpio_fd> cachedPins;

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
