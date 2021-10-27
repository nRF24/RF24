#ifndef RF24_UTILITY_TEENSY_RF24_ARCH_CONFIG_H_
#define RF24_UTILITY_TEENSY_RF24_ARCH_CONFIG_H_
#if ARDUINO < 100

    #include <WProgram.h>

#else
    #include <Arduino.h>
#endif

#include <stddef.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <SPI.h>

#define _SPI SPIClass
#define RF24_SPI_PTR

#define printf Serial.printf

#ifdef SERIAL_DEBUG
    #define IF_SERIAL_DEBUG(x) ({ x; })
#else
    #define IF_SERIAL_DEBUG(x)
#endif

#define PRIPSTR "%s"

#endif // RF24_UTILITY_TEENSY_RF24_ARCH_CONFIG_H_
