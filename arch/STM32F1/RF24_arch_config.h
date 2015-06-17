  #if ARDUINO < 100
	#include <WProgram.h>
  #else
	#include <Arduino.h>
  #endif

  #define _BV(x) (1<<(x))

  #include <SPI.h>
  #define _SPI SPI
  extern SPIClass SPI;

  #define printf_P(...)
  #define printf(...)
  
  #ifdef SERIAL_DEBUG
	#define IF_SERIAL_DEBUG(x) ({x;})
  #else
	#define IF_SERIAL_DEBUG(x)
  #endif

