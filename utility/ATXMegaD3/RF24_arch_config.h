/*
 * Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 */

/**
 * @file RF24_arch_config.h
 * General defines and includes for RF24/Linux
 */

#ifndef RF24_UTILITY_ATXMEGAD3_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_ATXMEGAD3_RF24_ARCH_CONFIG_H_

#include <stddef.h>
#include <avr/pgmspace.h>
#include "spi.h"
#include "gpio.h"
#include "compatibility.h"
#include <stdint.h>
#include <stdio.h>
//#include <time.h>
#include <string.h>
//#include <sys/time.h>

//#define _BV(x) (1<<(x))
#define _SPI SPI
#define RF24_SPI_PTR

#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
    #define IF_SERIAL_DEBUG(x) ({ x; })
#else
    #define IF_SERIAL_DEBUG(x)
#endif

// Use the avr pgmspace commands
//// Avoid spurious warnings
//#if 1
//#if ! defined( NATIVE ) && defined( ARDUINO )
//#undef PROGMEM
//#define PROGMEM __attribute__(( section(".progmem.data") ))
//#undef PSTR
//#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
//#endif
//#endif

typedef uint16_t prog_uint16_t;
//#define PSTR(x) (x)
//#define printf_P printf
//#define strlen_P strlen
//#define PROGMEM
//#define pgm_read_word(p) (*(const unsigned short *)(p))
#define PRIPSTR "%s"
//#define pgm_read_byte(p) (*(const unsigned char *)(p))

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

#endif // RF24_UTILITY_ATXMEGAD3_RF24_ARCH_CONFIG_H_
