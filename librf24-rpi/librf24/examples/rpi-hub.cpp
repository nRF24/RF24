/* 
 *
 *  Filename : rpi-hub.cpp
 *
 *  This program makes the RPi as a hub listening to all six pipes from the remote 
 *  sensor nodes ( usually Arduino  or RPi ) and will return the packet back to the 
 *  sensor on pipe0 so that the sender can calculate the round trip delays
 *  when the payload matches.
 *  
 *  Refer to RF24/examples/rpi_hub_arduino/ for the corresponding Arduino sketches 
 * to work with this code.
 *  
 *  CE is connected to GPIO25
 *  CSN is connected to GPIO8 
 *
 *  Refer to RPi docs for GPIO numbers
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

// Radio pipe addresses for the 2 nodes to communicate.
// First pipe is for writing, 2nd, 3rd, 4th, 5th & 6th is for reading...
// Pipe0 in bytes is "serv1" for mirf compatibility
const uint64_t pipes[6] = { 0x7365727631LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4, 0xF0F0F0F0E5 };

// CE and CSN pins On header using GPIO numbering (not pin numbers)
RF24 radio("/dev/spidev0.0",8000000,25);  // Setup for GPIO 25 CSN


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
	// Dump the configuration of the rf unit for debugging
	//

	// Start Listening
	radio.startListening();

	radio.printDetails();
	printf("\n\rOutput below : \n\r");
	usleep(1000);
}

void loop(void)
{
	char receivePayload[32];
	uint8_t pipe = 0;
	

	 while ( radio.available( &pipe ) ) {

		uint8_t len = radio.getDynamicPayloadSize();
		radio.read( receivePayload, len );

		// Display it on screen
		printf("Recv: size=%i payload=%s pipe=%i",len,receivePayload,pipe);

		// Send back payload to sender
		radio.stopListening();


		// if pipe is 7, do not send it back
		if ( pipe != 7 ) {
			// Send back using the same pipe
			// radio.openWritingPipe(pipes[pipe]);
			radio.write(receivePayload,len);

			receivePayload[len]=0;
			printf("\t Send: size=%i payload=%s pipe:%i\n\r",len,receivePayload,pipe);
  		} else {
			printf("\n\r");
                }

		// Enable start listening again
		radio.startListening();

	// Increase the pipe outside the while loop
	pipe++;
	// reset pipe to 0
	if ( pipe > 5 ) pipe = 0;
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

