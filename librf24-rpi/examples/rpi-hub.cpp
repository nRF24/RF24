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
 *  RF24 radio(23,24);  // Setup for GPIO 23 CE and 24 CSN
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
RF24 radio("/dev/spidev0.0",8000000,24);  // Setup for GPIO 23 CE and 24 CSN

// Receive payload size


void setup(void)
{
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
	radio.openReadingPipe(2,pipes[2]);
	radio.openReadingPipe(3,pipes[3]);
	radio.openReadingPipe(4,pipes[4]);
	radio.openReadingPipe(5,pipes[5]);

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
	char receivePayload[32];
	uint8_t pipe = 1;
	
	// Start listening
	radio.startListening();

        
	 while ( radio.available(&pipe) ) {

		uint8_t len = radio.getDynamicPayloadSize();
		radio.read( receivePayload, len );

		// Display it on screen
		printf("Recv: size=%i payload=%s pipe=%i",len,receivePayload,pipe);

		// Send back payload to sender
		radio.stopListening();

		// Match for blank and do not re-send it out
		if ( pipe != 7 ) {
			radio.write(receivePayload,len);
			receivePayload[len]=0;
			printf("\t Send: size=%i payload=%s pipe:%i\n\r",len,receivePayload,pipe);
		} else {
			printf("\n\r");
                }
		pipe++;
		if ( pipe > 6 ) pipe = 1;
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

