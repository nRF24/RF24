/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another
 * with Acknowledgement (ACK) payloads attached to ACK packets.
 *
 * A challenge to learn new skills:
 * This example uses the nRF24L01's ACK payloads feature. Try adjusting this
 * example to use a different RX pipe for that still responds with ACK
 * payloads.
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
// a string & an integer number that will be incremented
// on every successful transmission.
// Make a data structure to store the entire payload of different datatypes
struct PayloadStruct{
  char message[7];          // only using 6 characters for TX & ACK payloads
  uint8_t counter;
};
PayloadStruct payload;

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("nRF24L01 is not responding!!"));
    while(1) {} // hold in infinite loop
  }

  // print example's introductory prompt
  Serial.println(F("RF24/examples/AcknowledgementPayloads"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity of
  // each other.
  radio.setPALevel(RF24_PA_LOW);     // RF24_PA_MAX is default.

  // Acknowledgement packets have no payloads by default. We need to enable
  // this feature for all nodes (TX & RX) to use ACK payloads.
  radio.enableAckPayload();

  // Fot this example, we use the same address to send data back and forth
  // set the address of the RX node to the TX pipe
  radio.openWritingPipe(address);     // always uses pipe 0
  // set the address of the TX node to an RX pipe
  radio.openReadingPipe(0, address);  // using pipe 0

  // additional setup specific to the node's role
  if (role) {
    // setup the TX payload

    memcpy(payload.message, "Hello ", 6);                       // set the payload message
    radio.stopListening();                                      // powerUp() into TX mode
  } else {
    // setup the ACK payload & load the first response into the FIFO

    memcpy(payload.message, "World ", 6);                       // set the payload message
    // load the payload for the first received transmission on pipe 0
    radio.writeAckPayload(0, &payload, sizeof(PayloadStruct));

    radio.startListening();                                     // powerUp() into RX mode
  }
}

void loop() {

  if (role) {
    // This device is a TX node

    unsigned long start_timer = micros();                       // start the timer
    bool report = radio.write(&payload, sizeof(PayloadStruct)); // transmit & save the report
    unsigned long end_timer = micros();                         // end the timer

    if (report){
      Serial.print(F("Transmission successful!"));              // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.println(end_timer - start_timer);                  // print the timer result
      Serial.print(F("us. Sent: "));
      Serial.print(payload.message);                            // print the payload message
      Serial.print(payload.counter);                            // print the payload counter
      if (radio.available()) {                                  // is there an ACK payload?
        PayloadStruct ack;
        radio.read(&ack, sizeof(PayloadStruct));                // get ACK payload from FIFO
        Serial.print(F(" Recieved: "));
        Serial.print(ack.message);                              // print ACK message
        Serial.println(ack.counter);                              // print ACK counter
      } else {
        Serial.println(F(" Recieved: a blank ACK packet"));       // empty ACK packet received
      }
      payload.counter++;                                        // increment payload counter

    } else {
      Serial.println(F("Transmission failed or timed out"));    // payload was not delivered
    }

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {                    // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getDynamicPayloadSize(); // get the size of the payload
      PayloadStruct tx;
      radio.read(&tx, bytes);                        // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);                           // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                            // print the pipe number
      Serial.print(F(": "));
      Serial.print(tx.message);                      // print payload message
      Serial.print(tx.counter);                      // print payload counter
      Serial.print(F(" Sent: "));
      Serial.print(payload.message);                 // print ACK message
      Serial.println(payload.counter);               // print ACK counter

      // increment payload counter
      payload.counter++;
      // load the payload for the first received transmission on pipe 0
      radio.writeAckPayload(0, &payload, sizeof(PayloadStruct));
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      memcpy(payload.message, "Hello ", 6); // change payload message
      radio.stopListening();                // this also discards any unused ACK payloads
      // address for this example doesn't change
      // radio.openWritingPipe(address);

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));


      memcpy(payload.message, "World ", 6);                      // change payload message
      // load the payload for the first received transmission on pipe 0
      radio.writeAckPayload(0, &payload, sizeof(PayloadStruct));
      payload.counter++;                                         // increment payload counter

      // address for this example doesn't change
      // radio.openReadingPipe(0, address);
      radio.startListening();
    }
  }

  // to make this example readable in the serial monitor
  delay(1000); // slow it down by 1 second
} // loop