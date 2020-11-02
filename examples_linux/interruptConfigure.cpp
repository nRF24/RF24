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
 * This example does not use Arduino's attachInterrupt() function, but this
 * library has ported Arduino's attachInterrupt() function for ease of
 * portability in Linux. Try adjusting this example so that attachInterrupt()
 * calls this example's interruptHandler() function.
 * HINT: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 *
 * This example was written to be used on 2 or more devices acting as "nodes".
 * Use `ctrl+c` to quit at any time.
 */
#include <ctime>       // time()
#include <iostream>
#include <string>
#include <printf.h>
#include <RF24/RF24.h> // delay(), pinMode(), digitalRead(), OUTPUT

using namespace std;

// We will be using the nRF24L01's IRQ pin for this example
#define IRQ_PIN 6 // this needs to be a digital input capable pin

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
uint8_t address[6] = "1Node";
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// For this example, we'll be using a payload containing
// a string that changes on every transmission. (successful or not)
// Make a couple arrays of payloads & an iterator to traverse them
const uint8_t tx_pl_size = 5;
const uint8_t ack_pl_size = 4;
uint8_t pl_iterator = 0;
// The " + 1" compensates for the c-string's NULL terminating 0
char tx_payloads[][tx_pl_size + 1] = {"Ping ", "Pong ", "Radio", "1FAIL"};
char ack_payloads[][ack_pl_size + 1] = {"Yak ", "Back", " ACK"};

void interruptHandler(); // prototype to handle the interrupt request (IRQ) pin
void setRole(); // prototype to set the node's role
void master();  // prototype of the TX node's behavior; called by setRole()
void slave();   // prototype of the RX node's behavior; called by setRole()
void ping_n_wait(); // prototype that sends a payload and waits for the IRQ pin to get triggered


