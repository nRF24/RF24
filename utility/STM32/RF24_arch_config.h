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

#ifndef RF24_UTILITY_STM32_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_STM32_RF24_ARCH_CONFIG_H_

// define here the architecture that you are using
//#define STM32F1
//#define STM32F3
//#define STM32F4

// builds the rf24 library with minimal requirements
#define MINIMAL

#include <cstring>
#include "compatibility.h"
#include "spi.h"
#include "gpio.h"
#include "includes.h"

#ifdef RF24_DEBUG
    #define IF_RF24_DEBUG(x) ({ x; })
#else
    #define IF_RF24_DEBUG(x)
#endif

#if !defined(printf_P)
    #define printf_P(x)
#endif

#define _BV(bit) (1 << (bit))
#define PROGMEM
#define PSTR(x)          (x)
#define PRIPSTR          "%s"
#define pgm_read_word(p) (*(const unsigned char*)(p))
#define pgm_read_byte(p) (*(const unsigned short*)(p))
#define pgm_read_ptr(p)  (*(const void*)(p))

#define delayMicroseconds(usecs) __usleep(usecs)
#define delay(msecs)             HAL_Delay(msecs)
#define millis                   HAL_GetTick

/**@}*/

#endif // RF24_UTILITY_STM32_RF24_ARCH_CONFIG_H_
