#include "gpio.h"

GPIO::GPIO()
{
}

void GPIO::open(rf24_gpio_pin_t port, gpio_mode_t direction)
{
    gpio_config_t pin_conf;
    pin_conf.pin_bit_mask = (1 << port);
    pin_conf.mode = direction;
    pin_conf.pull_up_en = GPIO_PULLDOWN_DISABLE;
    pin_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    pin_conf.intr_type = GPIO_INTR_DISABLE;
    esp_err_t ret = gpio_config(&pin_conf);
    ESP_ERROR_CHECK(ret);
}

void GPIO::close(rf24_gpio_pin_t port)
{
    esp_err_t ret = gpio_reset_pin(port);
    ESP_ERROR_CHECK(ret);
}

int GPIO::read(rf24_gpio_pin_t port)
{
    return gpio_get_level(port);
}

void GPIO::write(rf24_gpio_pin_t port, int value)
{
    esp_err_t ret = gpio_set_level(port, value);
    ESP_ERROR_CHECK(ret);
}

GPIO::~GPIO()
{
}
