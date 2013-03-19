/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Channel scanner
 *
 * Example to detect interference on the various channels available.
 * This is a good diagnostic tool to check whether you're picking a
 * good channel for your application.
 *
 * Inspired by cpixip.
 * See http://arduino.cc/forum/index.php/topic,54795.0.html
 */

#include <cstdlib>
#include <iostream>
#include "../RF24.h"

using namespace std;

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

// CE and CSN pins 
//RF24 radio(8, 25);  //only CSN is NEEDED in RPI
RF24 radio("/dev/spidev0.0",8000000 , 25);  //spi device, speed and CSN,only CSN is NEEDED in RPI

//
// Channel info
//

//const uint8_t num_channels = 128;
const uint8_t num_channels = 120;
uint8_t values[num_channels];

//
// Setup
//

void setup(void)
{
  //
  // Print preamble
  //

  //Serial.begin(57600);
  //printf_begin();
  printf("\n\rRF24/examples/scanner/\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();
  radio.setAutoAck(false);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  radio.printDetails();

  // Print out header, high then low digit
  int i = 0;
  while ( i < num_channels )
  {
    printf("%x",i>>4);
    ++i;
  }
  printf("\n\r");
  i = 0;
  while ( i < num_channels )
  {
    printf("%x",i&0xf);
    ++i;
  }
  printf("\n\r");

}

//
// Loop
//
/*
const int num_reps = 100;

void loop2(void)
{
  // Clear measurement values
  memset(values,0,sizeof(values));

  // Scan all channels num_reps times
  int rep_counter = num_reps;
  while (rep_counter--)
  {
    int i = num_channels;
    while (i--)
    {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(128);
      radio.stopListening();

      // Did we get a carrier?
      if ( radio.testCarrier() )
        ++values[i];
    }
  }

  // Print out channel measurements, clamped to a single hex digit
  int i = 0;
  while ( i < num_channels )
  {
    printf("%x",min(0xf,values[i]&0xf));
    ++i;
  }
  printf("\n\r");
}
*/
//
// Loop
//

const int num_reps = 100;

int reset_array=0;

void loop(void)
{

if ( reset_array == 1 ) {	
  // Clear measurement values
  memset(values,0,sizeof(values));
  printf("\n\r");
}

  // Scan all channels num_reps times
    int i = num_channels;
    while (i--)
    {
      // Select this channel
      radio.setChannel(i);

      // Listen for a little
      radio.startListening();
      delayMicroseconds(128);
      radio.stopListening();

      // Did we get a carrier?
      if ( radio.testCarrier() )
        ++values[i];
	if ( values[i] == 0xf ) {
		reset_array = 2;
	}
    }

  // Print out channel measurements, clamped to a single hex digit
  i = 0;
  while ( i < num_channels )
  {
    printf("%x",min(0xf,values[i]&0xf));
    ++i;
  }
  printf("\n\r");
}

int main(int argc, char** argv)
{
        setup();
        while(1)
                loop();

        return 0;
}



// vim:ai:cin:sts=2 sw=2 ft=cpp
