/*
TMRh20 2014

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/** General Data Transfer Rate Test
 * This example demonstrates basic data transfer functionality with the 
 updated library. This example will display the transfer rates acheived using
 the slower form of high-speed transfer using blocking-writes.
 */



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

// Role management
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  

// The various roles supported by this sketch
typedef enum { role_TX = 1, role_RX } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

//Set this to determine the default role of the current running sketch
role_e role = role_RX;

//Data buffer for testing data transfer speeds
byte data[32]; 

//Counter and timer for keeping track transfer info
unsigned long counter, rxTimer;
float startTime, stopTime;  

void setup(void)
{

  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  radio.begin();                          // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setAutoAck(1);  // Ensure autoACK is enabled
  radio.setRetries(2,3);                // Optionally, increase the delay between retries & # of retries
  //radio.disableCRC();
  radio.setCRCLength(RF24_CRC_8); 
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);

  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
  randomSeed(analogRead(0));              //Seed for random number generation
  
  for(int i=0; i<32; i++){
     data[i] = random(255);               //Load the buffer with random data
  }
  radio.powerUp();
}

void loop(void){

  
  //TX with pre-blocking writes
  if(role == role_TX){
    
    delay(1500);
    
    printf("Initiating Basic Data Transfer\n\r");
    
    
    float cycles = 10000;
    
    startTime = millis();
            
    for(int i=0; i<cycles; i++){
      if(!radio.writeFast(&data,32)){
        counter++;
      }
    }
    stopTime = millis();
     
   while(!radio.txStandBy()){ }
   
   float numBytes = cycles * 32;
   float rate = numBytes / (stopTime - startTime) / cycles;

    
    printf("Transfer complete at "); Serial.print(rate); printf(" KB/s \n\r");
    printf("%d of ",counter); Serial.print(cycles); printf(" Packets Failed to Send\n\r");
    counter = 0;   
    



   }
  
  
  
  if(role == role_RX){
     while(radio.available()){       
      radio.read(&data,32);
      counter++;
     }
   if(millis() - rxTimer > 1000){
     rxTimer = millis();
//     printf("Rx Rate: ");
//     Serial.print(counter*32/1000);
//     printf(" KB/s\n\r"); 
     printf("Payload Count: %d \n\r", counter);
     counter = 0;
   }
    
  }

  //
  // Change roles
  //

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_RX )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");
      radio.stopListening();
      role = role_TX;                  // Become the primary transmitter (ping out)
      //radio.openWritingPipe(pipes[0]);
      //radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_TX )
    {
      radio.startListening();
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");
      
       role = role_RX;                // Become the primary receiver (pong back)
       
      //radio.openWritingPipe(pipes[1]);
      //radio.openReadingPipe(1,pipes[0]);
    }
  }
}
// vim:cin:ai:sts=2 sw=2 ft=cpp
