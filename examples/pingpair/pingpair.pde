/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Pair
 *
 * This sketch is an example of using the RF24 library for Arduino.  Deploy this on
 * two nodes, set one as the 'trasmit' and the other the 'receive' unit.  The transmit
 * unit will send out the value of millis() once a second.  The receive unit will respond
 * back with a copy of the value.  The transmit unit can get that 'ping' back, and
 * determine how long the whole cycle took.
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

// sets the address (and therefore the role of operation) of this unit.
// lo = node0, hi = node1
const int addr_pin = 7;

// The actual value of the node's address will be filled in by the sketch
// when it reads the addr_pin
int node_address;

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up address & role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the addr_pin.  Set it low for address #0, high for #1.
//

// The various roles supported by this sketch
typedef enum { role_rx = 1, role_tx1, role_end } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Receive", "Transmit"};

// Which role is assumed by each of the possible hardware addresses
const role_e role_map[2] = { role_rx, role_tx1 };

// The role of the current running sketch
role_e role;

void setup(void)
{
  //
  // Address & Role
  //
  
  // set up the address pin
  pinMode(addr_pin, INPUT);
  digitalWrite(addr_pin,HIGH);
  delay(20); // Just to get a solid reading on the addr pin
  
  // read the address pin, establish our address and role
  node_address = digitalRead(addr_pin) ? 0 : 1;
  role = role_map[node_address];

  //
  // Print preamble
  //
  
  Serial.begin(9600);
  printf_begin();
  printf("\n\rRF24 pingpair example\n\r");
  printf("ADDRESS: %x\n\r",node_address);
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //
  
  radio.begin();

  // Set channel (optional)
  radio.setChannel(1);
  
  // Set size of payload (optional, but recommended)
  // The library uses a fixed-size payload, so if you don't set one, it will pick
  // one for you!
  radio.setPayloadSize(sizeof(unsigned long));
    
  //
  // Open pipes to other nodes for communication (required)
  //
  
  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  
  // We will open 'our' pipe for writing
  radio.openWritingPipe(pipes[node_address]);
  
  // We open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)
  int other_node_address;
  if (node_address == 0)
    other_node_address = 1;
  else
    other_node_address = 0;
  radio.openReadingPipe(1,pipes[other_node_address]);
  
  //
  // Start listening
  //
  
  radio.startListening();
  
  //
  // Dump the configuration of the rf unit for debugging
  //
  
  radio.print_details();
}

void loop(void)
{
  //
  // Transmitter role.  Repeatedly send the current time
  //
  
  if (role == role_tx1)
  {
    // First, stop listening so we can talk.
    radio.stopListening();
    
    // Take the time, and send it.  This will block until complete
    unsigned long time = millis();
    printf("Now sending %lu...",time);
    bool ok = radio.write( &time );  
    
    // Now, continue listening
    radio.startListening();
    
    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 250 )
        timeout = true;
    
    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time );
  
      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }
    
    // Try again 1s later
    delay(1000);
  }
  
  //
  // Receiver role.  Receive each packet, dump it out, and send it back to the transmitter
  //
  
  if ( role == role_rx )
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
        done = radio.read( &got_time );
  
        // Spew it
        printf("Got payload %lu...",got_time);
      }
      
      // First, stop listening so we can talk
      radio.stopListening();
            
      // Send the final one back.
      radio.write( &got_time );  
      printf("Sent response.\n\r");
      
      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }
}