int main() {

    // setup the digital input pin connected to the nRF24L01's IRQ pin
    pinMode(IRQ_PIN, OUTPUT);

    // perform hardware check
    if (!radio.begin()) {
        cout << "nRF24L01 is not responding!!" << endl;
        return 0; // quit now
    }

    // print example's introductory prompt
    cout << "RF24/examples_linux/AcknowledgementPayloads\n";

    // Acknowledgement packets have no payloads by default. We need to enable
    // this feature for all nodes (TX & RX) to use ACK payloads.
    radio.enableAckPayload();

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

    // Fot this example, we use the same address to send data back and forth
    // set the addresses for both RX and TX nodes
    radio.openWritingPipe(address);    // always uses pipe 0
    radio.openReadingPipe(0, address); // using pipe 0

    // for debugging, uncomment the follow 2 lines
    // printf_begin();
    // radio.printDetails();

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
 * act as the transmitter
 */
void master() {
    pl_iterator = 0; // reset the iterator for the following tests done in master()


    // Test the "data ready" event with the IRQ pin
    cout << "\nConfiguring IRQ pin to ignore the 'data sent' event\n";
    radio.maskIRQ(true, false, false); // args = "data_sent", "data_fail", "data_ready"
    cout << "   Pinging RX node for 'data ready' event...";
    ping_n_wait();                     // transmit a payload and detect the IRQ pin
    pl_iterator++;                     // increment iterator for next test


    // Test the "data sent" event with the IRQ pin
    cout << "\nConfiguring IRQ pin to ignore the 'data ready' event\n";
    radio.maskIRQ(false, false, true); // args = "data_sent", "data_fail", "data_ready"
    cout << "   Pinging RX node for 'data sent' event...";
    ping_n_wait();                     // transmit a payload and detect the IRQ pin
    pl_iterator++;                     // increment iterator for next test


    // Use this iteration to fill the RX node's FIFO which sets us up for the next test.
    // write() uses virtual interrupt flags that work despite the masking of the IRQ pin
    radio.maskIRQ(1, 1, 1); // disable IRQ masking for this step

    cout << "\nSending 1 payload to fill RX node's FIFO. IRQ pin is neglected.\n";
    // write() will call flush_tx() on 'data fail' events
    if (radio.write(&tx_payloads[pl_iterator], tx_pl_size))
        cout << "RX node's FIFO is full; it is not listening any more" << endl;
    else
        cout << "Transmission failed or timed out. Continuing anyway." << endl;
    pl_iterator++;                     // increment iterator for next test


    // test the "data fail" event with the IRQ pin
    cout << "\nConfiguring IRQ pin to reflect all events\n";
    radio.maskIRQ(0, 0, 0); // args = "data_sent", "data_fail", "data_ready"
    cout << "   Pinging inactive RX node for 'data fail' event...";


    // all IRQ tests are done; flush_tx() and print the ACK payloads for fun
    char rx_fifo[ack_pl_size * 3];             // RX FIFO is full & we know ACK payloads' size
    if (radio.available()) {                   // if there is data in the RX FIFO
        radio.read(&rx_fifo, ack_pl_size * 3); // this clears the RX FIFO (for this example)

        // print the entire RX FIFO with 1 buffer
        cout << "\nComplete RX FIFO: " << rx_fifo << endl;
    }
    delay(500);                                // wait for RX node to startListening() again

} // master


/**
 * act as the receiver
 */
void slave() {
    // Fill the TX FIFO with 3 ACK payloads for the first 3 received
    // transmissions on pipe 0.
    radio.writeAckPayload(0, &ack_payloads[0], ack_pl_size);
    radio.writeAckPayload(0, &ack_payloads[1], ack_pl_size);
    radio.writeAckPayload(0, &ack_payloads[2], ack_pl_size);
    radio.startListening();                     // We're ready to start. Begin listening.

    time_t startTimer = time(nullptr);          // start a timer
    while (time(nullptr) - startTimer < 6 && !radio.rxFifoFull()) {
        // use 6 second timeout & wait till RX FIFO is full
    }
    delay(200);                                 // let last ACK finish transmitting
    radio.stopListening();                      // also discards unused ACK payloads

    if (radio.rxFifoFull()) {
        char rx_fifo[tx_pl_size * 3 + 1];       // RX FIFO is full & we know TX payloads' size
        radio.read(&rx_fifo, tx_pl_size * 3);   // this clears the RX FIFO for this example
        rx_fifo[tx_pl_size * 3] = 0;            // append a NULL terminating 0 for use as a c-string
        cout <<"Complete RX FIFO: " << rx_fifo; // print the entire RX FIFO with 1 buffer
        cout << endl;
    }
    else {
        cout << "Timeout was reached. Going back to setRole()" << endl;
    }
}


/**
 * pings the receiver with a non-blocking startWrite(), then waits till
 * the IRQ pin is triggered
 */
void ping_n_wait() {
    // use the non-blocking call to write a payload and begin transmission
    // the "false" argument means we are expecting an ACK packet response
    radio.startWrite(tx_payloads[pl_iterator], tx_pl_size, false);

    while (digitalRead(IRQ_PIN)) {
        /*
         * IRQ pin is LOW when activated. Otherwise it is always HIGH
         * Wait in this empty loop until IRQ pin is activated.
         *
         * In this example, the "data fail" event is always configured to
         * trigger the IRQ pin active. Because the auto-ACK feature is on by
         * default, we don't need a timeout check to prevent an infinite loop.
         */
    }
    interruptHandler(); // print what happened
}


/**
 * when the IRQ pin goes active LOW, call this fuction print out why
 */
void interruptHandler() {
    // print IRQ status and all masking flags' states

    cout << "\tIRQ pin is actively LOW" << endl;  // show that this function was called

    bool tx_ds, tx_df, rx_dr;                     // declare variables for IRQ masks
    radio.whatHappened(tx_ds, tx_df, rx_dr);      // get values for IRQ masks
    // whatHappened() clears the IRQ masks also. This is required for
    // continued TX operations when a transmission fails.
    // clearing the IRQ masks resets the IRQ pin to its inactive state (HIGH)

    cout << "\tdata_sent: " << tx_ds;             // print "data sent" mask state
    cout << ", data_fail: " << tx_df;             // print "data fail" mask state
    cout << ", data_ready: " << rx_dr << endl;    // print "data ready" mask state

    if (tx_df)                                    // if TX payload failed
        radio.flush_tx();                         // clear all payloads from the TX FIFO

    // print if test passed or failed. Unintentional fails mean the RX node was not listening.
    if (pl_iterator == 0)
        cout << "   'Data Ready' event test " << (rx_dr ? "passed" : "failed") << endl;
    else if (pl_iterator == 1)
        cout << "   'Data Sent' event test " << (tx_ds ? "passed" : "failed") << endl;
    else if (pl_iterator == 3)
        cout << "   'Data Fail' event test " << (tx_df ? "passed" : "failed") << endl;
} // interruptHandler
