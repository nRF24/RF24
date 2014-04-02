
/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 Added Arduino Due support from https://github.com/mcrosson/
 */

#ifndef __RF24_CONFIG_H__
#define __RF24_CONFIG_H__

  #if ARDUINO < 100
	#include <WProgram.h>
  #else
	#include <Arduino.h>
  #endif

  #include <stddef.h>

  //TMRh20:
  //#define MINIMAL

  // Define _BV for non-Arduino platforms and for Arduino DUE
  #if ! defined(ARDUINO) || (defined(ARDUINO) && defined(__arm__))
	#define _BV(x) (1<<(x))
  #endif

  #undef SERIAL_DEBUG
  #ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
  #else
	#define IF_SERIAL_DEBUG(x)
  #endif

  // Avoid spurious warnings
  #if 1
	#if ! defined( NATIVE ) && defined( ARDUINO ) && ! defined(__arm__)
		#undef PROGMEM
		#define PROGMEM __attribute__(( section(".progmem.data") ))
		#undef PSTR
		#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
	#endif
  #endif

  // Progmem is Arduino-specific
  #if defined(ARDUINO) && ! defined(__arm__)
	#include <avr/pgmspace.h>
	#define PRIPSTR "%S"
  #else

  	#if ! defined(ARDUINO)
	  typedef char const char;
      else // Fill in pgm_read_byte that is used, but missing from DUE
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



  // Stuff that is normally provided by Arduino
  #if !defined ARDUINO

	#include <stdint.h>
	#include <stdio.h>
	#include <string.h>
	extern HardwareSPI SPI;
  #else

    #if !defined( __AVR_ATtiny85__ ) || defined( __AVR_ATtiny84__)
	  #include <SPI.h>
    #else
	  #define ATTINY

	  #define SPI_CLOCK_DIV4 0x00
	  #define SPI_CLOCK_DIV16 0x01
	  #define SPI_CLOCK_DIV64 0x02
	  #define SPI_CLOCK_DIV128 0x03
	  #define SPI_CLOCK_DIV2 0x04
	  #define SPI_CLOCK_DIV8 0x05
	  #define SPI_CLOCK_DIV32 0x06
	  //#define SPI_CLOCK_DIV64 0x07

	  #define SPI_MODE0 0x00
	  #define SPI_MODE1 0x04
	  #define SPI_MODE2 0x08
	  #define SPI_MODE3 0x0C

	  #define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
	  #define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
	  #define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR



	  class SPIClass {
	  public:
	    inline static byte transfer(byte _data);

	    static void begin(); // Default
	    static void end();

	    static void setDataMode(byte);
	    static void setClockDivider(byte);
	    static void setBitOrder(byte);
	  };

	  extern SPIClass SPI;

	  byte SPIClass::transfer(byte _data){

	  	USIDR = _data;
	  	USISR = _BV(USIOIF);

		while((USISR & _BV(USIOIF)) == 0){
	    	USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
	  	}
	  	return USIDR;
	  }
    #endif //ATTINY

  #endif //Defined Arduino

#endif // __RF24_CONFIG_H__

