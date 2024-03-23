/*
 * TMRh20 2015
 *
 */

#include <map>
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
    // check that mraa::Gpio context doesn't already exist
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i = gpio_cache.find(port);
    if (i == gpio_cache.end()) {
        mraa::Gpio* gpio_inst = new mraa::Gpio(port);
        gpio_cache[port] = gpio_inst;
        gpio_inst->dir(DDR);
    }
    else {
        i->second->dir(DDR);
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
    mraa::Result result = mraa::Result::ERROR_UNSPECIFIED; // a default
    // get cache gpio instance
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator i = gpio_cache.find(port);
    if (i != gpio_cache.end()) {
        result = i->second->write(value);
    }
    else {
        throw GPIOException("[GPIO::write] pin was not initialized with GPIO::open()");
    }

    if (result != mraa::Result::SUCCESS) {
        throw GPIOException("GPIO::write() failed");
    }
}
