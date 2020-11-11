/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another
 * with manually transmitted (non-automatic) Acknowledgement (ACK) payloads.
 * This example still uses ACK packets, but they have no payloads. Instead the
 * acknowledging response is sent with `write()`. This tactic allows for more
 * updated acknowledgement payload data, where actual ACK payloads' data are
 * outdated by 1 transmission because they have to loaded before receiving a
 * transmission.
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */
#include <SPI.h>
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX node, false = RX node

// For this example, we'll be using a payload containing
// a string & an integer number that will be incremented
// on every successful transmission.
// Make a data structure to store the entire payload of different datatypes
struct PayloadStruct {
  char message[7];          // only using 6 characters for TX & RX payloads
  uint8_t counter;
};
PayloadStruct payload;

void setup() {

  // append a NULL terminating character for printing as a c-string
  payload.message[6] = 0;

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
  Serial.println(F("RF24/examples/ManualAcknowledgements"));

  // To set the radioNumber via the Serial monitor on startup
  Serial.println(F("Which radio is this? Enter '0' or '1'. Defaults to '0'"));
  while (!Serial.available()) {
    // wait for user input
  }
  char input = Serial.parseInt();
  radioNumber = input == 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  // role variable is hardcoded to RX behavior, inform the user of this
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload)); // char[7] & uint8_t datatypes occupy 8 bytes

  // For this example, we use the different addresses to send data
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1
  // Notice that the addresses assigned to pipes are not changed in
  // loop() because we are using pipe 1 to receive and pipe 0 to transmit
  // However, if we used pipe 0 to receive we would need to constantly
  // re-write the TX address on pipe 0

  if (role) {
    // setup the TX node

    memcpy(payload.message, "Hello ", 6); // set the outgoing message
    radio.stopListening();                // powerUp() into TX mode
  } else {
    // setup the RX node

    memcpy(payload.message, "World ", 6); // set the outgoing message
    radio.startListening();               // powerUp() into RX mode
  }
}

void loop() {

  if (role) {
    // This device is a TX node

    unsigned long start_timer = micros();                 // start the timer
    bool report = radio.write(&payload, sizeof(payload)); // transmit & save the report

    if (report) {
      // transmission successful; wait for response and print results

      bool timed_out = false;                                // a flag to track if response timed out
      radio.startListening();                                // put in RX mode
      unsigned long start_timeout = millis();                // timer to detect no response
      while (!radio.available() && !timed_out) {             // wait for response or timeout
        if (millis() - start_timeout > 250)                  // only wait 250 ms
          timed_out = true;
      }
      unsigned long end_timer = micros();                    // end the timer
      radio.stopListening();                                 // put back in TX mode

      // print summary of transactions
      Serial.print(F("Transmission successful!"));           // payload was delivered
      if (radio.available()) {                               // is there a payload received
        Serial.print(F(" Round trip delay = "));
        Serial.print(end_timer - start_timer);               // print the timer result
        Serial.print(F(" us. Sent: "));
        Serial.print(payload.message);                       // print the outgoing payload's message
        Serial.print(payload.counter);                       // print outgoing payload's counter
        PayloadStruct received;
        radio.read(&received, sizeof(received));             // get payload from RX FIFO
        Serial.print(F(" Recieved: "));
        Serial.print(received.message);                      // print the incoming payload's message
        Serial.println(received.counter);                    // print the incoming payload's counter
        payload.counter = received.counter;                  // save incoming counter for next outgoing counter
      } else {
        Serial.println(F(" Recieved no response."));         // no response received
      }
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    } // report

    // to make this example readable in the serial monitor
    delay(1000);  // slow transmissions down by 1 second

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {              // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize();  // get size of incoming payload
      PayloadStruct received;
      radio.read(&received, sizeof(received)); // get incoming payload
      payload.counter = received.counter + 1;  // increment incoming counter for next outgoing response

      // transmit response & save result to `report`
      radio.stopListening();                   // put in TX mode
      bool report = radio.write(&payload, sizeof(payload));
      radio.startListening();                  // put back in RX mode

      // print summary of transactions
      Serial.print(F("Received "));
      Serial.print(bytes);                     // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                      // print the pipe number
      Serial.print(F(": "));
      Serial.print(received.message);          // print incoming message
      Serial.print(received.counter);          // print incoming counter

      if (report) {
        Serial.print(F(" Sent: "));
        Serial.print(payload.message);         // print outgoing message
        Serial.println(payload.counter);       // print outgoing counter
      } else {
        Serial.println(" Response failed.");   // failed to send response
      }
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      memcpy(payload.message, "Hello ", 6); // set the outgoing message
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();                // put in TX mode

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      memcpy(payload.message, "World ", 6); // set the response message
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.startListening();               // put in RX mode
    }
  }
} // loop