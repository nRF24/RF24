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
 * A challenge to learn new skills:
 * This example uses 2 different addresses for the RX & TX nodes.
 * Try adjusting this example to use the same address on different pipes.
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */
#include <SPI.h>
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair of nodes used in this example
uint8_t address[][6] = {"1Node", "2Node"};
//             the TX address^ ,  ^the RX address
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX node, flase = RX node

// For this example, we'll be using a payload containing
// an integer number that will be incremented
// on every successful transmission.
unsigned int payload;

void setup() {

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
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);     // RF24_PA_MAX is default.


  // Fot this example, we use the different addresses to send data back and forth
  // Notice that the addresses assigned to pipes are changed in loop() also
  if (role) {
    // setup the TX node

    radio.stopListening();                // powerUp() into TX mode
    radio.openWritingPipe(address[0]);    // set pipe 0 to the TX address

    // initialize the payload (used as a counter for successful transmission)
    payload = 0;
  } else {
    // setup the RX node

    radio.openReadingPipe(1, address[0]); // set pipe 1 to the TX address
    radio.startListening();               // powerUp() into RX mode
  }
}

void loop() {

  if (role) {
    // This device is a TX node

    unsigned long start_timer = micros();                      // start the timer
    bool report = radio.write(&payload, sizeof(unsigned int)); // transmit & save the report

    if (report) {
      // transmission successful; wait for response and print results

      bool timed_out = false;                                // a flag to track if response timed out
      radio.openReadingPipe(1, address[1]);                  // open pipe 1 to the RX address
      radio.startListening();                                // put in RX mode
      unsigned long start_timeout = millis();                // timer to detect no response
      while (!radio.available() && !timed_out) {             // wait for response or timeout
        if (millis() - start_timeout > 200)                  // only wait 200 ms
          timed_out = true;
      }
      unsigned long end_timer = micros();                    // end the timer
      radio.stopListening();                                 // put back in TX mode
      radio.openWritingPipe(address[0]);                     // set the pipe 0 to TX address

      // print summary of transactions
      Serial.print(F("Transmission successful!"));           // payload was delivered
      if (!timed_out && radio.available()) {                 // is there a payload received
        Serial.print(F(" Round trip delay = "));
        Serial.print(end_timer - start_timer);               // print the timer result
        Serial.print(F(" us. Sent: "));
        Serial.print(payload);                               // print the payload sent
        radio.read(&payload, sizeof(unsigned int));          // get payload from FIFO
        Serial.print(F(" Recieved: "));
        Serial.println(payload);                             // print the payload received
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
    if (radio.available(&pipe)) {                    // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getDynamicPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);                   // fetch payload from FIFO
      payload++;                                     // increment payload for response

      // transmit response & save result to `report`
      radio.stopListening();                         // put in TX mode
      radio.openWritingPipe(address[1]);             // set the pipe 0 to RX address
      bool report = radio.write(&payload, sizeof(unsigned int));
      radio.openReadingPipe(1, address[0]);          // open pipe 1 to the TX address
      radio.startListening();                        // put back in RX mode

      // print summary of transactions
      Serial.print(F("Received "));
      Serial.print(bytes);                           // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                            // print the pipe number
      Serial.print(F(": "));
      Serial.print(payload - 1);                     // print payload received

      if (report) {
        Serial.print(F(" Sent: "));
        Serial.println(payload);                     // print payload sent in response
      } else {
        Serial.println(" Response failed.");         // failed to send response
      }
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();                // put in TX mode
      radio.openWritingPipe(address[0]);    // set pipe 0 to the TX address

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.openReadingPipe(1, address[0]); // open pipe 1 to the TX address
      radio.startListening();               // put in RX mode
    }
  }
} // loop