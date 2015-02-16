
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 Added Arduino Due support from https://github.com/mcrosson/
 */
 
 /* spaniakos <spaniakos@gmail.com>
  Added __ARDUINO_X86__ support
*/

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__

  /*** USER DEFINES:  ***/  
  //#define FAILURE_HANDLING
  //#define SERIAL_DEBUG
  //#define MINIMAL
  //#define SPI_UART  // Requires library from https://github.com/TMRh20/Sketches/tree/master/SPI_UART
  //#define SOFTSPI   // Requires library from https://github.com/greiman/DigitalIO
  /**********************/
  #define rf24_max(a,b) (a>b?a:b)
  #define rf24_min(a,b) (a<b?a:b)


//Generic Linux/ARM
#if ( defined (__linux) || defined (LINUX) ) && defined( __arm__ ) // BeagleBone Black running GNU/Linux or any other ARM-based linux device

  // The Makefile checks for bcm2835 (RPi) and copies the correct includes.h file to /arch/includes.h
  // The includes.h file defines either RF24_RPi or RF24_BBB and includes the correct RF24_arch_config.h file
  #include "arch/includes.h"

//Arduino Due
#elif defined ARDUINO_SAM_DUE 
  
  #define RF24_DUE
  #include "arch/Due/RF24_arch_config.h"

//ATTiny  
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  
  #define RF24_TINY
  #include "arch/ATTiny/RF24_arch_config.h"

//LittleWire  
#elif defined(LITTLEWIRE)
  
  #include "arch/LittleWire/RF24_arch_config.h"

// MRAA
#elif defined(MRAA)
  
  #include "arch/mraa/RF24_arch_config.h"
  
//Everything else
#else 

  #if ARDUINO < 100
	#include <WProgram.h>
  #else
	#include <Arduino.h>
  #endif

  #include <stddef.h>
  
 
  // Define _BV for non-Arduino platforms and for Arduino DUE
#if defined (ARDUINO) && !defined (__arm__) && !defined (__ARDUINO_X86__)
	#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
		#define RF24_TINY
		#define _SPI SPI
		#include "arch/ATTiny/RF24_arch_config.h"
		
	#else
      #if defined SPI_UART
		#include <SPI_UART.h>
		#define _SPI uspi
	  #elif defined SOFTSPI
	  // change these pins to your liking
      //
      const uint8_t SOFT_SPI_MISO_PIN = 16; 
      const uint8_t SOFT_SPI_MOSI_PIN = 15; 
      const uint8_t SOFT_SPI_SCK_PIN = 14;  
      const uint8_t SPI_MODE = 0;
      #define _SPI spi
      
	  #else	    
		#include <SPI.h>
		#define _SPI SPI
	  #endif
	#endif
#else
  #include <stdint.h>
  #include <stdio.h>
  #include <string.h>


 #if defined(__arm__) || defined (CORE_TEENSY) || defined (__ARDUINO_X86__)
   #include <SPI.h>
 #endif

 #if !defined(CORE_TEENSY)	
   #define _BV(x) (1<<(x))
   #if !defined(__arm__) && !defined (__ARDUINO_X86__)
     extern HardwareSPI SPI;
   #endif
 #else
    #define printf Serial.printf
 #endif

  #define _SPI SPI
#endif

  
  #ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
  #else
	#define IF_SERIAL_DEBUG(x)
	#if defined(RF24_TINY)
	#define printf_P(...)
    #endif
  #endif
  
#if  defined (__ARDUINO_X86__)
	#define printf_P printf
	#define _BV(bit) (1<<(bit))
#endif
  
// Avoid spurious warnings
// Arduino DUE is arm and uses traditional PROGMEM constructs
#if 1
#if ! defined( NATIVE ) && defined( ARDUINO ) && ! defined(__arm__)  && ! defined( CORE_TEENSY3 )
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
#undef PSTR
#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
#endif
#endif

// Progmem is Arduino-specific
// Arduino DUE is arm and does not include avr/pgmspace
#if defined(ARDUINO) && ! defined(__arm__) && !defined (__ARDUINO_X86__)
	#include <avr/pgmspace.h>
	#define PRIPSTR "%S"
#else
#if ! defined(ARDUINO) // This doesn't work on Arduino DUE
	typedef char const char;
#else // Fill in pgm_read_byte that is used, but missing from DUE
	#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif

#if !defined ( CORE_TEENSY )
	typedef uint16_t prog_uint16_t;
	#define PSTR(x) (x)
	#define printf_P printf
	#define strlen_P strlen
	#define PROGMEM
	#define pgm_read_word(p) (*(p))
#endif

	#define PRIPSTR "%s"

#endif

#endif //Defined Linux 



#endif // __RF24_CONFIG_H__

