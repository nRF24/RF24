/*
 *
 * Copyright (c) 2024, Copyright (c) 2024 TMRh20 & 2bndy5
 * All rights reserved.
 *
 *
 */
#include <linux/gpio.h>
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <sys/ioctl.h> // ioctl()
#include <errno.h>     // errno, strerror()
#include <string.h>    // std::string, strcpy()
#include <map>
#include "gpio.h"

// instantiate some global structs to setup cache
// doing this globally ensures the data struct is zero-ed out
typedef int gpio_fd; // for readability
std::map<rf24_gpio_pin_t, gpio_fd> cached_pins;
struct gpio_v2_line_request request;
struct gpio_v2_line_values data;

// use this struct to keep a track of open file descriptors
struct GlobalCache
{
    const char* chip = "/dev/gpiochip4";
    int fd = -1;

    // should be called automatically on program start.
    // Here, we do some one-off configuration.
    GlobalCache()
    {
        if (fd < 0) {
            fd = ::open(chip, O_RDWR);
            if (fd < 0) {
                chip = "/dev/gpiochip0";
                fd = ::open(chip, O_RDWR);
                if (fd < 0) {
                    std::string msg = "Can't open device ";
                    msg += chip;
                    throw GPIOException(msg);
                }
            }
        }
        request.num_lines = 1;
        strcpy(request.consumer, "RF24 lib");
        data.mask = 1ULL; // only change value for specified pin
    }

    // Should be called automatically on program exit.
    // What we need here is to make sure that the File Descriptors used to
    // control GPIO pins are properly closed.
    ~GlobalCache()
    {
        if (fd >= 0) {
            close(fd);
        }
        for (std::map<rf24_gpio_pin_t, gpio_fd>::iterator i = cached_pins.begin(); i != cached_pins.end(); ++i) {
            if (i->second > 0) {
                close(i->second);
            }
        }
    }
} gpio_cache;

GPIO::GPIO()
{
}

GPIO::~GPIO()
{
}

void GPIO::open(rf24_gpio_pin_t port, int DDR)
{
    // check if pin is already in use
    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = cached_pins.find(port);
    if (pin == cached_pins.end()) { // pin not in use; add it to cached request
        request.offsets[0] = port;
    }
    else {
        request.fd = pin->second;
    }
    // set the pin and direction
    request.config.flags = DDR ? GPIO_V2_LINE_FLAG_OUTPUT : GPIO_V2_LINE_FLAG_INPUT;

    int ret;
    if (request.fd <= 0) {
        ret = ioctl(gpio_cache.fd, GPIO_V2_GET_LINE_IOCTL, &request);
        if (ret == -1 || request.fd <= 0) {
            std::string msg = "[GPIO::open] Can't get line handle from IOCTL; ";
            msg += strerror(errno);
            throw GPIOException(msg);
            return;
        }
    }
    ret = ioctl(request.fd, GPIO_V2_LINE_SET_CONFIG_IOCTL, &request.config);
    if (ret == -1) {
        std::string msg = "[gpio::open] Can't set line config; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return;
    }
    cached_pins.insert(std::pair<rf24_gpio_pin_t, gpio_fd>(port, request.fd));
}

void GPIO::close(rf24_gpio_pin_t port)
{
    // This is not really used in RF24 convention (designed for embedded apps).
    // Instead rely on gpio_cache destructor (see above)
}

int GPIO::read(rf24_gpio_pin_t port)
{
    // if (gpio_cache.fd < 0) {
    //     throw GPIOException("[GPIO::read] device not initialized! Use GPIO::open() first.");
    //     return -1;
    // }

    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = cached_pins.find(port);
    if (pin == cached_pins.end() || pin->second <= 0) {
        throw GPIOException("[GPIO::read] pin not initialized! Use GPIO::open() first");
        return -1;
    }

    data.bits = 0ULL;

    int ret = ioctl(pin->second, GPIO_V2_LINE_GET_VALUES_IOCTL, &data);
    if (ret == -1) {
        std::string msg = "[GPIO::read] Can't get line value from IOCTL; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return ret;
    }
    return data.bits & 1ULL;
}

void GPIO::write(rf24_gpio_pin_t port, int value)
{
    // if (gpio_cache.fd < 0) {
    //     throw GPIOException("[GPIO::write] device not initialized! Use GPIO::open() first.");
    //     return;
    // }

    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = cached_pins.find(port);
    if (pin == cached_pins.end() || pin->second <= 0) {
        throw GPIOException("[GPIO::write] pin not initialized! Use GPIO::open() first");
        return;
    }

    data.bits = value;

    int ret = ioctl(pin->second, GPIO_V2_LINE_SET_VALUES_IOCTL, &data);
    if (ret == -1) {
        std::string msg = "[GPIO::write] Can't set line value from IOCTL; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return;
    }
}
