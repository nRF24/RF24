/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from 1 nRF24L01 transceiver to another.
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use `ctrl+c` to quit at any time.
 */
#include <ctime>       // time()
#include <cmath>       // abs()
#include <iostream>
#include <string>
#include <printf.h>
#include <RF24/RF24.h> // millis()

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

// For this example, we'll be sending 32 payloads each containing
// 32 bytes of data that looks like ASCII art when printed to the serial
// monitor. The TX node and RX node needs only a single 32 byte buffer.
#define SIZE 32
char buffer[SIZE + 1];     // for the RX node
unsigned int counter = 0;  // for counting the number of received payloads
void makePayload(uint8_t); // prototype to construct payload dynamically

void setRole(); // prototype to set the node's role
void master();  // prototype of the TX node's behavior; called by setRole()
void slave();   // prototype of the RX node's behavior; called by setRole()


int main() {

    // add a NULL terminating 0 for printing as a c-string
    buffer[SIZE] = 0;

    // perform hardware check
    if (!radio.begin()) {
        cout << "nRF24L01 is not responding!!" << endl;
        return 0; // quit now
    }

    // print example's introductory prompt
    cout << "RF24/examples_linux/streamingData\n";

    // To set the radioNumber via the terminal on startup
    cout << "Which radio is this? Enter '0' or '1'. Defaults to '0' ";
    string input;
    getline(cin, input);
    radioNumber = input.length() > 0 && (uint8_t)input[0] == 49;

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit a float
    radio.setPayloadSize(SIZE);        // default value is the maximum 32 bytes

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW);     // RF24_PA_MAX is default.

    // Fot this example, we use the same address to send data back and forth
    // set the addresses for both RX and TX nodes
    radio.openWritingPipe(address);    // always uses pipe 0
    radio.openReadingPipe(0, address); // using pipe 0

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
    radio.stopListening();                           // powerUp() into TX mode

    unsigned int failures = 0;               // keep track of failures
    uint8_t i = 0;
    unsigned long startTimer = millis();     // start the timer
    while (failures < 100 && i < SIZE) {
        makePayload(i);
        if (!radio.writeFast(&buffer, SIZE)) {
            failures++;
            radio.reUseTX();
        }
        else {
            i++;
        }
    }
    uint32_t endTimer = millis();            // end the timer
    if (failures < 100) {
        cout << "Time to transmit data = ";
        cout << endTimer - startTimer;       // print the timer result
        cout << " ms. Detected: ";
        cout << failures;                    // print number of retries
        cout << " failures." << endl;
    }
    else {
        // else There was (most likely) no device listening for the data stream
        cout << "Too many failures detected (" << failures;
        cout << "); going back to setRole()" << endl;
    }
}

/**
 * make this node act as the receiver
 */
void slave() {

    radio.startListening();                                  // powerUp() into RX mode

    time_t startTimer = time(nullptr);                       // start a timer
    while (time(nullptr) - startTimer < 6) {                 // use 6 second timeout
        if (radio.available()) {                             // is there a payload
            radio.read(&buffer, SIZE);                       // fetch payload from FIFO
            cout << "Received: " << buffer;                  // print the payload's value
            cout << " - " << counter << endl;                // print the counter
            counter++;                                       // increment counter
            startTimer = time(nullptr);                      // reset timer
        }
    }
    cout << "Timeout reached. Nothing received in 6 seconds" << endl;
    radio.stopListening();
}

/**
 * Make a single payload based on position in stream.
 * This example employs function to save on memory allocated.
 */
void makePayload(uint8_t i) {

  // let the first character be an identifying alphanumeric prefix
  // this lets us see which payload didn't get received
  buffer[0] = i + (i < 26 ? 65 : 71);
  for (uint8_t j = 0; j < SIZE - 1; ++j) {
    char chr = j >= (SIZE - 1) / 2 + abs((SIZE - 1) / 2 - i);
    chr |= j <= (SIZE - 1) / 2 - abs((SIZE - 1) / 2 - i);
    buffer[j + 1] = chr + 48;
  }
}
