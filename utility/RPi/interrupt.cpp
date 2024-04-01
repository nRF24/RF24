/**
 * Interrupt implementations
 */
#include <pthread.h>
#include <map>
#include "bcm2835.h"
#include "interrupt.h"

#ifdef __cplusplus
extern "C" {
#endif

static pthread_mutex_t irq_mutex = PTHREAD_MUTEX_INITIALIZER;
std::map<rf24_gpio_pin_t, IrqPinCache> irqCache;

// A simple struct instantiated privately to:
// 1. properly clean up open threads
// 2. clear BCM2835 lib's Edge Detection Status settings
struct IrqCacheDestructor
{
    ~IrqCacheDestructor()
    {
        for (std::map<rf24_gpio_pin_t, IrqPinCache>::iterator i = irqCache.begin(); i != irqCache.end(); ++i) {
            pthread_cancel(i->second.id);
            pthread_join(i->second.id, NULL);
            bcm2835_gpio_clr_aren(i->second.pin);
            bcm2835_gpio_clr_afen(i->second.pin);
            bcm2835_gpio_set_eds(i->second.pin);
        }
        irqCache.clear();
    }
} irqCacheMgr;

void* poll_irq(void* arg)
{
    IrqPinCache* pinCache = (IrqPinCache*)(arg);

    for (;;) {
        int ret = bcm2835_gpio_eds(pinCache->pin);
        if (ret > 0) {
            bcm2835_gpio_set_eds(pinCache->pin);
            pinCache->function();
        }
        pthread_testcancel();
    }
    return NULL;
}

int attachInterrupt(rf24_gpio_pin_t pin, uint8_t mode, void (*function)(void))
{
    // ensure pin is not already being used in a separate thread
    detachInterrupt(pin);

    // configure the specified pin
    switch (mode) {
        case INT_EDGE_BOTH:
            bcm2835_gpio_aren(pin);
            bcm2835_gpio_afen(pin);
            break;
        case INT_EDGE_RISING:
            bcm2835_gpio_aren(pin);
            break;
        case INT_EDGE_FALLING:
            bcm2835_gpio_afen(pin);
            break;
        default:
            // bad user input!
            return 0; // stop here
    }

    // cache details
    IrqPinCache irqPinCache;
    irqPinCache.pin = pin;
    irqPinCache.function = function;
    std::pair<std::map<rf24_gpio_pin_t, IrqPinCache>::iterator, bool> indexPair = irqCache.insert(std::pair<rf24_gpio_pin_t, IrqPinCache>(pin, irqPinCache));

    if (!indexPair.second) {
        // this should not be reached, but indexPair.first needs to be the inserted map element
        throw IRQException("[attachInterrupt] Could not cache the IRQ pin with function pointer");
        return 0;
    }

    // create and start thread
    pthread_mutex_lock(&irq_mutex);
    pthread_create(&indexPair.first->second.id, nullptr, poll_irq, &indexPair.first->second);
    pthread_mutex_unlock(&irq_mutex);

    return 1;
}

int detachInterrupt(rf24_gpio_pin_t pin)
{
    std::map<rf24_gpio_pin_t, IrqPinCache>::iterator cachedPin = irqCache.find(pin);
    if (cachedPin == irqCache.end()) {
        return 0; // pin not in cache; just exit
    }
    pthread_cancel(cachedPin->second.id);     // send cancel request
    pthread_join(cachedPin->second.id, NULL); // wait till thread terminates
    bcm2835_gpio_clr_aren(cachedPin->second.pin);
    bcm2835_gpio_clr_afen(cachedPin->second.pin);
    bcm2835_gpio_set_eds(cachedPin->second.pin);
    irqCache.erase(cachedPin);
    return 1;
}

void rfNoInterrupts()
{
}

void rfInterrupts()
{
}

#ifdef __cplusplus
}
#endif
