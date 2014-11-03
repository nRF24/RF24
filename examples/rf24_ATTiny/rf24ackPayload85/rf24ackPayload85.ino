/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

    rf24ackPayload85.ino by op2op2op2 ( https://github.com/op2op2op2 )
    This is an example of how to use the RF24 class to communicate with ATtiny85 and other node.

    Write this sketch to an ATtiny85. It will act like 'receiver' (RX) mode of GettingStarted.ino.
    It will use ackPayload to send data back to TX node. It sleeps most of the time and when it wakes up
    it reads from TX node, and sends back the ackPayload with the last counting number. 
    (it wakes up, writes ackPayload and, AFTER, start listening).

    Write GettingStarted.ino sketch to UNO (or other board or RPi) and put the node in 'transmit' mode.
    The ATtiny85 will transmit a counting number of runs starting from 1. 
    
    NOTE: in GettingStarted_CallResponse.ino example, you get the ackPayload response of a "previous run"
    (see http://forum.arduino.cc/index.php?topic=178511.msg1872563)
    
    rf24ackPayload85.ino: you will recieve: 1, 2, 3, 4, 5, 6, ... (values from actual run)
        (as GettingStarted_CallResponse TX node's time is not the same as rfackPayload85 sleep time, 
        you will recieve several "Sending failed" strings)
    GettingStarted_CallResponse.ino: you will recieve: "blank response", 1, 2, 3, 4, 5, 6, ... (values from previous run)
    
    For real use, you will have to change COUNTER to: internal temperature, digitalRead, sensors, ...
 
    The ATtiny85 uses the tiny-core by CodingBadly (https://code.google.com/p/arduino-tiny/)
    When direct use of 3v3 does not work (UNO boards have bad 3v3 line) use 5v with LED (1.8V ~ 2.2V drop)
    For low power consumption solutions floating pins (SCK and MOSI) should be pulled high or low with eg. 10K

    ** Hardware configuration **
    See rf24ping95.ino example, ONLY USE 5 pins schema or 4 pins schema (in order to get one more free so you can get a sensor value)
    
    ATtiny25/45/85 Pin map with CSN_PIN 0 => PB4 is free to use for application and you can use ackPayload funtionallity
    
                                                                                            ^^
                                 +-\/-+                                                    //
                           PB5  1|o   |8  Vcc --- nRF24L01  VCC, pin2 -----------------x--|<|-- 5V
    nRF24L01  CE, pin3 --- PB3  2|    |7  PB2 --- nRF24L01  SCK, pin5 --|<|---x-[22k]--|  LED
                   NC      PB4  3|    |6  PB1 --- nRF24L01 MOSI, pin7  1n4148 |
    nRF24L01 GND, pin1 -x- GND  4|    |5  PB0 --- nRF24L01 MISO, pin6         |
                        |        +----+                                       |
                        |-----------------------------------------------||----x-- nRF24L01 CSN, pin4 
                                                                       10nF    
        
    It will work with Arduino UNO an so on, only you need to use startListening(false) not to flush TX buffer.
*/

// CE and CSN are configurable, specified values for ATtiny85 as connected above
#define CE_PIN 3
#define CSN_PIN 0 // // uncomment for ATtiny85 4 pins solution
//#define CSN_PIN 4 // // uncomment for ATtiny85 5 pins solution

#include "RF24.h"

RF24 radio(CE_PIN, CSN_PIN);

byte addresses[][6] = {
  "1Node","2Node"};
byte payload = 0;

void setup() {
  // Setup and configure rf radio
  radio.begin(); // Start up the radio
  radio.enableAckPayload();  
  radio.setPayloadSize(1); 
  radio.setAutoAck(1); // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openReadingPipe(1,addresses[0]); // Read on pipe 0 for device address '1Node'
  //radio.openWritingPipe(addresses[1]); //Not necessary as our node is only RX node.
  //radio.startListening(); // Start listening
}

void loop(void){
  //PowerDown RF24
  radio.powerDown();

  delay(5000); // Change this line with your "low power sleep" best function or library

  //PowerUp RF24
  radio.powerUp();  
  
  radio.stopListening(); // First, stop listening
  radio.flush_tx();  //TX buffer has three possible values, but we need to flush it only to write one value as AckPayload
                     //   If not, after some runs we will fill TX buffer with old values.
  payload++;
  radio.writeAckPayload(1, &payload, sizeof(byte) );
  
  radio.startListening(false); // Now, continue listening WITHOUT flush_tx buffer (We've just write ackPayload)
    
  unsigned long started_waiting_at = micros(); // Set up a timeout period, get the current microseconds
  boolean timeout = false; // Set up a variable to indicate if a response was received or not

  while ( !radio.available() ){ // While nothing is received
    if (micros() - started_waiting_at > 1200000 ){ // Need to wait longer than TX node repeat cylce (1000ms in this case), indicate timeout and exit while loop
      timeout = true;
      break;
    }

  }

  if ( !timeout ){ // Describe the results
    byte got_time; // Grab the response, compare, and send to debugging spew
    radio.read( &got_time, sizeof(byte) );
    //After ATtiny85 reads, RF24 will send ackPayload that we have written
  }


}
