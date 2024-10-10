#include "gpio.h"

GPIO::GPIO()
{
}

void GPIO::open(rf24_gpio_pin_t port, gpio_mode_t direction)
{
    // gpio_config_t pin_conf;
    // pin_conf.pin_bit_mask = (1 << port);
    // pin_conf.mode = direction;
    // pin_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    // pin_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    // pin_conf.intr_type = GPIO_INTR_DISABLE;
    // esp_err_t ret = gpio_config(&pin_conf);
    // ESP_ERROR_CHECK(ret);
    close(port);
    esp_err_t ret = gpio_set_direction((gpio_num_t)port, direction);
    ESP_ERROR_CHECK(ret);
    ret = gpio_set_level((gpio_num_t)port, (uint32_t)0);
    ESP_ERROR_CHECK(ret);
}

void GPIO::close(rf24_gpio_pin_t port)
{
    esp_err_t ret = gpio_reset_pin((gpio_num_t)port);
    ESP_ERROR_CHECK(ret);
}

int GPIO::read(rf24_gpio_pin_t port)
{
    return gpio_get_level((gpio_num_t)port);
}

void GPIO::write(rf24_gpio_pin_t port, int value)
{
    esp_err_t ret = gpio_set_level((gpio_num_t)port, value);
    ESP_ERROR_CHECK(ret);
}

GPIO::~GPIO()
{
}
