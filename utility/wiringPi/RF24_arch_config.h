/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 */
#ifndef RF24_UTILITY_WIRINGPI_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_WIRINGPI_RF24_ARCH_CONFIG_H_

#define RF24_LINUX

#include <stdint.h> // uint16_t
#include <stdio.h>  // printf
#include <string.h> // strlen
#include "spi.h"
#include "wiringPi.h"

#define _BV(x) (1 << (x))
#define _SPI   spi

#ifdef RF24_DEBUG
    #define IF_RF24_DEBUG(x) ({ x; })
#else
    #define IF_RF24_DEBUG(x)
#endif

// Avoid spurious warnings
#if !defined(NATIVE) && defined(ARDUINO)
    #undef PROGMEM
    #define PROGMEM __attribute__((section(".progmem.data")))
    #undef PSTR
    #define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0]; }))
#endif

typedef uint16_t prog_uint16_t;
typedef uint8_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFF

#define PSTR(x)  (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(const unsigned short*)(p))
#define PRIPSTR          "%s"
#define pgm_read_byte(p) (*(const unsigned char*)(p))
#define pgm_read_ptr(p)  (*(void* const*)(p))

#endif // RF24_UTILITY_WIRINGPI_RF24_ARCH_CONFIG_H_
