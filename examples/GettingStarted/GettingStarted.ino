/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example for Getting Started with nRF24L01+ radios. 
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two 
 * different nodes.  Put one of the nodes into 'transmit' mode by connecting 
 * with the serial monitor and sending a 'T'.  The ping node sends the current 
 * time to the pong node, which responds by sending the value back.  The ping 
 * node can then see how long the whole cycle took.
 */

//March 2014 - TMRh20 - Updated to utilize High Speed RF24 Library fork
//This 


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration
// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 

RF24 radio(48,49);

// Topology
// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

//
// Role management
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

void setup(void)
{
  //
  // Print preamble
  //

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  //
  // Setup and configure rf radio

  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled

  radio.setRetries(15,15);                // Optionally, increase the delay between retries & # of retries

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);

  radio.startListening();                 // Start listening

  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop(void)
{
  //
  // Ping out role.  Repeatedly send the current time
  //

  if (role == role_ping_out)
  {
    
    radio.stopListening();                                  // First, stop listening so we can talk.
    
    unsigned long time = millis();                          // Take the time, and send it.  This will block until complete
    printf("Now sending %lu...",time);
    bool ok = radio.writeFast( &time, sizeof(unsigned long) );//New function for proper use of FIFO buffers
    while( ! radio.txStandBy() ){}                          //Called when STANDBY-I mode is engaged (User is finished sending)
    if (!ok)
      printf("failed.\n\r");
    
    
    radio.startListening();                                 // Now, continue listening
    
    unsigned long started_waiting_at = millis();            // Wait here until we get a response, or timeout (250ms)
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;
        
    if ( timeout )                                          // Describe the results
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      unsigned long got_time;                               // Grab the response, compare, and send to debugging spew
      radio.read( &got_time, sizeof(unsigned long) );
      unsigned long tim = millis();
      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,tim-got_time);
    }

    // Try again 1s later
    delay(1000);
  }

  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

  if ( role == role_pong_back )
  {
    if( radio.available()){
      unsigned long got_time;                                       // Dump the payloads until we've gotten everything
      bool done = false;
      while (radio.available()) {                                   // While there is data ready
        // Fetch the payload, and see if this was the last one.
        radio.read( &got_time, sizeof(unsigned long) );
      }    
        // Spew it
        //printf("Got payload %lu...",got_time);

	// Delay just a little bit to let the other unit
	// make the transition to receiver
	//delay(2);
     
      radio.stopListening();                                          // First, stop listening so we can talk
     
      radio.write( &got_time, sizeof(unsigned long) );                // Send the final one back.      
      
      radio.startListening();                                         // Now, resume listening so we catch the next packets.
      
      //printf("Sent response.\n\r");
    
   }
 }

  //
  // Change roles
  //

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");

      role = role_ping_out;                  // Become the primary transmitter (ping out)
      //radio.openWritingPipe(pipes[0]);
      //radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      
       role = role_pong_back;                // Become the primary receiver (pong back)
      //radio.openWritingPipe(pipes[1]);
      //radio.openReadingPipe(1,pipes[0]);
    }
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp