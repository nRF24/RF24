#ifndef RF24_UTILITY_LITTLEWIRE_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_LITTLEWIRE_RF24_ARCH_CONFIG_H_

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <stddef.h>

// Additional fixes for LittleWire
#include <LittleWireSPI/littlewirespi.h>
#include <LittleWireSPI/avr_fixes.h>

extern LittleWireSPI _SPI;

// GCC a Arduino Missing
#define _BV(x)           (1 << (x))
#define pgm_read_word(p) (*(const unsigned short*)(p))
#define pgm_read_byte(p) (*(const unsigned char*)(p))
#define pgm_read_ptr(p)  (*(void* const*)(p))

//typedef uint16_t prog_uint16_t;
typedef uint8_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFF

#define PSTR(x)  (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define PRIPSTR "%s"

#ifdef SERIAL_DEBUG
    #define IF_SERIAL_DEBUG(x) ({ x; })
#else
    #define IF_SERIAL_DEBUG(x)
    #if defined(RF24_TINY)
        #define printf_P(...)
    #endif
#endif

#endif // RF24_UTILITY_LITTLEWIRE_RF24_ARCH_CONFIG_H_
