/*
 * Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

/**
 * @file RF24_arch_config.h
 * General defines and includes for RF24/Linux
 */

/**
 * Example of RF24_arch_config.h for RF24 portability
 *
 * @defgroup Porting_General Porting: General
 * @{
 */

#ifndef RF24_UTILITY_TEMPLATE_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_TEMPLATE_RF24_ARCH_CONFIG_H_

#include <cstdint>
#include <memory.h>

// define here the architecture that you are using
//#define STM32F1
//#define STM32F3
//#define STM32F4

// builds the rf24 library with minimal requirements
#define MINIMAL

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_gpio.h"
#include "stm32f3xx_hal_spi.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#endif

#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
    #define IF_SERIAL_DEBUG(x) ({ x; })
#else
    #define IF_SERIAL_DEBUG(x)
#endif

#if !defined(PROGMEM)
#define PROGMEM
#endif

#if !defined(_BV)
#define _BV(bit) (1<<(bit))
#endif

#if !defined(PSTR)
#define PSTR(x) (x)
#endif

#if !defined(printf_P)
#define printf_P(x)
#endif

#if !defined(pgm_read_word)
#define pgm_read_word(p) (*(p))
#endif

#if !defined(pgm_read_byte)
#define pgm_read_byte(p) (*(p))
#endif

#if !defined(pgm_read_ptr)
#define pgm_read_ptr(p)  (*(p))
#endif

typedef enum {
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

#if !defined(HIGH)
#define HIGH true
#endif

#if !defined(LOW)
#define LOW false
#endif

#if !defined(INPUT)
#define INPUT                    GPIO_MODE_INPUT
#endif

#if !defined(OUTPUT)
#define OUTPUT                   GPIO_MODE_OUTPUT_PP
#endif

#if !defined(digitalWrite)
void digitalWrite(uint8_t pin, uint8_t value);
#endif

#if !defined(pinMode)
void pinMode(uint8_t pin, uint8_t direction);
#endif

#if !defined(millis)
#define millis HAL_GetTick
#endif

#if !defined(delayMicroseconds)
void delayMicroseconds(uint32_t usecs);
#endif

#if !defined(delay)
#define delay(msecs) delayMicroseconds(1000*msecs)
#endif

class RF24_SPI {
public:
    RF24_SPI();
    void begin();
    void begin(SPI_HandleTypeDef* hspi);
    uint8_t transfer(uint8_t data_to_send);
private:
    SPI_HandleTypeDef* _hspi;
};

extern RF24_SPI _SPI;

/**@}*/

#endif // RF24_UTILITY_TEMPLATE_RF24_ARCH_CONFIG_H_
