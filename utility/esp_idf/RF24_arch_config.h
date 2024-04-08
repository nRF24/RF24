/**
 * @file RF24_arch_config.h
 * General defines and includes for RF24 on ESP-IDF platform
 */
#ifndef RF24_UTILITY_ESP_IDF_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_ESP_IDF_RF24_ARCH_CONFIG_H_

#define RF24_ESP_IDF

#include <stdint.h> // uintXX_t
#include <stdio.h>  // printf(), sprintf()
#include <string.h> // memcpy() used in RF24.cpp, strlen()
#include "spi.h"
#include "gpio.h"
#include "compatibility.h"

#define _BV(x) (1 << (x))
#define _SPI   SPIClass
#define RF24_SPI_PTR

#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
    #define IF_SERIAL_DEBUG(x) ({ x; })
#else
    #define IF_SERIAL_DEBUG(x)
#endif

typedef uint16_t prog_uint16_t;
#define PSTR(x)  (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(const unsigned short*)(p))
#define PRIPSTR          "%s"
#define pgm_read_byte(p) (*(const unsigned char*)(p))

// Function, constant map as a result of migrating from Arduino
#define LOW                      GPIO::OUTPUT_LOW
#define HIGH                     GPIO::OUTPUT_HIGH
#define INPUT                    GPIO::DIRECTION_IN
#define OUTPUT                   GPIO::DIRECTION_OUT
#define digitalWrite(pin, value) GPIO::write(pin, value)
#define pinMode(pin, direction)  GPIO::open(pin, direction)
#define delay(milisec)           __msleep(milisec)
#define delayMicroseconds(usec)  __usleep(usec)
#define millis()                 __millis()

#endif // RF24_UTILITY_ESP_IDF_RF24_ARCH_CONFIG_H_
