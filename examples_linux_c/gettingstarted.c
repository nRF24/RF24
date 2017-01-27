/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.

 03/17/2013 : Charles-Henri Hallard (http://hallard.me)
              Modified to use with Arduipi board http://hallard.me/arduipi
						  Changed to use modified bcm2835 and RF24 library
TMRh20 2014 - Updated to work with optimized RF24 Arduino library

 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class on RPi, communicating to an Arduino running
 * the GettingStarted sketch.
 */

//#include <cstdlib>
//#include <iostream>
//#include <sstream>
//#include <string>
#include <unistd.h>
#include <RF24/RF24.h>

//
// Hardware configuration
// Configure the appropriate pins for your connections

/****************** Raspberry Pi ***********************/

// Radio CE Pin, CSN Pin, SPI Speed
// See http://www.airspayce.com/mikem/bcm2835/group__constants.html#ga63c029bd6500167152db4e57736d0939 and the related enumerations for pin information.

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);

// NEW: Setup for RPi B+
//RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);

// Setup for GPIO 15 CE and CE0 CSN with SPI Speed @ 8Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

// RPi generic:
//RF24 radio;

/*** RPi Alternate ***/
//Note: Specify SPI BUS 0 or 1 instead of CS pin number.
// See http://tmrh20.github.io/RF24/RPi.html for more information on usage

//RPi Alternate, with MRAA
//RF24 radio(15,0);

//RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
//RF24 radio(22,0);


/****************** Linux (BBB,x86,etc) ***********************/

// See http://tmrh20.github.io/RF24/pages.html for more information on usage
// See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV

// Setup for ARM(Linux) devices like BBB using spidev (default is "/dev/spidev1.0" )
//RF24 radio(115,0);

//BBB Alternate, with mraa
// CE pin = (Header P9, Pin 13) = 59 = 13 + 46 
//Note: Specify SPI BUS 0 or 1 instead of CS pin number. 
//RF24 radio(59,0);

/********** User Config *********/
// Assign a unique identifier for this node, 0 or 1
uint8_t radioNumber = 1;

/********************************/

// Radio pipe addresses for the 2 nodes to communicate.
const uint8_t pipes[][6] = {"1Node","2Node"};


int main(int argc, char** argv){

  uint8_t role_ping_out = 1, role_pong_back = 0;
  uint8_t role = role_pong_back;

  RF24_init(22,0);

  printf("RF24/examples/GettingStarted/\n");

  // Setup and configure rf radio
  RF24_begin();

  // optionally, increase the delay between retries & # of retries
  RF24_setRetries(15,15);
  // Dump the configuration of the rf unit for debugging
  RF24_printDetails();


/********* Role chooser ***********/

  printf("\n ************ Role Setup ***********\n");
  char input[40];
  char myChar = {0};
  printf("Choose a role: Enter 0 for receiver, 1 for transmitter (CTRL+C to exit) \n>");
  input[0]=getchar();
  input[1]=0;

  if(strlen(input) == 1) {
	myChar = input[0];
	if(myChar == '0'){
		printf("Role: Pong Back, awaiting transmission \n\n");
	}else{  printf("Role: Ping Out, starting transmission \n\n");
		role = role_ping_out;
	}
  }
/***********************************/
  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.

    if ( !radioNumber )    {
      RF24_openWritingPipe(pipes[0]);
      RF24_openReadingPipe(1,pipes[1]);
    } else {
      RF24_openWritingPipe(pipes[1]);
      RF24_openReadingPipe(1,pipes[0]);
    }
	
	RF24_startListening();
	
	// forever loop
	while (1)
	{
		if (role == role_ping_out)
		{
			// First, stop listening so we can talk.
			RF24_stopListening();

			// Take the time, and send it.  This will block until complete

			printf("Now sending...\n");
			unsigned long time = millis();

			uint8_t ok = RF24_write( &time, sizeof(unsigned long) );

			if (!ok){
				printf("failed.\n");
			}
			// Now, continue listening
			RF24_startListening();

			// Wait here until we get a response, or timeout (250ms)
			unsigned long started_waiting_at = millis();
			uint8_t timeout = 0;
			while ( ! RF24_available() && ! timeout ) {
				if (millis() - started_waiting_at > 200 )
					timeout = 1;
			}


			// Describe the results
			if ( timeout )
			{
				printf("Failed, response timed out.\n");
			}
			else
			{
				// Grab the response, compare, and send to debugging spew
				unsigned long got_time;
				RF24_read( &got_time, sizeof(unsigned long) );

				// Spew it
				printf("Got response %lu, round-trip delay: %lu\n",got_time,millis()-got_time);
			}
			sleep(1);
		}

		//
		// Pong back role.  Receive each packet, dump it out, and send it back
		//

		if ( role == role_pong_back )
		{
			
			// if there is data ready
			if ( RF24_available() )
			{
				// Dump the payloads until we've gotten everything
				unsigned long got_time;

				// Fetch the payload, and see if this was the last one.
				while(RF24_available()){
					RF24_read( &got_time, sizeof(unsigned long) );
				}
				RF24_stopListening();
				
				RF24_write( &got_time, sizeof(unsigned long) );

				// Now, resume listening so we catch the next packets.
				RF24_startListening();

				// Spew it
				printf("Got payload(%d) %lu...\n",sizeof(unsigned long), got_time);
				
				delay(925); //Delay after payload responded to, minimize RPi CPU time
				
			}
		
		}

	} // forever loop

  return 0;
}

