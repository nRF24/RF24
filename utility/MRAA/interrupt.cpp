#include <map>
#include <mraa.h>   // mraa_strresult()
#include <mraa.hpp> // mraa::Gpio
#include "interrupt.h"
#include "gpio.h" // rf24_gpio_pin_t

#ifdef __cplusplus
extern "C" {
#endif

std::map<rf24_gpio_pin_t, mraa::Gpio*> irqCache;

int attachInterrupt(rf24_gpio_pin_t pin, uint8_t mode, void (*function)(void))
{
    // ensure pin is not already being used in a separate thread
    detachInterrupt(pin);
    GPIO::close(pin);

    mraa::Gpio* gpio = new mraa::Gpio(pin);
    mraa::Result status = gpio->dir(mraa::DIR_IN);
    if (status != mraa::SUCCESS) {
        std::string msg = "[attachInterrupt] Could not set the pin as an input; ";
        msg += mraa_strresult((mraa_result_t)status);
        throw IRQException(msg);
        return 0;
    }
    status = gpio->isr((mraa::Edge)mode, (void (*)(void*))function, NULL);
    if (status != mraa::SUCCESS) {
        std::string msg = "[attachInterrupt] Could not setup the ISR; ";
        msg += mraa_strresult((mraa_result_t)status);
        throw IRQException(msg);
        return 0;
    }

    std::pair<std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator, bool> indexPair = irqCache.insert(std::pair<rf24_gpio_pin_t, mraa::Gpio*>(pin, gpio));
    if (!indexPair.second) {
        // this should not be reached, but indexPair.first needs to be the inserted map element
        gpio->close();
        throw IRQException("[attachInterrupt] Could not cache the mraa::Gpio object");
        return 0;
    }
    return 1;
}

int detachInterrupt(rf24_gpio_pin_t pin)
{
    std::map<rf24_gpio_pin_t, mraa::Gpio*>::iterator cachedPin = irqCache.find(pin);
    if (cachedPin == irqCache.end()) {
        return 0; // pin not in cache; just exit
    }
    cachedPin->second->close();
    irqCache.erase(cachedPin);
    return 1;
}

#ifdef __cplusplus
}
#endif
