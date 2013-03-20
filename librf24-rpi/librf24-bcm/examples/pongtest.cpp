/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 
 03/17/2013 : Charles-Henri Hallard (http://hallard.me)
              Modified to use with Arduipi board http://hallard.me/arduipi
						  Changed to use modified bcm2835 and RF24 library 

 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
 * connect the role_pin to ground on one.  The ping node sends the current time to the pong node,
 * which responds by sending the value back.  The ping node can then see how long the whole cycle
 * took.
 */

#include <cstdlib>
#include <iostream>
#include "./RF24.h"

//
// Hardware configuration
//

// CE Pin, CSN Pin, SPI Speed

// Setup for GPIO 22 CE and GPIO 25 CSN with SPI Speed @ 1Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_18, BCM2835_SPI_SPEED_1MHZ);

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ); 

// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_26, BCM2835_SPI_SPEED_8MHZ);  


// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
const int role_pin = 7;

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the role_pin
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role;


int main(int argc, char** argv)
{
  // Role
  role = role_pong_back;

  //
  // Print preamble:
  //

  //Serial.begin(115200);
  //printf_begin();
  printf("RF24/examples/pongtest/\n");
  printf("ROLE: %s\n",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //
  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
	//  radio.setPayloadSize(8);
	radio.setChannel(0x4c);
  radio.setPALevel(RF24_PA_LOW);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)
  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //
  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //
  radio.printDetails();
  //
  // Ping out role.  Repeatedly send the current time
  //
	
	// forever loop
	while (1)
	{
		if (role == role_ping_out)
		{
			// First, stop listening so we can talk.
			radio.stopListening();

			// Take the time, and send it.  This will block until complete
			unsigned long time = millis();
			printf("Now sending %lu...",time);
			bool ok = radio.write( &time, sizeof(unsigned long) );
			
			if (ok)
				printf("ok...");
			else
				printf("failed.\n");

			// Now, continue listening
			radio.startListening();

			// Wait here until we get a response, or timeout (250ms)
			unsigned long started_waiting_at = millis();
			bool timeout = false;
			while ( ! radio.available() && ! timeout ) {
					// by bcatalin » Thu Feb 14, 2013 11:26 am
					delay(5); //add a small delay to let radio.available to check payload
				if (millis() - started_waiting_at > 200 )
					timeout = true;
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
				radio.read( &got_time, sizeof(unsigned long) );

				// Spew it
				printf("Got response %lu, round-trip delay: %lu\n",got_time,millis()-got_time);
			}

			// Try again 1s later
			//    delay(1000);
			sleep(1);
			
		}

		//
		// Pong back role.  Receive each packet, dump it out, and send it back
		//

		if ( role == role_pong_back )
		{
			// if there is data ready
			//printf("Check available...\n");
			if ( radio.available() )
			{
				// Dump the payloads until we've gotten everything
				unsigned long got_time;
				bool done = false;
				
				while (!done)
				{
					// Fetch the payload, and see if this was the last one.
					done = radio.read( &got_time, sizeof(unsigned long) );

					// Spew it
					printf("Got payload(%d) %lu...\n",sizeof(unsigned long), got_time);

					// Delay just a little bit to let the other unit
					// make the transition to receiver
					delay(20);
				}

				// First, stop listening so we can talk
				radio.stopListening();

				// Send the final one back.
				radio.write( &got_time, sizeof(unsigned long) );

				// Now, resume listening so we catch the next packets.
				radio.startListening();
			}
		}
	} // forever loop

  return 0;
}

// vim:cin:ai:sts=2 sw=2 ft=cpp
