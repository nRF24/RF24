/*
 * TMRh20 2015
 *
 */

#include <map>
#include <mraa.h> // mraa_strresult()
#include "gpio.h"

// cache for mraa::Gpio instances
std::map<rf24_gpio_pin_t, mraa::Gpio*> gpio_cache;

GPIO::GPIO()
{
}

GPIO::~GPIO()
{
    // deinitialize cache of mraa::Gpio instances/pointers
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i;
    for (i = gpio_cache.begin(); i != gpio_cache.end(); i++) {
        i->second->close();
    }
    gpio_cache.clear();
}

void GPIO::open(rf24_gpio_pin_t port, mraa::Dir DDR)
{
    mraa::Result status;

    // check that mraa::Gpio context doesn't already exist
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i = gpio_cache.find(port);
    if (i == gpio_cache.end()) {
        mraa::Gpio* gpio_inst = new mraa::Gpio(port);
        gpio_cache[port] = gpio_inst;
        status = gpio_inst->dir(DDR);
    }
    else {
        status = i->second->dir(DDR);
    }
    if (status != mraa::SUCCESS) {
        std::string msg = "[GPIO::open] Could not set the pin direction; ";
        msg += mraa_strresult((mraa_result_t)status);
        throw GPIOException(msg);
    }
}

void GPIO::close(rf24_gpio_pin_t port)
{
    // check that mraa::Gpio context exists, meaning GPIO::open() was called.
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i = gpio_cache.find(port);
    if (i != gpio_cache.end()) {
        i->second->close();  // close the cached Gpio instance
        gpio_cache.erase(i); // Delete cache entry
    }
}

int GPIO::read(rf24_gpio_pin_t port)
{
    // get cache gpio instance
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i = gpio_cache.find(port);
    if (i != gpio_cache.end()) {
        return i->second->read();
    }
    throw GPIOException("[GPIO::read] pin was not initialized with GPIO::open()");
    return -1;
}

void GPIO::write(rf24_gpio_pin_t port, int value)
{
    // get cache gpio instance
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i = gpio_cache.find(port);
    if (i != gpio_cache.end()) {
        mraa::Result result = i->second->write(value);
        if (result != mraa::Result::SUCCESS) {
            std::string msg = "[GPIO::write] Could not set pin output value; ";
            msg += mraa_strresult((mraa_result_t)result);
            throw GPIOException(msg);
        }
    }
    else {
        throw GPIOException("[GPIO::write] pin was not initialized with GPIO::open()");
    }
}
