/*
 *
 *  Filename : sendto_hub.cpp
 *
 * This is the client for rpi-hub.cpp or use the RPi as a client to an Arduino as a hub
 * The first address in the pipe is for writing and the second address is for reading
 *
 *
 *  Author : Stanley Seow
 *  e-mail : stanleyseow@gmail.com
 *  date   : 4th Apr 2013
 *
 */

#include <cstdlib>
#include <iostream>
#include "../RF24.h"

using namespace std;

// For best performance, use P1-P5 for writing and Pipe0 for reading as per the hub setting
// Below is the settings from the hub/receiver listening to P0 to P5
//const uint64_t pipes[6] = { 0x7365727631LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL, 0xF0F0F0F0E5LL };
// Example below using pipe2
const uint64_t pipes[2] = { 0xF0F0F0F0E3L, 0x7365727631LL };

// CE and CSN pins On header using GPIO numbering (not pin numbers)
RF24 radio("/dev/spidev0.0",8000000,25);  // Setup for GPIO 25 CSN
uint8_t counter = 0;
char receivePayload[32];


void setup(void) {
	//
	// Refer to RF24.h or nRF24L01 DS for settings
	radio.begin();
	radio.enableDynamicPayloads();
	radio.setAutoAck(1);
	radio.setRetries(15,15);
	radio.setDataRate(RF24_1MBPS);
	radio.setPALevel(RF24_PA_MAX);
	radio.setChannel(76);
	radio.setCRCLength(RF24_CRC_16);

	// Open 6 pipes for readings ( 5 plus pipe0, also can be used for reading )
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);

	//
	// Dump the configuration of the rf unit for debugging
	//

	radio.printDetails();
	printf("\n\rOutput below : \n\r");
	usleep(1000);
}

void loop(void)
{

  int Data1,Data2,Data3,Data4 = 0;
  char temp[5];
  bool timeout=0;

  // Get the last two Bytes as node-id
  uint16_t nodeID = pipes[0] & 0xff;

  // Use the last 2 pipes address as nodeID  
  // sprintf(nodeID,"%X",pipes[0]);
  
  char outBuffer[32]=""; // Clear the outBuffer before every loop
  unsigned long send_time;
  uint8_t rtt = 0;
    
    // Get readings from sensors, change codes below to read sensors
    Data1 = counter++;
    Data2 = rand() % 1000;
    Data3 = rand() % 1000;
    Data4 = rand() % 1000;
    
    if ( counter > 999 ) counter = 0;

    // Append the hex nodeID to the beginning of the payload    
    sprintf(outBuffer,"%2X",nodeID);
    
    strcat(outBuffer,",");
    
    // Convert int to strings and append with zeros if number smaller than 3 digits
    // 000 to 999
    
    sprintf(temp,"%03d",Data1);  
    strcat(outBuffer,temp);
    
    strcat(outBuffer,",");
    
    sprintf(temp,"%03d",Data2);
    strcat(outBuffer,temp);
    
    strcat(outBuffer,",");

    sprintf(temp,"%03d",Data3);
    strcat(outBuffer,temp);
   
    strcat(outBuffer,",");
   
    sprintf(temp,"%03d",Data4);
    strcat(outBuffer,temp); 

    // Test for max payload size
    //strcat(outBuffer,"012345678901");

    
    // End string with 0
    // strcat(outBuffer,0);
            
    printf("outBuffer: %s len: %d\n\r",outBuffer, strlen(outBuffer));
    
    send_time = __millis();
    
    // Stop listening and write to radio 
    radio.stopListening();
    
    // Send to hub
    if ( radio.write( outBuffer, strlen(outBuffer)) ) {
       printf("Send successful\n\r"); 
    }
    else {
       printf("Send failed\n\r");
    }
  
    radio.startListening();
    delay(20);  

  while ( radio.available() && !timeout ) {

         uint8_t len = radio.getDynamicPayloadSize();
         radio.read( receivePayload, len); 
         
         receivePayload[len] = 0;
         printf("inBuffer:  %s\n\r",receivePayload);
         
         // Compare receive payload with outBuffer        
         if ( ! strcmp(outBuffer, receivePayload) ) {
             rtt = __millis() - send_time;
             printf("inBuffer --> rtt: %i \n\r",rtt);       

         }       
    
    // Check for timeout and exit the while loop
    if ( __millis() - send_time > 500 ) {
         printf("Timeout!!!\n\r");
         timeout = 1;
     }          
      
     delay(10);
   } // End while  
     
    delay(250);
    
}


int main(int argc, char** argv) 
{
	setup();
	while(1)
		loop();
	
	return 0;
}


