/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

    rf24ping85.ino by tong67 ( https://github.com/tong67 )
    This is an example of how to use the RF24 class to communicate with ATtiny85 and other node.
    Write this sketch to an ATtiny85. It will act like the 'transmit' mode of GettingStarted.ino
    Write GettingStarted.ino sketch to UNO (or other board or RPi) and put the node in 'receiver' mode.
    The ATtiny85 will transmit a counting number every second starting from 1.
    The ATtiny85 uses the tiny-core by CodingBadly (https://code.google.com/p/arduino-tiny/)
    When direct use of 3v3 does not work (UNO boards have bad 3v3 line) use 5v with LED (1.8V ~ 2.2V drop)


    ** Hardware configuration **
    ATtiny25/45/85 Pin map
    +-\/-+
    Reset/Ain0 (D 5) PB5 1|o |8 Vcc (3v3 or -- LED -- 5v)
    nRF24L01 CE, Pin3 - Ain3 (D 3) PB3 2| |7 PB2 (D 2) Ain1 - nRF24L01 SCK, pin5
    nRF24L01 CSN, Pin4 - Ain2 (D 4) PB4 3| |6 PB1 (D 1) pwm1 - nRF24L01 MOSI, pin7
    GND 4| |5 PB0 (D 0) pwm0 - nRF24L01 MISO, pin6
    CE and CSN are configurable
*/  


#define CE_PIN 3
#define CSN_PIN 4

#include "RF24.h"

RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {
  "1Node","2Node"};
unsigned long payload = 0;

void setup() {
  // Setup and configure rf radio
  radio.begin(); // Start up the radio
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(addresses[0]); // Write to device address '1Node'
  radio.openReadingPipe(1,addresses[1]); // Read on pipe 1 for device address '2Node'
  radio.startListening(); // Start listening
}

void loop(void){
  
  radio.stopListening(); // First, stop listening so we can talk.
  payload++;
  radio.write( &payload, sizeof(unsigned long) );
  radio.startListening(); // Now, continue listening

    unsigned long started_waiting_at = micros(); // Set up a timeout period, get the current microseconds
  boolean timeout = false; // Set up a variable to indicate if a response was received or not

  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 200000 ){ // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }

  }

  if ( !timeout ){ // Describe the results
    unsigned long got_time; // Grab the response, compare, and send to debugging spew
    radio.read( &got_time, sizeof(unsigned long) );
  }

  // Try again 1s later
  delay(1000);
}
