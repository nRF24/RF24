#include "gpio.h"

GPIO::GPIO()
{
    //printf("PicoRF24: GPIO::GPIO\n");
}

void GPIO::open(int port, int DDR) {
    //printf("PicoRF24: GPIO::open(int port: %d, int DDR: %d)\n", port, DDR);
    gpio_init(port);
    gpio_set_dir(port, DDR);
}

void GPIO::close(int port) {
    //printf("PicoRF24: GPIO::close(int port: %d)\n", port);
    gpio_init(port);
}

int GPIO::read(int port) {
    //printf("PicoRF24: GPIO::read(int port: %d)\n", port);
    return gpio_get(port);
}

void GPIO::write(int port, int value) {
    //printf("PicoRF24: GPIO::write(int port: %d, int value: %d)\n", port, value);
    gpio_put(port, value);
}

GPIO::~GPIO()
{
    //printf("PicoRF24: GPIO::~GPIO\n");
}
