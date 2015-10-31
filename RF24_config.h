
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
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

  #if defined SPI_HAS_TRANSACTION && !defined SPI_UART && !defined SOFTSPI
    #define RF24_SPI_TRANSACTIONS
  #endif
  
//Generic Linux/ARM and //http://iotdk.intel.com/docs/master/mraa/
#if ( defined (__linux) || defined (LINUX) ) && defined( __arm__ ) || defined(MRAA) // BeagleBone Black running GNU/Linux or any other ARM-based linux device

  // The Makefile checks for bcm2835 (RPi) and copies the correct includes.h file to /utility/includes.h (Default is spidev config)
  // This behavior can be overridden by calling 'make RF24_SPIDEV=1' or 'make RF24_MRAA=1'
  // The includes.h file defines either RF24_RPi, MRAA or RF24_BBB and includes the correct RF24_arch_config.h file
  #include "utility/includes.h"

//ATTiny  
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
  
  #define RF24_TINY
  #include "utility/ATTiny/RF24_arch_config.h"

//LittleWire  
#elif defined(LITTLEWIRE)
  
  #include "utility/LittleWire/RF24_arch_config.h"

//Teensy  
#elif defined (TEENSYDUINO)

  #include "utility/Teensy/RF24_arch_config.h"  
//Everything else
#else 

  #include <Arduino.h>
  
  // RF modules support 10 Mhz SPI bus speed
  const uint32_t RF_SPI_SPEED = 10000000;  

#if defined (ARDUINO) && !defined (__arm__) && !defined (__ARDUINO_X86__)
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
#else
  // Define _BV for non-Arduino platforms and for Arduino DUE
  #include <stdint.h>
  #include <stdio.h>
  #include <string.h>


 #if defined(__arm__) || defined (__ARDUINO_X86__)
   #include <SPI.h>
 #endif

 
 #define _BV(x) (1<<(x))
 #if !defined(__arm__) && !defined (__ARDUINO_X86__)
   extern HardwareSPI SPI;
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
  
// Progmem is Arduino-specific
// Arduino DUE is arm and does not include avr/pgmspace
#if defined (ARDUINO_ARCH_ESP8266)

  #define PSTR(x) (x)
  #define printf Serial.printf
  #define sprintf(...) os_sprintf( __VA_ARGS__ )
  #define printf_P printf
  #define strlen_P strlen  
  #define PROGMEM
  #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
  #define pgm_read_word(p) (*(p))
  #define PRIPSTR "%s"

#elif defined(ARDUINO) && ! defined(__arm__) && !defined (__ARDUINO_X86__)
	#include <avr/pgmspace.h>
	#define PRIPSTR "%S"
#else
  #if ! defined(ARDUINO) // This doesn't work on Arduino DUE
	typedef char const char;
  #else // Fill in pgm_read_byte that is used, but missing from DUE
	#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
  #endif


  typedef uint16_t prog_uint16_t;
  #define PSTR(x) (x)
  #define printf_P printf
  #define strlen_P strlen
  #define PROGMEM
  #define pgm_read_word(p) (*(p))

  #define PRIPSTR "%s"

#endif

#endif



#endif // __RF24_CONFIG_H__

