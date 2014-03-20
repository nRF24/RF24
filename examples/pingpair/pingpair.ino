/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
 * connect the role_pin to ground on one.  The ping node sends the current time to the pong node,
 * which responds by sending the value back.  The ping node can then see how long the whole cycle
 * took.
 */

//March 2014 TMRh20 - Updated to utilize High Speed RF24 Library fork

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 9 & 10
RF24 radio(9,10);

// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
const int role_pin = 5;

// Topology
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

void setup(void)
{
  //
  // Role
  //
  pinMode(role_pin, INPUT);          // set up the role pin
  digitalWrite(role_pin,HIGH);  //Change this to HIGH/LOW to pre-choose a role
  delay(20);                         // Just to get a solid reading on the role pin

  if ( ! digitalRead(role_pin) )     // read the address pin, establish our role
    role = role_ping_out;
  else
    role = role_pong_back;

  //
  // Print preamble
  //

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/pingpair/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //

  radio.begin();
  
  radio.setRetries(15,15);                          // optionally, increase the delay between retries & # of retries
  
  radio.setPayloadSize(8);                          // optionally, reduce the payload size.  seems to improve reliability

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

  radio.startListening();                              // Start listening

  radio.printDetails();                                // Dump the configuration of the rf unit for debugging
}

void loop(void)
{
  //
  // Ping out role.  Repeatedly send the current time
  //

  if (role == role_ping_out)
  {    
    radio.stopListening();                              // First, stop listening so we can talk.

    unsigned long time = millis();                      // Take the time, and send it.  This will block until complete
    printf("Now sending %lu...",time);
    bool ok = radio.writeFast( &time, sizeof(unsigned long) );  // NEW command to buffer data more efficiently
    
    if (!ok)
      printf("failed.\n\r");

    while(!radio.txStandBy()){}     //NEW command needs to be called after done sending. Allows FIFO buffers to be filled
    
    radio.startListening();                              // Now, continue listening

    unsigned long started_waiting_at = millis();         // Wait here until we get a response, or timeout (250ms)
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    if ( timeout )                                        // Describe the results
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      unsigned long got_time;                             // Grab the response, compare, and send to debugging spew
      radio.read( &got_time, sizeof(unsigned long) );

      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);        // Spew it
    }

    delay(1000);                                          // Try again 1s later
  }

  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

  if ( role == role_pong_back )
  {
    if ( radio.available() )                               // if there is data ready
    {
      unsigned long got_time;                              // Dump the payloads until we've gotten everything
      bool done = false;
      while (radio.available())
      {
        radio.read( &got_time, sizeof(unsigned long) );    // Fetch the payload, and see if this was the last one.
      }
        printf("Got payload %lu...",got_time);             // Spew it

	// Delay just a little bit to let the other unit
	// make the transition to receiver
	//delay(20);      

      radio.stopListening();                               // First, stop listening so we can talk

      radio.write( &got_time, sizeof(unsigned long) );// Send the final one back.
      printf("Sent response.\n\r");

      radio.startListening();                              // Now, resume listening so we catch the next packets.
    }
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp