/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example of using interrupts
 *
 * This is an example of how to user interrupts to interact with the radio.
 * It builds on the pingpair_pl example, and uses ack payloads.
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

//
// Topology
//

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes in this
// system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the role_pin
//

// The various roles supported by this sketch
typedef enum { role_sender = 1, role_receiver } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Sender", "Receiver"};

// The role of the current running sketch
role_e role;

// Message buffer to allow interrupt handler to print messages
bool message_ready;
char message[100];

// Interrupt handler, check the radio because we got an IRQ
void check_radio(void);

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
    role = role_sender;
  else
    role = role_receiver;

  //
  // Print preamble
  //
  
  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/pingpair_irq/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Attach interrupt handler to interrupt #0 (using pin 2)
  //

  attachInterrupt(0, check_radio, FALLING);

  //
  // Setup and configure rf radio
  //
  
  radio.begin();
  
  // We will be using the Ack Payload feature, so please enable it
  radio.enableAckPayload();

  // Pick a high channel
  radio.setChannel(110);

  //
  // Open pipes to other nodes for communication
  //
  
  // This simple sketch opens a single pipes for these two nodes to communicate
  // back and forth.  One listens on it, the other talks to it.
  
  if ( role == role_sender )
  {
    radio.openWritingPipe(pipe);
  }
  else
  {
    radio.openReadingPipe(1,pipe);
  }

  //
  // Start listening
  //
  
  if ( role == role_receiver )
    radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //
  
  radio.printDetails();
}

static uint32_t message_count = 0;

void loop(void)
{
  
  //
  // Sender role.  Repeatedly send the current time
  //
  
  if (role == role_sender)
  {
    // Take the time, and send it.
    unsigned long time = millis();
    printf("Now sending %lu...",time);
    radio.startWrite( &time, sizeof(unsigned long) );
    
    // Try again soon 
    delay(2000);
  }
  
  //
  // Receiver role.  Receive each packet, dump it out, add ack payload for next time
  //
  
  if ( role == role_receiver )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      static unsigned long got_time;
      boolean done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &got_time, sizeof(unsigned long) );
  
        // Spew it
        printf("Got payload %lu\n",got_time);
      }
      
      // Add an ack packet for the next time around.  This is a simple
      // packet counter
      radio.writeAckPayload( 1, &message_count, sizeof(message_count) );
      ++message_count;
    }
  }

  //
  // Message handler.  Display messages from the interrupt
  //
  if ( message_ready )
  {
    message_ready = false;
    Serial.println(message);
  }
}

void check_radio(void)
{
  // What happened?
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
 
  char *messageptr = message;
  message_ready = true;
  sprintf(message,"Unknown");
  
  if ( tx )
  {
    radio.powerDown();
    sprintf(messageptr,"Send:OK ");
    messageptr += strlen(messageptr);
  }

  if ( fail )
  {
    radio.powerDown();
    sprintf(messageptr,"Send:Failed ");
    messageptr += strlen(messageptr);
  }

  if ( rx )
  {
    radio.read(&message_count,sizeof(message_count));
    sprintf(messageptr,"Ack:%lu ",message_count);
    messageptr += strlen(messageptr);
  }
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
