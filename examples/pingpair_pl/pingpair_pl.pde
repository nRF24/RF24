/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
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
 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 8 & 9

RF24 radio(8,9);

// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter 
const short role_pin = 7;

const short led_pin = 13; // flash the led when a packet has been sent

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xE8E8F0F0E1LL, 0xE8E8F0F0D2LL };

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
  
  // set up the role pin
  pinMode(role_pin, INPUT);
  digitalWrite(role_pin,HIGH);
  delay(20); // Just to get a solid reading on the role pin
  
  // read the address pin, establish our role
  if ( digitalRead(role_pin) )
    role = role_ping_out;
  else
    role = role_pong_back;

  //
  // Print preamble
  //
  
  Serial.begin(9600);
  printf_begin();
  printf("\n\rRF24/examples/pingpair_pl/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //
  
  radio.begin();
  
  // We will be using the Ack Payload feature, so please enable it
  radio.enableAckPayload();

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
}

void loop(void)
{
  //
  // Ping out role.  Repeatedly send the current time
  //
  
  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();
    
    // Take the time, and send it.  This will block until complete
    unsigned long time = millis();
    printf("Now sending %lu...",time);
    radio.write( &time, sizeof(unsigned long) );

    if ( radio.isAckPayloadAvailable() )
    {
      static char response[32];
      radio.read(response,32);
      printf("Ack: [%s]",response);

      // try flushing the rx buffer to get the ack packet out of the system ...
      radio.flush_rx();
    }  
    
    // Now, continue listening
    radio.startListening();
    
    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 500 )
        timeout = true;
    
    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Stop listening while we are clocking out the data
      radio.stopListening();

      // Dump the payloads until we've gotten everything
      unsigned long got_time;
      boolean done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );
  
	// Spew it
	printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
      }
      // Begin listening again 
      radio.startListening();
    }
    
    // Try again later
    digitalWrite(led_pin,HIGH);
    delay(3000);
    digitalWrite(led_pin,LOW);
  }
  
  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //
  
  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned long got_time;
      boolean done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );
  
        // Spew it
        printf("Got payload %lu...",got_time);
      }
      
      // First, stop listening so we can talk
      radio.stopListening();
  
      //delay(250);
      
      // necessary to flush the ack packet out
      // but kills the entire tx queue, which I might not
      // want in the future!!
      radio.flush_tx();
            
      // Send the final one back.
      radio.write( &got_time, sizeof(unsigned long) );  
      printf("Sent response.\n\r");
      
      // Now, resume listening so we catch the next packets.
      radio.startListening();
     
      //delay(250);

      // Add an ack packet for the next time around
      static unsigned id = 0;
      static char pl_buffer[10];
      memset(pl_buffer,' ',10);
      pl_buffer[9] = 0;
      snprintf(pl_buffer,10,"id %04x",id++);
      radio.writeAckPayload( 1, pl_buffer, 10 );

    }
  }
}
// vim:ai:cin:sts=2 sw=2 ft=cpp
