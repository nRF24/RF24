/**
 * @file gpio.h
 * Class declaration for GPIO helper files
 */

#ifndef RF24_UTILITY_STM32_GPIO_H_
#define RF24_UTILITY_STM32_GPIO_H_

#include <stdint.h>
#include "includes.h"

#define INPUT  GPIO_MODE_INPUT
#define OUTPUT GPIO_MODE_OUTPUT_PP
#define HIGH   true
#define LOW    false

typedef enum
{
    RF24_PA0 = 0,
    RF24_PA1,
    RF24_PA2,
    RF24_PA3,
    RF24_PA4,
    RF24_PA5,
    RF24_PA6,
    RF24_PA7,
    RF24_PA8,
    RF24_PA9,
    RF24_PA10,
    RF24_PA11,
    RF24_PA12,
    RF24_PA13,
    RF24_PA14,
    RF24_PA15,
    RF24_PB0,
    RF24_PB1,
    RF24_PB2,
    RF24_PB3,
    RF24_PB4,
    RF24_PB5,
    RF24_PB6,
    RF24_PB7,
    RF24_PB8,
    RF24_PB9,
    RF24_PB10,
    RF24_PB11,
    RF24_PB12,
    RF24_PB13,
    RF24_PB14,
    RF24_PB15,
    RF24_PC0,
    RF24_PC1,
    RF24_PC2,
    RF24_PC3,
    RF24_PC4,
    RF24_PC5,
    RF24_PC6,
    RF24_PC7,
    RF24_PC8,
    RF24_PC9,
    RF24_PC10,
    RF24_PC11,
    RF24_PC12,
    RF24_PC13,
    RF24_PC14,
    RF24_PC15,
    RF24_PD0,
    RF24_PD1,
    RF24_PD2,
    RF24_PD3,
    RF24_PD4,
    RF24_PD5,
    RF24_PD6,
    RF24_PD7,
    RF24_PD8,
    RF24_PD9,
    RF24_PD10,
    RF24_PD11,
    RF24_PD12,
    RF24_PD13,
    RF24_PD14,
    RF24_PD15,
    RF24_PE0,
    RF24_PE1,
    RF24_PE2,
    RF24_PE3,
    RF24_PE4,
    RF24_PE5,
    RF24_PE6,
    RF24_PE7,
    RF24_PE8,
    RF24_PE9,
    RF24_PE10,
    RF24_PE11,
    RF24_PE12,
    RF24_PE13,
    RF24_PE14,
    RF24_PE15,
    RF24_PF0,
    RF24_PF1,
    RF24_PF2,
    RF24_PF3,
    RF24_PF4,
    RF24_PF5,
    RF24_PF6,
    RF24_PF7,
    RF24_PF8,
    RF24_PF9,
    RF24_PF10,
    RF24_PF11,
    RF24_PF12,
    RF24_PF13,
    RF24_PF14,
    RF24_PF15,
    RF24_PG0,
    RF24_PG1,
    RF24_PG2,
    RF24_PG3,
    RF24_PG4,
    RF24_PG5,
    RF24_PG6,
    RF24_PG7,
    RF24_PG8,
    RF24_PG9,
    RF24_PG10,
    RF24_PG11,
    RF24_PG12,
    RF24_PG13,
    RF24_PG14,
    RF24_PG15,
} rf24_pin;

GPIO_TypeDef* decode_pin(uint8_t pin, uint16_t* decoded_pin);

void digitalWrite(uint8_t pin, uint8_t value);

void pinMode(uint8_t pin, uint8_t direction);

#endif // RF24_UTILITY_STM32_GPIO_H_
