/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty 2bndy5
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another.
 *
 * A challenge to learn new skills:
 * This example uses the RF24 library's default settings which includes having
 * dynamic payload length enabled. Try adjusting this example to use
 * statically sized payloads.
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

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX node, flase = RX node

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
float payload = 0.0;

void setup() {

  // print example's introdictory prompt
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // initialize the transceiver on the SPI bus
  radio.begin();

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity of
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

    unsigned long start_timer = millis();                    // start the timer
    bool report = radio.write(&payload, sizeof(float));      // transmit & save the report
    unsigned long end_timer = millis();                      // end the timer

    if (report){
      Serial.print(F("Transmission successful!"));           // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.println(end_timer - start_timer);               // print the timer result
      payload += 0.01;                                       // increment float payload
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {                    // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getDynamicPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);                   // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);                           // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                            // print the pipe number
      Serial.print(F(": "));
      Serial.println(payload);                       // print the payload's value
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
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

  // to make this example readable in the serial monitor
  delay(1000);  // slow it down by 1 second
} // loop