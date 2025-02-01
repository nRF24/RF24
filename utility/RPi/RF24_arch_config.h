#ifndef RF24_UTILITY_RPI_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_RPI_RF24_ARCH_CONFIG_H_

#define RF24_LINUX

#include <stdint.h> // uint8_t
#include <stdio.h>  // printf
#include <string.h> // strlen
#include "bcm2835.h"
#include "spi.h"
#include "compatibility.h"

#define _SPI spi

#if defined(SPI_HAS_TRANSACTION)
    // this gets triggered as /utility/RPi/spi.h defines SPI_HAS_TRANSACTION (unless modified by end-user)
    #define RF24_SPI_TRANSACTIONS
#endif

// GCC a Arduino Missing
#define _BV(x)           (1 << (x))
#define pgm_read_word(p) (*(const unsigned short*)(p))
#define pgm_read_byte(p) (*(const unsigned char*)(p))
#define pgm_read_ptr(p)  (*(void* const*)(p))

//typedef uint16_t prog_uint16_t;
typedef uint8_t rf24_gpio_pin_t;
#define RF24_PIN_INVALID 0xFF

#ifndef RF24_LINUX_GPIO_CHIP
    /**
     * The default GPIO chip to use.
     * Defaults to `/dev/gpiochip0`.
     * Define this when compiling if this value is somehow incorrect.
     */
    #define RF24_LINUX_GPIO_CHIP "/dev/gpiochip0"
#endif

#define PSTR(x)  (x)
#define printf_P printf
#define strlen_P strlen
#define PROGMEM
#define PRIPSTR "%s"

#ifdef RF24_DEBUG
    #define IF_RF24_DEBUG(x) ({ x; })
#else
    #define IF_RF24_DEBUG(x)
#endif

#define digitalWrite(pin, value) bcm2835_gpio_write(pin, value)
#define pinMode(pin, value)      bcm2835_gpio_fsel(pin, value)
#define OUTPUT                   BCM2835_GPIO_FSEL_OUTP
#define INPUT                    BCM2835_GPIO_FSEL_INPT

#endif // RF24_UTILITY_RPI_RF24_ARCH_CONFIG_H_
