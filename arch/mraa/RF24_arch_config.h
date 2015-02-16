#ifndef __ARCH_CONFIG_H__
#define __ARCH_CONFIG_H__

  #include <stdint.h>
  #include <stdio.h>
  #include <time.h>
  #include <string.h>
  #include <sys/time.h>
  #include <stddef.h>
  #include <iostream>
  #include <unistd.h>
  #include <stdlib.h>
  #include <mraa/gpio.h>
  #include <mraa/spi.h>

  #include <UtilTime.h> // Precompiled arduino x86 based utiltime for timing functions

  // GCC a Arduino Missing
  #define HIGH	1
  #define LOW	0
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
  
  
#endif
