/*
 *
 * Copyright (c) 2024, Copyright (c) 2024 TMRh20 & 2bndy5
 * All rights reserved.
 *
 *
 */
#include "linux/gpio.h"
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <sys/ioctl.h> // ioctl()
#include <errno.h>     // errno, strerror()
#include <string.h>    // std::string, strcpy()
#include "gpio.h"

// instantiate some global structs to setup cache
// doing this globally ensures the data struct is zero-ed out
struct gpio_v2_line_request request;
struct gpio_v2_line_values data;

// initialize static members.
int GPIOChipCache::fd = -1;
std::map<rf24_gpio_pin_t, gpio_fd> GPIOChipCache::cachedPins = std::map<rf24_gpio_pin_t, gpio_fd>();

void GPIOChipCache::openDevice()
{
    if (fd < 0) {
        fd = open(RF24_LINUX_GPIO_CHIP, O_RDONLY);
        if (fd < 0) {
            std::string msg = "Can't open device ";
            msg += RF24_LINUX_GPIO_CHIP;
            msg += "; ";
            msg += strerror(errno);
            throw GPIOException(msg);
            return;
        }
    }
}

void GPIOChipCache::closeDevice()
{
    if (fd >= 0) {
        close(fd);
        fd = -1;
    }
}

GPIOChipCache::GPIOChipCache()
{
    request.num_lines = 1;
    strcpy(request.consumer, "RF24 lib");
    data.mask = 1ULL; // only change value for specified pin
}

GPIOChipCache::~GPIOChipCache()
{
    closeDevice();
    for (std::map<rf24_gpio_pin_t, gpio_fd>::iterator i = cachedPins.begin(); i != cachedPins.end(); ++i) {
        if (i->second > 0) {
            close(i->second);
        }
    }
}

// GPIO chip cache manager
GPIOChipCache gpioCache;

GPIO::GPIO()
{
}

GPIO::~GPIO()
{
}

void GPIO::open(rf24_gpio_pin_t port, int DDR)
{
    gpioCache.openDevice();

    // get chip info
    gpiochip_info info;
    memset(&info, 0, sizeof(info));
    int ret = ioctl(gpioCache.fd, GPIO_GET_CHIPINFO_IOCTL, &info);
    if (ret < 0) {
        std::string msg = "Could not gather info about ";
        msg += RF24_LINUX_GPIO_CHIP;
        throw GPIOException(msg);
        return;
    }

    if (port > info.lines) {
        std::string msg = "pin number " + std::to_string(port) + " not available for " + RF24_LINUX_GPIO_CHIP;
        throw GPIOException(msg);
        return;
    }

    // check if pin is already in use
    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = gpioCache.cachedPins.find(port);
    if (pin == gpioCache.cachedPins.end()) { // pin not in use; add it to cached request
        request.offsets[0] = port;
        request.fd = 0;
    }
    else {
        request.fd = pin->second;
    }

    if (request.fd <= 0) {
        ret = ioctl(gpioCache.fd, GPIO_V2_GET_LINE_IOCTL, &request);
        if (ret == -1 || request.fd <= 0) {
            std::string msg = "[GPIO::open] Can't get line handle from IOCTL; ";
            msg += strerror(errno);
            throw GPIOException(msg);
            return;
        }
    }
    gpioCache.closeDevice(); // in case other apps want to access it

    // set the pin and direction
    request.config.flags = DDR ? GPIO_V2_LINE_FLAG_OUTPUT : GPIO_V2_LINE_FLAG_INPUT;

    ret = ioctl(request.fd, GPIO_V2_LINE_SET_CONFIG_IOCTL, &request.config);
    if (ret == -1) {
        std::string msg = "[gpio::open] Can't set line config; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return;
    }
    gpioCache.cachedPins.insert(std::pair<rf24_gpio_pin_t, gpio_fd>(port, request.fd));
}

void GPIO::close(rf24_gpio_pin_t port)
{
    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = gpioCache.cachedPins.find(port);
    if (pin == gpioCache.cachedPins.end()) {
        return;
    }
    if (pin->second > 0) {
        ::close(pin->second);
    }
    gpioCache.cachedPins.erase(pin);
}

int GPIO::read(rf24_gpio_pin_t port)
{
    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = gpioCache.cachedPins.find(port);
    if (pin == gpioCache.cachedPins.end() || pin->second <= 0) {
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
    std::map<rf24_gpio_pin_t, gpio_fd>::iterator pin = gpioCache.cachedPins.find(port);
    if (pin == gpioCache.cachedPins.end() || pin->second <= 0) {
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
