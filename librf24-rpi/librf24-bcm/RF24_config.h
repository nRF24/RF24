
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__


#ifdef ARDUINO
  //#warning "Arduino enabled"
  #if ARDUINO < 100
    //#include <WProgram.h>
  #else
    //#include <Arduino.h>
  #endif

#else 
	//#warning "Arduino disabled"
	#include "compatibility.h"
	#include <stdint.h>
	#include <stdio.h>
	#include <time.h>
	#include <string.h>
	#include <sys/time.h>
	//#include <stdlib.h>
	//#include <unistd.h> 
	#include <bcm2835.h> 

	#define pgm_read_word(p) (*(p))
	#define pgm_read_byte(p) (*(p))

	// Function, constant map as a result of migrating from Arduino
//	#define delay(milisec) __msleep(milisec)
//	#define delayMicroseconds(usec) __usleep(usec)
	
	
	// GCC Missing
	#define max(a,b) (a>b?a:b)
	#define min(a,b) (a<b?a:b)
#endif

#include <stddef.h>



#define _BV(x) (1<<(x))

#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
  #define IF_SERIAL_DEBUG(x) ({x;})
#else
  #define IF_SERIAL_DEBUG(x)
#endif

// Avoid spurious warnings
#if 1
	#if ! defined( NATIVE ) && defined( ARDUINO )
		#undef PROGMEM
		#define PROGMEM __attribute__(( section(".progmem.data") ))
		#undef PSTR
		#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
	#endif
#endif


typedef uint16_t prog_uint16_t;
#define PSTR(x) (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define pgm_read_word(p) (*(p)) 
#define PRIPSTR "%s"



//Chip enable and chip Select on ArduiPi Board
#define NRF_PI_CE    RPI_V2_GPIO_P1_15 	/* GPIO 22 pin 15 */
#define NRF_PI_CS    BCM2835_SPI_CS1		/* Chip Select 1  */


//#endif

#endif // __RF24_CONFIG_H__
// vim:ai:cin:sts=2 sw=2 ft=cpp
