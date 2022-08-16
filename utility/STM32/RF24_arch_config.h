#ifndef RF24_UTILITY_STM32_RF24_ARCH_CONFIG_H
#define RF24_UTILITY_STM32_RF24_ARCH_CONFIG_H


#include <cstdint>
#include <memory.h>


#if defined(STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32F1)
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#elif defined(STM32L0)
#include "stm32l0xx_hal.h"
#elif defined(STM32L1)
#include "stm32l1xx_hal.h"
#elif defined(STM32L4)
#include "stm32l4xx_hal.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#elif defined(STM32G0)
#include "stm32g0xx_hal.h"
#elif defined(STM32G4)
#include "stm32g4xx_hal.h"
#endif


#if !defined(PROGMEM)
#define PROGMEM
#endif

#if !defined(HIGH)
#define HIGH true
#endif

#if !defined(LOW)
#define LOW false
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

#if !defined(_BV)
#define _BV(bit) (1<<(bit))
#endif

#if !defined(PSTR)
#define PSTR(x) (x)
#endif

#if !defined(printf_P)
#define printf_P printf
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

class DummySpi {
public:
    DummySpi(SPI_HandleTypeDef* hspi);
    void begin();
    uint8_t transfer(uint8_t data_to_send);
    uint32_t get_baud();
private:
    SPI_HandleTypeDef* _hspi;
};

#define RF24_SPI_PTR
#define _SPI DummySpi


#endif //RF24_UTILITY_STM32_RF24_ARCH_CONFIG_H
