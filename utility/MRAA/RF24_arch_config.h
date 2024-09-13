#ifndef RF24_UTILITY_MRAA_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_MRAA_RF24_ARCH_CONFIG_H_

#include <stdint.h> // uint16_t
#include <stdio.h>  // printf
#include <string.h> // strlen
#include "mraa.h"
#include "spi.h"
#include "gpio.h"
#include "compatibility.h"

//#include <UtilTime.h> // Precompiled arduino x86 based utiltime for timing functions

// GCC a Arduino Missing
#define HIGH             1
#define LOW              0
#define _BV(x)           (1 << (x))
#define pgm_read_word(p) (*(const unsigned short*)(p))
#define pgm_read_byte(p) (*(const unsigned char*)(p))
#define pgm_read_ptr(p)  (*(void* const*)(p))
#define _SPI             spi

#define RF24_LINUX
//typedef uint16_t prog_uint16_t;

#define PSTR(x)   (x)
#define printf_P  printf
#define sprintf_P sprintf
#define strlen_P  strlen
#define PROGMEM
#define PRIPSTR "%s"

#ifdef RF24_DEBUG
    #define IF_RF24_DEBUG(x) ({ x; })
#else
    #define IF_RF24_DEBUG(x)
#endif

#define digitalWrite(pin, value) GPIO::write(pin, value)
#define digitalRead(pin)         GPIO::read(pin)
#define pinMode(pin, direction)  GPIO::open(pin, direction)

#ifndef __TIME_H__
    // Prophet: Redefine time functions only if precompiled arduino time is not included
    #define delay(millisec)         __msleep(millisec)
    #define delayMicroseconds(usec) __usleep(usec)
    #define millis()                __millis()
#endif

#define INPUT  mraa::DIR_IN
#define OUTPUT mraa::DIR_OUT

// SPI defines for ARDUINO API
#define MSBFIRST 1
//#define SPI_MODE0 mraa::SPI_MODE0
#define SPI_CLOCK_DIV2 RF24_SPI_SPEED

#endif // RF24_UTILITY_MRAA_RF24_ARCH_CONFIG_H_
