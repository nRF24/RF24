/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another
 * with Acknowledgement (ACK) payloads attached to ACK packets.
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use `ctrl+c` to quit at any time.
 */
#include <ctime>       // time()
#include <iostream>
#include <string>
#include <time.h>      // CLOCK_MONOTONIC_RAW, timespec, clock_gettime()
#include <printf.h>
#include <RF24/RF24.h> // delay()

using namespace std;

/****************** Linux ***********************/
// Radio CE Pin, CSN Pin, SPI Speed
// CE Pin uses GPIO number with BCM and SPIDEV drivers, other platforms use their own pin numbering
// CS Pin addresses the SPI bus number at /dev/spidev<a>.<b>
// ie: RF24 radio(<ce_pin>, <a>*10+<b>); spidev1.0 is 10, spidev1.1 is 11 etc..

// Generic:
RF24 radio(22, 0);

/****************** Linux (BBB,x86,etc) ***********************/
// See http://tmrh20.github.io/RF24/pages.html for more information on usage
// See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV

// Let these addresses be used for the pair
uint8_t address[2][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// For this example, we'll be using a payload containing
// a string & an integer number that will be incremented
// on every successful transmission.
// Make a data structure to store the entire payload of different datatypes
struct PayloadStruct {
  char message[7]; // only using 6 characters for TX & ACK payloads
  uint8_t counter;
};
PayloadStruct payload;

void setRole(); // prototype to set the node's role
void master();  // prototype of the TX node's behavior; called by setRole()
void slave();   // prototype of the RX node's behavior; called by setRole()

// custom defined timer for evaluating transmission time in microseconds
struct timespec startTimer, endTimer;
uint32_t getMicros(); // prototype to get ellapsed time in microseconds


int main() {
    // perform hardware check
    if (!radio.begin()) {
        cout << "nRF24L01 is not responding!!" << endl;
        return 0; // quit now
    }

    // print example's introductory prompt
    cout << "RF24/examples_linux/AcknowledgementPayloads\n";

    // To set the radioNumber via the terminal on startup
    cout << "Which radio is this? Enter '0' or '1'. Defaults to '0' ";
    string input;
    getline(cin, input);
    radioNumber = input.length() > 0 && (uint8_t)input[0] == 49;

    // to use ACK payloads, we need to enable dynamic payload lengths
    radio.enableDynamicPayloads();    // ACK payloads are dynamically sized

    // Acknowledgement packets have no payloads by default. We need to enable
    // this feature for all nodes (TX & RX) to use ACK payloads.
    radio.enableAckPayload();

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

    // For this example, we use the different addresses to send data
    radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0
    radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

    // for debugging
    printf_begin();
    radio.printDetails();

    // ready to execute program now
    setRole(); // calls master() or slave() based on user input
    return 0;
}

/**
 * set this node's role from stdin stream.
 * this only considers the first char as input.
 */
void setRole() {
    string input = "";
    while (!input.length()) {
        cout << "*** PRESS 'T' to begin transmitting to the other node\n";
        cout << "*** PRESS 'R' to begin receiving from the other node\n";
        cout << "*** PRESS 'Q' to exit" << endl;
        getline(cin, input);
        if (input.length() >= 1) {
            if (input[0] == 'T' || input[0] == 't')
                master();
            else if (input[0] == 'R' || input[0] == 'r')
                slave();
            else if (input[0] == 'Q' || input[0] == 'q')
                break;
            else
                cout << input[0] << " is an invalid input. Please try again." << endl;
        }
        input = ""; // stay in the while loop
    } // while
} // setRole()


/**
 * make this node act as the transmitter
 */
void master() {
    memcpy(payload.message, "Hello ", 6);                           // set the payload message
    radio.stopListening();                                          // powerUp() into TX mode

    unsigned int failures = 0;                                            // keep track of failures
    while (failures <  6) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &startTimer);      // start the timer
        bool report = radio.write(&payload, sizeof(payload)); // transmit & save the report
        uint32_t timerEllapsed = getMicros();                 // end the timer

        if (report) {
            // payload was delivered
            cout << "Transmission successful! Time to transmit = ";
            cout << timerEllapsed;                                // print the timer result
            cout << " us. Sent: ";
            cout << payload.message;                              // print outgoing message
            cout << (unsigned int)payload.counter;                // print outgoing counter counter

            if (radio.available()) {
                PayloadStruct received;
                radio.read(&received, sizeof(received));          // get incoming ACK payload
                cout << " Received: ";
                cout << received.message;                         // print incoming message
                cout << (unsigned int)received.counter << endl;   // print incoming counter
                payload.counter++;                                // increment outgoing counter
            }
            else {
                cout << " Received an empty ACK packet." << endl; // ACK had no payload
            }
        }
        else {
            cout << "Transmission failed or timed out" << endl;   // payload was not delivered
            failures++;                                           // increment failures
        }

        // to make this example readable in the terminal
        delay(1000);  // slow transmissions down by 1 second
    }
    cout << failures << " failures detected, going back to setRole()" << endl;
}

/**
 * make this node act as the receiver
 */
void slave() {
    memcpy(payload.message, "World ", 6);                    // set the payload message

    // load the payload for the first received transmission on pipe 0
    radio.writeAckPayload(1, &payload, sizeof(payload));

    radio.startListening();                                  // powerUp() into RX mode
    time_t startTimer = time(nullptr);                       // start a timer
    while (time(nullptr) - startTimer < 6) {                 // use 6 second timeout
        uint8_t pipe;
        if (radio.available(&pipe)) {                        // is there a payload? get the pipe number that recieved it
            uint8_t bytes = radio.getDynamicPayloadSize();   // get the size of the payload
            PayloadStruct received;
            radio.read(&received, sizeof(received));         // fetch payload from RX FIFO
            cout << "Received " << (unsigned int)bytes;      // print the size of the payload
            cout << " bytes on pipe " << (unsigned int)pipe; // print the pipe number
            cout << ": " << received.message;
            cout << (unsigned int)received.counter;          // print received payload
            cout << " Sent: ";
            cout << payload.message;
            cout << (unsigned int)payload.counter << endl;   // print ACK payload sent
            startTimer = time(nullptr);                      // reset timer
            payload.counter += 1;                            // increment payload counter

            // load the payload for the first received transmission on pipe 0
            radio.writeAckPayload(1, &payload, sizeof(payload));
        }
    }
    cout << "Timeout reached. Nothing received in 6 seconds" << endl;
    radio.stopListening(); // recommended idle behavior is TX mode
}


/**
 * Calculate the ellapsed time in microseconds
 */
uint32_t getMicros() {
    // this function assumes that the timer was started using
    // `clock_gettime(CLOCK_MONOTONIC_RAW, &startTimer);`

    clock_gettime(CLOCK_MONOTONIC_RAW, &endTimer);
    uint32_t seconds = endTimer.tv_sec - startTimer.tv_sec;
    uint32_t useconds = (endTimer.tv_nsec - startTimer.tv_nsec) / 1000;

    return ((seconds) * 1000 + useconds) + 0.5;
}
