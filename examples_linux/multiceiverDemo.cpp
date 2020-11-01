/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
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


// For this example, we'll be using 6 addresses; 1 for each TX node
// It is very helpful to think of an address as a path instead of as
// an identifying device destination
// Notice that the last byte is the only byte that changes in the last 5
// addresses. This is a limitation of the nRF24L01 transceiver for pipes 2-5
// because they use the same first 4 bytes from pipe 1.
uint64_t address[6] = {0x7878787878LL,
                       0xB3B4B5B6F1LL,
                       0xB3B4B5B6CDLL,
                       0xB3B4B5B6A3LL,
                       0xB3B4B5B60FLL,
                       0xB3B4B5B605LL};


// For this example, we'll be using a payload containing
// a node ID number and a single integer number that will be incremented
// on every successful transmission.
// Make a data structure to use as a payload.
struct PayloadStruct
{
  uint8_t nodeID;
  unsigned int payloadID = 0;
};
PayloadStruct payload;

void setRole();       // prototype to set the node's role
void master(uint8_t); // prototype of a TX node's behavior; called by setRole()
void slave();         // prototype of the RX node's behavior; called by setRole()

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
    cout <<"RF24/examples_linux/multiceiverDemo" << endl;

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

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
        cout << "*** Enter a number between 0 and 5 (inclusive) to act as\n";
        cout << "    a unique node number that transmits to the RX node.\n";
        cout << "*** PRESS 'R' to begin receiving from the other nodes\n";
        cout << "*** PRESS 'Q' to exit" << endl;
        getline(cin, input);
        if (input.length() >= 1) {
            uint8_t toNumber = stoi(input[0]);
            if (toNumber < 6 && toNumber >= 0)
                master(toNumber);
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
 * act as unique TX node identified by the `role` number
 */
void master(uint8_t role) {
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

    unsigned int failures = 0;
    while (failures < 6) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &startTimer);            // start the timer
        bool report = radio.write(&payload, sizeof(PayloadStruct)); // transmit & save the report
        uint32_t timerEllapsed = getMicros();                       // end the timer

        if (report) {
            // payload was delivered
            cout << "Transmission successful! Time to transmit = ";
            cout << timerEllapsed << " us" << endl;                 // print the timer result
            payload.payloadID++;                                    // increment payload number
        }
        else {
            // payload was not delivered
            failures++;
            cout << "Transmission failed or timed out" << endl;
        }

        // to make this example readable in the terminal
        delay(1000); // slow transmissions down by 1 second
    } // while
    cout << failures << " detected. Going back to setRole()." << endl;
} // master


/**
 * act as the RX node that receives from up to 6 other TX nodes
 */
void slave() {

    // Set the addresses for all pipes to TX nodes
    for (uint8_t i = 0; i < 6; ++i)
      radio.openReadingPipe(i, address[i]);

    radio.startListening();                                        // put radio in RX mode

    time_t startTimer = time(nullptr);                             // start a timer
    while (time(nullptr) - startTimer < 6) {                       // use 6 second timeout
        uint8_t pipe;
        if (radio.available(&pipe)) {                              // is there a payload? get the pipe number that recieved it
            uint8_t bytes = radio.getDynamicPayloadSize();         // get the size of the payload
            radio.read(&payload, bytes);                           // fetch payload from FIFO
            cout << "Received " << (unsigned int)bytes;            // print the size of the payload
            cout << " bytes on pipe " << (unsigned int)pipe;       // print the pipe number
            cout << " from node " << (unsigned int)payload.nodeID; // print the payload's origin
            cout << ". PayloadID: " << payload.payloadID << endl;  // print the payload's number
            startTimer = time(nullptr);                            // reset timer
        }
    }
    cout << "Nothing received in 6 seconds. Going back to setRole()" << endl;
} // slave


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
