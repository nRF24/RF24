/* 
 * File:   main.cpp
 * Author: purinda
 * 
 * This file has to be compiled and uploaded to the Beaglebone
 * the role of the application is to ping the arduino module
 * file the arduino sketch in 
 *
 * Created on 24 June 2012, 10:54 AM
 */

#include <cstdlib>
#include <iostream>
//#include "lib/RF24/RF24.h"
#include "../librf24/RF24.h"
//#include "lib/RF24/compatibility.h"

using namespace std;


// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the role_pin
//

// The various roles supported by this sketch
 typedef enum { role_ping_out = 1, role_pong_back } role_e;
//typedef enum { role_ping_out , role_pong_back=1 } role_e;

//
// Payload
//

const int min_payload_size = 4;
const int max_payload_size = 32;
const int payload_size_increments_by = 2;
int next_payload_size = min_payload_size;

char receive_payload[max_payload_size+1]; // +1 to allow room for a terminating NULL char

// CE and CSN pins On header P9 (P3.21 and P3.19)
//RF24 radio(8, 25);  //only CSN is NEEDED in RPI
RF24 radio("/dev/spidev0.0",8000000 , 25);  //spi device, speed and CSN,only CSN is NEEDED in RPI



void setup(void)
{
	//
	radio.begin();
//	radio.enableDynamicPayloads();
//	radio.setRetries(15,15);
//	radio.setDataRate(RF24_1MBPS);
	radio.setPALevel(RF24_PA_LOW);
	radio.setChannel(0x4c);
//	radio.setCRCLength(RF24_CRC_16);
//	radio.setPayloadSize(8);

	radio.openWritingPipe(pipes[0]);
	radio.openReadingPipe(1,pipes[1]);

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
	//
	// Ping out.
	//
	// The payload will always be the same, what will change is how much of it we send.
	static char send_payload[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ789012";

	// First, stop listening so we can talk.
	radio.stopListening();

	// Take the time, and send it.  This will block until complete
	printf("Now sending length %i...",next_payload_size);
	radio.write( send_payload, next_payload_size );

	// Now, continue listening
	radio.startListening();

	// Wait here until we get a response, or timeout
	long started_waiting_at = __millis();

	bool timeout = false;
	while ( ! radio.available() && ! timeout )
		if (__millis() - started_waiting_at > 1000 )
			timeout = true;

	// Describe the results
	if ( timeout )
	{
		printf("Failed, response timed out.\n\r");
}
	else
//	if ( radio.available() )
	{
		// Grab the response, compare, and send to debugging spew
		uint8_t len = radio.getDynamicPayloadSize();
		radio.read( receive_payload, len );

		// Put a zero at the end for easy printing
		receive_payload[len] = 0;

		// Spew it
		printf("Got response size=%i value=%s\n\r",len,receive_payload);
	}

	// Update size for next time.
	next_payload_size += payload_size_increments_by;
	if ( next_payload_size > max_payload_size )
		next_payload_size = min_payload_size;

	sleep(1);

}


int main(int argc, char** argv) 
{
	setup();
	while(1)
		loop();
	
	return 0;
}

