/*
Interrupt functions
*/

#include <linux/gpio.h>
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <sys/ioctl.h> // ioctl()
#include <errno.h>     // errno, strerror()
#include <string.h>    // std::string, strcpy()
#include <pthread.h>
#include <sys/poll.h>
#include <map>
#include "interrupt.h"
#include "gpio.h" // GPIOChipCache

#ifdef __cplusplus
extern "C" {
#endif

static pthread_mutex_t irq_mutex = PTHREAD_MUTEX_INITIALIZER;
std::map<rf24_gpio_pin_t, IrqPinCache> irqCache;

IrqPinCache::~IrqPinCache()
{
    pthread_join(id, NULL);
    if (fd > 0) {
        close(fd);
    }
}

struct IrqChipCache : public GPIOChipCache
{
    IrqChipCache() : GPIOChipCache() {};
    ~IrqChipCache()
    {
        for (std::map<rf24_gpio_pin_t, IrqPinCache>::iterator i = irqCache.begin(); i != irqCache.end(); ++i) {
            pthread_join(i->second.id, NULL);
            close(i->second.fd);
        }
        irqCache.clear();
    }
};

IrqChipCache irqChipCache;

int waitForInterrupt(pollfd* pollObj, int mS = -1)
{
    // pollObj.events = POLLPRI | POLLERR ;

    int x = poll(pollObj, 1, mS) ;
    return x ;
}

void* poll_irq(void* arg)
{
    IrqPinCache* pin_cache = (IrqPinCache*)(arg);
    struct pollfd poll_obj;
    poll_obj.fd = pin_cache->fd;
    poll_obj.events = POLLIN;

    for (;;) {
        if (waitForInterrupt(&poll_obj) > 0)
            pin_cache->function();
    }
    return NULL;
}

int attachInterrupt(rf24_gpio_pin_t pin, int mode, void (*function)(void))
{
    // ensure pin is not already being used in a separate thread
    detachInterrupt(pin);
    GPIO::close(pin);

    if (pin > irqChipCache.info.lines) {
        std::string msg = "[attachInterrupt] pin " + std::to_string(pin) + " is not available on " + irqChipCache.chip;
        throw GPIOException(msg);
        return 0;
    }

    // create a request object to configure the specified pin
    struct gpio_v2_line_request request;
    memset(&request, 0, sizeof(request));
    strcpy(request.consumer, "RF24 IRQ");
    request.num_lines = 1U;
    request.offsets[0] = pin;

    // set debounce for the pin
    request.config.attrs[0].mask = 1LL;
    request.config.attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_DEBOUNCE;
    request.config.attrs[0].attr.debounce_period_us = 10U;
    request.config.num_attrs = 1U;

    // set pin as input and configure edge detection
    request.config.flags = GPIO_V2_LINE_FLAG_INPUT | GPIO_V2_LINE_FLAG_ACTIVE_LOW;
    switch (mode) {
        case INT_EDGE_BOTH:
        case INT_EDGE_FALLING:
        case INT_EDGE_RISING:
            request.config.flags |= mode;
            break;
        default:
            // bad user input!
            return 0; // stop here
    }

    // write pin request's config
    irqChipCache.openDevice();
    int ret = ioctl(irqChipCache.fd, GPIO_V2_GET_LINE_IOCTL, &request);
    if (ret < 0 || request.fd <= 0) {
        std::string msg = "[attachInterrupt] Could not get line handle from ioctl; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return 0;
    }
    irqChipCache.closeDevice();

    ret = ioctl(request.fd, GPIO_V2_LINE_SET_CONFIG_IOCTL, &request.config);
    if (ret < 0) {
        std::string msg = "[attachInterrupt] Could not set line config; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return 0;
    }

    // create thread and cache details
    IrqPinCache cachedIrq;
    cachedIrq.fd = request.fd;
    cachedIrq.function = function;
    irqCache.insert(std::pair<rf24_gpio_pin_t, IrqPinCache>(pin, cachedIrq));

    pthread_mutex_lock(&irq_mutex);
    pthread_create(&cachedIrq.id, NULL, poll_irq, &cachedIrq);
    pthread_mutex_unlock(&irq_mutex);

    return 1;
}

int detachInterrupt(rf24_gpio_pin_t pin)
{
    std::map<rf24_gpio_pin_t, IrqPinCache>::iterator cachedPin = irqCache.find(pin);
    if (cachedPin == irqCache.end()) {
        return 0; // pin not in cache; just exit
    }
    pthread_join(cachedPin->second.id, NULL);
    close(cachedPin->second.fd);
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
