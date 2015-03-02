
#ifndef __ARCH_CONFIG_H__
#define __ARCH_CONFIG_H__

  #define RF24_LINUX
  
  #include <stdint.h>
  #include <stdio.h>
  #include <time.h>
  #include <string.h>
  #include <sys/time.h>
  #include <stddef.h>
  
  #include "bcm2835.h"
  #include "spi.h"
  #define _SPI spi
    #define RF24_BIT_ORDER BCM2835_SPI_BIT_ORDER_MSBFIRST
	#define RF24_DATA_MODE BCM2835_SPI_MODE0
	#define RF24_CLOCK_DIVIDER BCM2835_SPI_SPEED_8MHZ
		
  // GCC a Arduino Missing
  #define _BV(x) (1<<(x))
  #define pgm_read_word(p) (*(p))
  #define pgm_read_byte(p) (*(p))
  
  //typedef uint16_t prog_uint16_t;
  #define PSTR(x) (x)
  #define printf_P printf
  #define strlen_P strlen
  #define PROGMEM
  #define PRIPSTR "%s"

  #ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
  #else
	#define IF_SERIAL_DEBUG(x)
  #endif
  
  #define digitalWrite(pin, value) bcm2835_gpio_write(pin, value)
  #define pinMode(pin,value) bcm2835_gpio_fsel(pin,value);
  #define OUTPUT BCM2835_GPIO_FSEL_OUTP
  
#endif