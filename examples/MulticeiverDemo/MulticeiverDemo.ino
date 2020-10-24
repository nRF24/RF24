/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty 2bndy5
 */

/**
 * A simple example of sending data from as many as 6 nRF24L01 transceivers to
 * 1 receiving transceiver. This technique is trademarked by
 * Nordic Semiconductors as "MultiCeiver".
 *
 * A challenge to learn new skills:
 * This example uses the Serial Monitor to change a node's role. Try adjusting
 * this example so that the 1 recieving node sends a ping that tells
 * all other transmitting nodes to start transmitting. HINT: use the
 * "multicast" parameter to write().
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */
#include <SPI.h>
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// For this example, we'll be using 6 addresses; 1 for each TX node
// It helps to think of addresses as paths instead of destinations.
// Notice that the last byte is the only byte that changes in the last 5
// addresses. This is a limitation of the nRF24L01 transceiver for pipes 2-5
// because they use the same first 4 bytes from pipe 1.
uint64_t address[6] = { 0x7878787878LL,
                        0xB3B4B5B6F1LL,
                        0xB3B4B5B6CDLL,
                        0xB3B4B5B6A3LL,
                        0xB3B4B5B60FLL,
                        0xB3B4B5B605LL };


// Because this example allow up to 6 nodes (specified by numbers 0-5) to
// transmit and only 1 node to receive, we will use a negative value in our
// role variable to signify this node is a receiver.
// Used to control whether this node is sending or receiving
int8_t role = -1;  // 0-5 = TX node; any negative number = RX node

// For this example, we'll be using a payload containing
// a node ID number and a single integer number that will be incremented
// on every successful transmission.
// Make a data structure to use as a payload.
struct PayloadStruct {
    uint8_t nodeID;
    uint8_t payloadID = 0;
};
PayloadStruct payload;

// This example uses all 6 pipes to receive while TX nodes only use 2 pipes
// To make this easier we'll use a function to manage the addresses, and the
// payload's nodeID
void setRole(); // declare a prototype; definition is found after the loop()

void setup() {

  // print example's introductory prompt
  Serial.begin(115200);
  Serial.println(F("RF24/examples/MulticeiverDemo"));
  Serial.println(F("*** PRESS a number between 0 and 5 (inclusive) to act as a unique node that transmits to the RX node"));

  // initialize the transceiver on the SPI bus
  radio.begin();

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity of
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // Set the pipe addresses accordingly. This function additionally also
  // calls startListening() or stopListening() and sets the payload's nodeID
  setRole();
}

void loop() {

  if (role <= 0) {
    // This device is a TX node

    unsigned long start_timer = millis();                    // start the timer
    bool report = radio.write(&payload, sizeof(float));      // transmit & save the report
    unsigned long end_timer = millis();                      // end the timer

    if (report){
      Serial.print(F("Transmission successful!"));           // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.println(end_timer - start_timer);               // print the timer result
      payload.payloadID++;                                   // increment payload number
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else if (role < 0) {
    // This device is the RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {                    // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getDynamicPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);                   // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);                           // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                            // print the pipe number
      Serial.print(F(" from node "));
      Serial.print(payload.nodeID);                  // print the payload's origin
      Serial.print(F(". PayloadID: "));
      Serial.println(payload.payloadID);             // print the payload's number
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = Serial.parseInt();
    if ((c >= 0 || c <= 5) && role < 0) {
      // Become a TX node with identifier 'c'

      role = c;
      Serial.print(F("*** CHANGING ROLE TO NODE "));
      Serial.print(c);
      Serial.println(F(" ***"));
      setRole(); // change address on pipe 0 to the RX node

    } else if (c < 0  && role > 0) {
      // Become the RX node

      role = c;
      Serial.println(F("*** CHANGING ROLE TO RECEIVER ***"));
      setRole(); // change address on all pipes to TX nodes
    }
  }

} // loop

void setRole() {
  if (role < 0) {
    // For the RX node

    // Set the addresses for all pipes to TX nodes
    for (uint8_t i = 0; i < 6; ++i) {
      radio.openReadingPipe(i, address[i]);
    }
    radio.startListening(); // put radio in RX mode

  } else {
    // For the TX node

    // set the payload's nodeID & reset the payload's identifying number
    payload.nodeID = role;
    payload.payloadID = 0;

    // Set the address on pipe 0 to the RX node.
    radio.stopListening(); // put radio in TX mode
    radio.openWritingPipe(address[role]);

    // According to the datasheet, the auto-retry features's delay value should
    // be "skewed" to allow the RX node to receive 1 transmission at a time.
    // So, use varying delay between retry attempts and 15 (at most) retry attempts
    radio.setRetries(((role * 3) % 12) + 3, 15); // maximum value is 15 for both args
  }
}