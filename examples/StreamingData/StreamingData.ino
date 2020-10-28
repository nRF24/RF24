/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty 2bndy5
 */

/**
 * A simple example of streaming data from 1 nRF24L01 transceiver to another.
 *
 * A challenge to learn new skills:
 * This example uses the startFastWrite() function to utilize all 3 levels of
 * the TX FIFO. Try adjusting this example to use the write() function which
 * only uses 1 level of the TX FIFO per call. Notice the difference in
 * transmissions times.
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */
#include <SPI.h>
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair
uint8_t address[6] = "1Node";
// It is very helpful to think of an address as a one-way path instead of as
// an identifying device destination

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX node, flase = RX node

// For this example, we'll be sending 32 payloads each containing
// 32 bytes of data that looks like ASCII art when printed to the serial
// monitor. The TX node and RX node needs only a single 32 byte buffer.
#define SIZE 32
char buffer[SIZE + 1];     // for the RX node
uint8_t counter = 0;       // for counting the number of received payloads
void makePayload(uint8_t); // prototype to construct payload dynamically


void setup() {


  buffer[SIZE] = 0;        // add a NULL terminating charcter (for easy printing)

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("nRF24L01 is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  // print example's introductory prompt
  Serial.println(F("RF24/examples/StreamingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // Fot this example, we use the same address to send data back and forth
  // set the address of the RX node to the TX pipe
  radio.openWritingPipe(address);    // always uses pipe 0
  // set the address of the TX node to an RX pipe
  radio.openReadingPipe(0, address); // using pipe 0

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // powerUp() into TX mode
  } else {
    radio.startListening(); // powerUp() into RX mode
  }
} // setup

void loop() {

  if (role) {
    // This device is a TX node

    uint8_t i = 0;
    uint8_t failures = 0;
    unsigned long start_timer = millis();       // start the timer
    while (i < SIZE) {
      makePayload(i);                           // make the payload
      if (!radio.writeFast(&buffer, SIZE)) {
        failures++;
        radio.reUseTX();
      } else {
        i++;
      }
    }
    unsigned long end_timer = millis();         // end the timer

    Serial.print(F("Time to transmit = "));
    Serial.print(end_timer - start_timer);      // print the timer result
    Serial.print(F(" ms with "));
    Serial.print(failures);                     // print failures detected
    Serial.println(F(" failures detected"));

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    if (radio.available()) {         // is there a payload?
      radio.read(&buffer, SIZE);     // fetch payload from FIFO
      Serial.print(F("Received: "));
      Serial.print(buffer);          // print the payload's value
      Serial.print(F(" - "));
      Serial.println(counter++);     // print the received counter
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      counter = 0; //reset the RX node's counter
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();
      // address for this example doesn't change
      // radio.openWritingPipe(address);

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      // address for this example doesn't change
      // radio.openReadingPipe(0, address);
      radio.startListening();
    }
  }

} // loop

void makePayload(uint8_t i) {
  // Make a single payload based on position in stream.
  // This example employs function to save memory on certain boards.

  // let the first character be an identifying alphanumeric prefix
  // this lets us see which payload didn't get received
  buffer[0] = i + (i < 26 ? 65 : 71);
  for (uint8_t j = 0; j < SIZE - 1; ++j) {
    char chr = j >= (SIZE - 1) / 2 + abs((SIZE - 1) / 2 - i);
    chr |= j <= (SIZE - 1) / 2 - abs((SIZE - 1) / 2 - i);
    buffer[j + 1] = chr + 48;
  }
}