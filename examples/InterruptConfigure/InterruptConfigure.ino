/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * This example uses Acknowledgement (ACK) payloads attached to ACK packets to
 * demonstrate how the nRF24L01's IRQ (Interrupt Request) pin can be
 * configured to detect when data is received, or when data has transmitted
 * successfully, or when data has failed to transmit.
 *
 * A challenge to learn new skills:
 * This example does not use Arduino's attachInterrupt() function. Try
 * adjusting this example so that attachInterrupt() calls this example's
 * interruptHandler() function.
 * HINT: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use the Serial Monitor to change each node's behavior.
 */
#include <SPI.h>
#include "RF24.h"

// We will be using the nRF24L01's IRQ pin for this example
#define IRQ_PIN 6 // this needs to be a digital input capable pin

// We will be using the nRF24L01's CE pin to control transmissions
#define CE_PIN 7
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// Let these addresses be used for the pair
uint8_t address[6] = "1Node";
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX node, flase = RX node

// For this example, we'll be using a payload containing
// a string that changes on every transmission. (successful or not)
// Make a couple arrays of payloads & an iterator to traverse them
const uint8_t tx_pl_size = 5;
const uint8_t ack_pl_size = 4;
uint8_t pl_iterator = 0;
// The " + 1" compensates for the c-string's NULL terminating 0
char tx_payloads[][tx_pl_size + 1] = {"Ping ", "Pong ", "Radio", "1FAIL"};
char ack_payloads[][ack_pl_size + 1] = {"Yak ", "Back", " ACK"};

// Declare prototype for interruptHandler()
void interruptHandler(); // see definition below loop()

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
  Serial.println(F("RF24/examples/InterruptConfigure"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // setup the IRQ_PIN
  pinMode(IRQ_PIN, INPUT);
  // pinMode(CE_PIN, OUTPUT); // performed by radio.begin()

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);     // RF24_PA_MAX is default.

  // For this example we use acknowledgment payloads to trigger the
  // IRQ pin when data is received on the TX node.
  // Acknowledgement packets have no payloads by default. We need to enable
  // this feature for all nodes (TX & RX) to use ACK payloads.
  radio.enableAckPayload();

  // Fot this example, we use the same address to send data back and forth
  // set the addresses for both RX and TX nodes
  radio.openWritingPipe(address);    // always uses pipe 0
  radio.openReadingPipe(0, address); // using pipe 0

  // additional setup specific to the node's role
  if (role) {
    // setup for TX mode
    radio.stopListening();                                  // powerUp() into TX mode

  } else {
    // setup for RX mode
    // Fill the TX FIFO with 3 ACK payloads for the first 3 received
    // transmissions on pipe 0.
    radio.writeAckPayload(0, &ack_payloads[0], ack_pl_size);
    radio.writeAckPayload(0, &ack_payloads[1], ack_pl_size);
    radio.writeAckPayload(0, &ack_payloads[2], ack_pl_size);
    radio.startListening();                                 // powerUp() into RX mode
  }
}

