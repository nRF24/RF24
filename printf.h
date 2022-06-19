/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
/*  Galileo support from spaniakos <spaniakos@gmail.com> */

/**
 * @file printf.h
 *
 * Setup necessary to direct stdout to the Arduino Serial library, which
 * enables 'printf'
 */

#ifndef __PRINTF_H__
#define __PRINTF_H__

#if defined(ARDUINO_ARCH_AVR) || defined(__ARDUINO_X86__) || defined(ARDUINO_ARCH_MEGAAVR)

int serial_putc(char c, FILE*)
{
    Serial.write(c);
    return c;
}

#elif defined(ARDUINO_ARCH_MBED)
REDIRECT_STDOUT_TO(Serial);

#endif // defined (ARDUINO_ARCH_AVR) || defined (__ARDUINO_X86__) || defined (ARDUINO_ARCH_MBED) || defined (ARDUINO_ARCH_MEGAAVR)

void printf_begin(void)
{
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)
    fdevopen(&serial_putc, 0);

#elif defined(__ARDUINO_X86__)
    // For redirect stdout to /dev/ttyGS0 (Serial Monitor port)
    stdout = freopen("/dev/ttyGS0", "w", stdout);
    delay(500);
    printf("Redirecting to Serial...");
#endif // defined(__ARDUINO_X86__)
}

#endif // __PRINTF_H__
