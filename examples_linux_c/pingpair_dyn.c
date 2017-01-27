/*
	TMRh20 2014 - Optimized RF24 Library Fork
*/

/**
 * Example using Dynamic Payloads
 *
 * This is an example of how to use payloads of a varying (dynamic) size.
 */

//#include <cstdlib>
//#include <iostream>
//#include <sstream>
//#include <string>
#include <stdio.h>
#include <string.h>
#include "./RF24.h"


//using namespace std;
//
// Hardware configuration
// Configure the appropriate pins for your connections

/****************** Raspberry Pi ***********************/

// Radio CE Pin, CSN Pin, SPI Speed
// See http://www.airspayce.com/mikem/bcm2835/group__constants.html#ga63c029bd6500167152db4e57736d0939 and the related enumerations for pin information.

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);

// NEW: Setup for RPi B+
//RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);

// Setup for GPIO 15 CE and CE0 CSN with SPI Speed @ 8Mhz
//RF24 radio;

/*** RPi Alternate ***/
//Note: Specify SPI BUS 0 or 1 instead of CS pin number.
// See http://tmrh20.github.io/RF24/RPi.html for more information on usage

//RPi Alternate, with MRAA
//RF24 radio(15,0);

//RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
//RF24 radio(22,0);


/****************** Linux (BBB,x86,etc) ***********************/

// See http://tmrh20.github.io/RF24/pages.html for more information on usage
// See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV

// Setup for ARM(Linux) devices like BBB using spidev (default is "/dev/spidev1.0" )
//RF24 radio(115,0);

//BBB Alternate, with mraa
// CE pin = (Header P9, Pin 13) = 59 = 13 + 46 
//Note: Specify SPI BUS 0 or 1 instead of CS pin number. 
//RF24 radio(59,0);

/**************************************************************/

// Radio pipe addresses for the 2 nodes to communicate.
const raddr_t pipes[2][5] = { {0xF0,0xF0,0xF0,0xF0,0xE1}, {0xF0,0xF0,0xF0,0xF0,0xD2} };



const int min_payload_size = 4;
const int max_payload_size = 32;
const int payload_size_increments_by = 1;
int next_payload_size = 4;//min_payload_size;

char receive_payload[33/*max_payload_size+1*/]; // +1 to allow room for a terminating NULL char

int main(int argc, char** argv){

  uint8_t role_ping_out = 1, role_pong_back = 0;
  uint8_t role = 0;

  RF24_init(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24/*, BCM2835_SPI_SPEED_8MHZ*/ );

  // Print preamble:
  printf( "RF24/examples/pingpair_dyn/\n");

  // Setup and configure rf radio
  RF24_begin();
  RF24_enableDynamicPayloads();
  RF24_setRetries(5,15);
  RF24_printDetails();


/********* Role chooser ***********/

  printf("\n ************ Role Setup ***********\n");
  char input[40];
  char myChar = 0;
  printf("Choose a role: Enter 0 for receiver, 1 for transmitter (CTRL+C to exit) \n>");
  input[0]=getchar();
  input[1]=0;

  if(strlen(input) == 1) {
	myChar = input[0];
	if(myChar == '0'){
		printf("Role: Pong Back, awaiting transmission \n\n");
	}else{  printf("Role: Ping Out, starting transmission \n\n");
		role = role_ping_out;
	}
  }
/***********************************/

    if ( role == role_ping_out )    {
      RF24_openWritingPipe_d(pipes[0]);
      RF24_openReadingPipe_d(1,pipes[1]);
    } else {
      RF24_openWritingPipe_d(pipes[1]);
      RF24_openReadingPipe_d(1,pipes[0]);
      RF24_startListening();
    }


// forever loop
	while (1)
	{

if (role == role_ping_out)
  {
    // The payload will always be the same, what will change is how much of it we send.
    static char send_payload[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ789012";

    // First, stop listening so we can talk.
    RF24_stopListening();

    // Take the time, and send it.  This will block until complete
    printf("Now sending length %i...",next_payload_size);
    RF24_write(send_payload, next_payload_size );

    // Now, continue listening
    RF24_startListening();

    // Wait here until we get a response, or timeout
    unsigned long started_waiting_at = millis();
    uint8_t timeout = 0;
    while ( ! RF24_available() && ! timeout )
      if (millis() - started_waiting_at > 500 )
        timeout = 1;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      uint8_t len = RF24_getDynamicPayloadSize();
      RF24_read( receive_payload, len );

      // Put a zero at the end for easy printing
      receive_payload[len] = 0;

      // Spew it
      printf("Got response size=%i value=%s\n\r",len,receive_payload);
    }

    // Update size for next time.
    next_payload_size += payload_size_increments_by;
    if ( next_payload_size > max_payload_size )
      next_payload_size = min_payload_size;

    // Try again 1s later
    delay(100);
  }

  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( RF24_available() )
    {
      // Dump the payloads until we've gotten everything
      uint8_t len;

      while (RF24_available())
      {
        // Fetch the payload, and see if this was the last one.
	len = RF24_getDynamicPayloadSize();
	RF24_read( receive_payload, len );

	// Put a zero at the end for easy printing
	receive_payload[len] = 0;

	// Spew it
	printf("Got payload size=%i value=%s\n\r",len,receive_payload);
      }

      // First, stop listening so we can talk
      RF24_stopListening();

      // Send the final one back.
      RF24_write( receive_payload, len );
      printf("Sent response.\n\r");

      // Now, resume listening so we catch the next packets.
      RF24_startListening();
    }
  }
}
}


