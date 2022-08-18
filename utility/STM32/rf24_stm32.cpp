#include "RF24_arch_config.h"


static GPIO_TypeDef* decode_pin(uint8_t pin, uint16_t* decoded_pin) {
    GPIO_TypeDef* port;
    *decoded_pin = 1 << (pin % 16);

    switch (pin / 16) {
#if defined(GPIOA)
        case 0:
            port = GPIOA;
            break;
#endif
#if defined(GPIOB)
        case 1:
            port = GPIOB;
            break;
#endif
#if defined(GPIOC)
        case 2:
            port = GPIOC;
            break;
#endif
#if defined(GPIOD)
        case 3:
            port = GPIOD;
            break;
#endif
#if defined(GPIOE)
        case 4:
            port = GPIOE;
            break;
#endif
#if defined(GPIOF)
            case 5:
            port = GPIOF;
            break;
#endif
#if defined(GPIOG)
            case 6:
            port = GPIOG;
            break;
#endif
        default:
            break;
    }

    return port;
}

static uint32_t rf24_get_time_us()
{
    return 1000 * HAL_GetTick() + 1000 - (SysTick->VAL / (SystemCoreClock / 1000000));
}

void pinMode(uint8_t pin, uint8_t direction) {
    uint16_t decoded_pin;
    GPIO_TypeDef* port = decode_pin(pin, &decoded_pin);

    GPIO_InitTypeDef config;
    config.Pull = GPIO_NOPULL;
    config.Speed = GPIO_SPEED_FREQ_HIGH;
    config.Pin = 1 << (pin % 16);
    config.Mode = direction;
    HAL_GPIO_Init(port, &config);
}

void digitalWrite(uint8_t pin, uint8_t value) {
    uint16_t decoded_pin;
    GPIO_TypeDef* port = decode_pin(pin, &decoded_pin);
    HAL_GPIO_WritePin(port, decoded_pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void delayMicroseconds(uint32_t usecs)
{
    uint32_t now = rf24_get_time_us();
    uint32_t blocked_until = now + usecs;
    while (blocked_until > rf24_get_time_us()) {}
}

RF24_SPI::RF24_SPI() {
    _hspi = nullptr;
}

void RF24_SPI::begin() {
    HAL_SPI_Init(_hspi);
}

void RF24_SPI::begin(SPI_HandleTypeDef* hspi) {
    _hspi = hspi;
}

uint8_t RF24_SPI::transfer(uint8_t data_to_send) {
    uint8_t rx_data;
    HAL_SPI_TransmitReceive(_hspi, &data_to_send, &rx_data, 1, HAL_MAX_DELAY);
    return rx_data;
}

RF24_SPI _SPI;
