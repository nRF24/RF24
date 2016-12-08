
#define _XTAL_FREQ  32000000

#define MINIMAL

#ifdef __XC8 
#include<xc.h>

typedef  unsigned char bool;

typedef  char int8_t;
typedef  unsigned char uint8_t;

typedef  int int16_t;
typedef  unsigned int uint16_t;

typedef  long int32_t;
typedef  unsigned long uint32_t;


typedef unsigned int size_t;
#define __asm #asm
#define __endasm  #endasm

#else
#ifdef __SDCC_pic16
#include <pic18fregs.h>
#else
#include <pic16fregs.h>
#endif
void *malloc(unsigned int size);
void free(void *dat);
void *realloc(void *dat, unsigned int size);
#endif

//hard coded pins
#define csn_pin PORTBbits.RB2
#define ce_pin PORTBbits.RB3

#define csn_pin_t TRISBbits.TRISB2
#define ce_pin_t TRISBbits.TRISB3


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LOW  0
#define HIGH 1

#define INPUT  1
#define OUTPUT 0

#define true  1
#define false 0

#define F(x) x

  #if defined SPI_HAS_TRANSACTION && !defined SPI_UART && !defined SOFTSPI
    #define RF24_SPI_TRANSACTIONS
  #endif	
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
	#define IF_SERIAL_DEBUG(x) x //{x;})
  #else
	#define IF_SERIAL_DEBUG(x)
  #endif
  
extern unsigned long mtime;//for millis


//functions below in spi.c

//void digitalWrite(uint8_t pin,uint8_t value);
//void pinMode(uint8_t pin,uint8_t mode);
//uint8_t digitalRead(uint8_t pin);

long millis(void);

void delay(uint16_t d);
void delayMicroseconds(uint8_t d);