void loop() {

  if (role) {
    // This device is a TX node

    if (pl_iterator == 0) {
      // Test the "data ready" event with the IRQ pin

      Serial.println(F("\nConfiguring IRQ pin to ignore the 'data sent' event"));
      radio.maskIRQ(true, false, false); // args = "data_sent", "data_fail", "data_ready"
      Serial.println(F("   Pinging RX node for 'data ready' event..."));

    } else if (pl_iterator == 1) {
      // Test the "data sent" event with the IRQ pin

      Serial.println(F("\nConfiguring IRQ pin to ignore the 'data ready' event"));
      radio.maskIRQ(false, false, true); // args = "data_sent", "data_fail", "data_ready"
      Serial.println(F("   Pinging RX node for 'data sent' event..."));

    } else if (pl_iterator == 2) {
      // Use this iteration to fill the RX node's FIFO which sets us up for the next test.

      // write() uses virtual interrupt flags that work despite the masking of the IRQ pin
      radio.maskIRQ(1, 1, 1); // disable IRQ masking for this step

      Serial.println(F("\nSending 1 payload to fill RX node's FIFO. IRQ pin is neglected."));
      if (radio.write(&tx_payloads[pl_iterator], tx_pl_size)) {
        Serial.println(F("RX node's FIFO is full; it is not listening any more"));
      } else {
        radio.flush_tx(); // clear the failed payload for continued operation
        Serial.println(F("Transmission failed or timed out. Continuing anyway."));
      }

    } else if (pl_iterator == 3) {
      // test the "data fail" event with the IRQ pin

      Serial.println(F("\nConfiguring IRQ pin to reflect all events"));
      radio.maskIRQ(0, 0, 0); // args = "data_sent", "data_fail", "data_ready"
      Serial.println(F("   Pinging inactive RX node for 'data fail' event..."));
    }

    if (pl_iterator < 4 && pl_iterator != 2) {
      // use the non-blocking call to write a payload and begin transmission
      // the "false" argument means we are expecting an ACK packet response
      radio.startFastWrite(tx_payloads[pl_iterator++], tx_pl_size, false);

      // To only send 1 payload at a time, there needs to be a 10 us pulse on
      // the CE_PIN. Every call to startWrite() initiates that pulse.
      delayMicroseconds(10); // ensure pulse is at least 10 us
      digitalWrite(CE_PIN, LOW); // end the 10 us mandatory pulse

      while (digitalRead(IRQ_PIN)) {
        /*
         * IRQ pin is LOW when activated. Otherwise it is always HIGH
         * Wait in this empty loop until IRQ pin is activated.
         *
         * In this example, the "data fail" event is always configured to
         * trigger the IRQ pin active. Because the auto-ACK feature is on by
         * default, we don't need to use a timeout check to prevent an
         * infinite loop.
         */
      }
      interruptHandler(); // print what happened

    } else if (pl_iterator == 4) {
      // all IRQ tests are done; flush_tx() and print the ACK payloads for fun
      char rx_fifo[ack_pl_size * 3];             // RX FIFO is full & we know ACK payloads' size
      if (radio.available()) {                   // if there is data in the RX FIFO
        radio.read(&rx_fifo, ack_pl_size * 3);   // this clears the RX FIFO (for this example)
        Serial.print(F("\nComplete RX FIFO: "));
        Serial.println(rx_fifo);                 // print the entire RX FIFO with 1 buffer
      }
      delay(500);                                // wait for RX node to startListening() again

    } else if (pl_iterator == 2) {
      pl_iterator++; // proceed from step 3 to last step (stop at step 4 for readability)
    }


  } else {
    // This device is a RX node

    if (radio.rxFifoFull()) {
      // wait until RX FIFO is full then stop listening

      radio.stopListening();                 // also discards unused ACK payloads
      char rx_fifo[tx_pl_size * 3 + 1];      // RX FIFO is full & we know TX payloads' size
      radio.read(&rx_fifo, tx_pl_size * 3);  // this clears the RX FIFO for this example
      rx_fifo[tx_pl_size * 3] = 0;           // add NULL termintating 0 (for easy printing)
      Serial.print(F("Complete RX FIFO: "));
      Serial.println(rx_fifo);               // print the entire RX FIFO with 1 buffer
      delay(100);                            // wait 100 ms for TX node to complete it's role

      // Fill the TX FIFO with 3 ACK payloads for the first 3 received
      // transmissions on pipe 0.
      radio.writeAckPayload(0, &ack_payloads[0], ack_pl_size);
      radio.writeAckPayload(0, &ack_payloads[1], ack_pl_size);
      radio.writeAckPayload(0, &ack_payloads[2], ack_pl_size);
      radio.startListening();                // We're ready to start over. Begin listening.
    }

  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T') {
      // Become the TX node
      if (!role)
        Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      else
        Serial.println(F("*** RESTARTING IRQ PIN TEST ***"));

      role = true;
      pl_iterator = 0;  // reset the iterator

      // startListening() clears the IRQ masks also. This is required for
      // continued TX operations when a transmission fails.
      radio.stopListening(); // this also discards any unused ACK payloads
      // address for this example doesn't change
      // radio.openWritingPipe(address);

    } else if (c == 'R' && role) {
      // Become the RX node
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));

      role = false;

      // Fill the TX FIFO with 3 ACK payloads for the first 3 received
      // transmissions on pipe 0
      radio.flush_tx(); // make sure there is room for 3 new ACK payloads
      radio.writeAckPayload(0, &ack_payloads[0], ack_pl_size);
      radio.writeAckPayload(0, &ack_payloads[1], ack_pl_size);
      radio.writeAckPayload(0, &ack_payloads[2], ack_pl_size);

      // address for this example doesn't change
      // radio.openReadingPipe(0, address);
      radio.startListening();
    } // change role
  } // Serial.available()
} // loop

void interruptHandler() {
  // print IRQ status and all masking flags' states

  Serial.println(F("\tIRQ pin is actively LOW")); // show that this function was called

  bool tx_ds, tx_df, rx_dr;                     // declare variables for IRQ masks
  radio.whatHappened(tx_ds, tx_df, rx_dr);      // get values for IRQ masks
  // whatHappened() clears the IRQ masks also. This is required for
  // continued TX operations when a transmission fails.

  Serial.print(F("\tdata_sent: "));
  Serial.print(tx_ds);                          // print "data sent" mask state
  Serial.print(F(", data_fail: "));
  Serial.print(tx_df);                          // print "data fail" mask state
  Serial.print(F(", data_ready: "));
  Serial.println(rx_dr);                        // print "data ready" mask state

  if (tx_df)                                    // if TX payload failed
    radio.flush_tx();                           // clear all payloads from the TX FIFO

  // print if test passed or failed. Unintentional fails mean the RX node was not listening.
  // pl_iterator has already been incremented by now
  if (pl_iterator == 1) {
    if (rx_dr) {
      Serial.println(F("   'Data Ready' event test passed."));
    } else {
      Serial.println(F("   'Data Ready' event test failed."));
    }
  } else if (pl_iterator == 2) {
    if (tx_ds) {
      Serial.println(F("   'Data Sent' event test passed."));
    } else {
      Serial.println(F("   'Data Sent' event test failed."));
    }
  } else if (pl_iterator == 4) {
    if (tx_df) {
      Serial.println(F("   'Data Fail' event test passed."));
    } else {
      Serial.println(F("   'Data Fail' event test failed."));
    }
  }
} // interruptHandler