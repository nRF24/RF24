/**
   Example for efficient call-response using ack-payloads

   This example continues to make use of all the normal functionality of the radios including
   the auto-ack and auto-retry features, but allows ack-payloads to be written optionally as well.
   This allows very fast call-response communication, with the responding radio never having to
   switch out of Primary Receiver mode to send back a payload, but having the option to if wanting
   to initiate communication instead of respond to a commmunication.
*/
/*
  // March 2014 - TMRh20 - Updated along with High Speed RF24 Library fork
  // Parts derived from examples by J. Coliz <maniacbug@ymail.com>
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


// Hardware configuration
RF24 radio(7, 8);  // Set up nRF24L01 radio on SPI bus plus pins 7 & 8

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = {0xABCDABCD71LL, 0x544d52687CLL};

// Role management: Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.

typedef enum {role_ping_out = 1, role_pong_back} role_e;                  // The various roles supported by this sketch
const char* role_friendly_name[] = {"invalid", "Ping out", "Pong back"};  // The debug-friendly names of those roles
role_e role = role_pong_back;                                             // The role of the current running sketch

byte counter = 1;                                                         // A single byte to keep track of the data being sent back and forth

void setup(){
  Serial.begin(115200);
  printf_begin();                         // needed for printDetails()
  Serial.print(F("\n\rRF24/examples/pingpair_ack/\n\rROLE: "));
  Serial.println(role_friendly_name[role]);
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Setup and configure rf radio

  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.enableDynamicPayloads();          // needed for using ACK payloads
  radio.setRetries(0, 15);                // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
}

void loop(void){


  /****************** Ping Out Role ***************************/

  if (role == role_ping_out){
    radio.stopListening();                             // First, stop listening so we can talk.

    Serial.print(F("Now sending ");
    Serial.print(counter);
    Serial.println(F(" as payload."));
    byte gotByte;
    unsigned long start_time = micros();               // Take the time, and send it.  This will block until complete

    //Called when STANDBY-I mode is engaged (User is finished sending)
    if (!radio.write(&counter, 1)){
      Serial.println(F("failed."));
    }else{
      if (!radio.available()){
        Serial.println(F("Blank Payload Received."));
      }else{
        while (radio.available()){
          unsigned long end_time = micros();
          radio.read(&gotByte, 1);
          Serial.print(F("Got response "));
          Serial.print(gotByte);
          Serial.print(F(", round-trip delay: "));
          Serial.print(end_time - start_time);
          Serial.println(F(" microseconds"));
          counter++;
        }
      }
    }

    delay(1000);                                       // Try again later
  }


  /****************** Pong Back Role ***************************/
  // Receive each packet, send it back, dump it out

  if (role == role_pong_back){
    byte pipeNo;
    byte gotByte;

    // Dump the payloads until we've gotten everything
    while (radio.available(&pipeNo)){
      radio.read(&gotByte, 1);
      radio.writeAckPayload(pipeNo, &gotByte, 1);
      Serial.print(F("Received message and replied at "));
      Serial.println(millis());
    }
  }


  /****************** Change Roles via Serial Commands ***************************/

  if (Serial.available()){
    char c = toupper(Serial.read());
    if (c == 'T' && role == role_pong_back){
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));

      role = role_ping_out;                  // Become the primary transmitter (ping out)
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1, pipes[1]);
    }else if (c == 'R' && role == role_ping_out){
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));

      role = role_pong_back;                 // Become the primary receiver (pong back)
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1, pipes[0]);
      radio.startListening();
    }
  }
} // loop
