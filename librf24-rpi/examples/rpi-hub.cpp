/* 
 * File:   main.cpp
 * Author: purinda
 * 
 * 
 * This file has to be compiled and uploaded to the Beaglebone
 * the role of the application is to ping the arduino module
 * file the arduino sketch in 
 *
 * Created on 24 June 2012, 10:54 AM
 *  Date : 2/2/2013
 *
 *  Modified by : Stanley to work with Arduino using the following
 *  CE/SS and CSN pins on header using GPIO numbering (not pin numbers)
 *  
 *  RF24 radio("/dev/spidev0.0",8000000,24);  // Setup for GPIO 24 CSN
 *  Refer to RPi docs for GPIO numbers
 *  Author : Stanley Seow
 *  e-mail : stanleyseow@gmail.com
 */

#include <cstdlib>
#include <iostream>
#include "../librf24/RF24.h"
#include "../librf24/compatibility.h"

using namespace std;

// Radio pipe addresses for the 2 nodes to communicate.
// First pipe is for writing, 2nd, 3rd, 4th, 5th & 6th is for reading...
const uint64_t pipes[6] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0F1, 0xF0F0F0F0F2 };

// CE and CSN pins On header using GPIO numbering (not pin numbers)
RF24 radio("/dev/spidev0.0",8000000,24);  // Setup for GPIO 24 CSN


void setup(void)
{
	//
	// Refer to RF24.h or nRF24L01 DS for settings
	radio.begin();
	// Enable AutoAck, was disable by default
	radio.setAutoAck(1);
	radio.enableDynamicPayloads();
	radio.setRetries(15,15);
	radio.setDataRate(RF24_1MBPS);
	radio.setPALevel(RF24_PA_MAX);
	radio.setChannel(76);
	radio.setCRCLength(RF24_CRC_16);

	// Open 6 pipes for readings ( 5 plus pipe0, also can be used for reading )
	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);
	radio.openReadingPipe(2,pipes[2]);
	radio.openReadingPipe(3,pipes[3]);
	radio.openReadingPipe(4,pipes[4]);
	radio.openReadingPipe(5,pipes[5]);

	//
	// Start listening
	//

	radio.startListening();
	radio.stopListening();

	//
	// Dump the configuration of the rf unit for debugging
	//

	radio.printDetails();
}

void loop(void)
{
	
	// Receive payload size
	char receivePayload[32]="";

	uint8_t len = 0;
	uint8_t pipe = 1;

	// Start listening
	radio.startListening();
       
	// Reset pipes to 1, valid pipes for reading is 1 to 5 only 

	for (pipe=1;pipe<6;pipe++) {
	   while ( radio.available( &pipe ) ) { 
	   //while ( radio.available() ) {

		len = radio.getDynamicPayloadSize();
		radio.read( receivePayload, len );
		printf("Recv: size=%i payload=%s\n\r",len,receivePayload);

		radio.stopListening();
		if (pipe!=7) {
		radio.write(receivePayload,len);
		radio.write(receivePayload,len);
		radio.write(receivePayload,len);
		radio.write(receivePayload,len);
		radio.write(receivePayload,len);
		printf("\tSend: size=%i payload=%s pipes:%i\n\r",len,receivePayload,pipe);
		}

		// Put 0 to string before printing		
		//receivePayload[len] = 0;

	   }
	}

	usleep(20);
}


int main(int argc, char** argv) 
{
	setup();
	while(1)
		loop();
	
	return 0;
}

