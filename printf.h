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

#if defined (ARDUINO) && !defined (__arm__) && !defined(__ARDUINO_X86__)

int serial_putc( char c, FILE * )
{
  Serial.write( c );

  return c;
}

void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

#elif defined (__arm__)

void printf_begin(void){}

#elif defined(__ARDUINO_X86__)
int serial_putc( char c, FILE * )
{
  Serial.write( c );

  return c;
}

void printf_begin(void)
{
  //JESUS - For reddirect stdout to /dev/ttyGS0 (Serial Monitor port)
  stdout = freopen("/dev/ttyGS0","w",stdout);
  delay(500);
  printf("redirecting to Serial...");
  
  //JESUS -----------------------------------------------------------
}
#else
#error This example is only for use on Arduino.
#endif // ARDUINO

#endif // __PRINTF_H__
