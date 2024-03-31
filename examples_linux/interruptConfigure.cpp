/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * This example uses Acknowledgement (ACK) payloads attached to ACK packets to
 * demonstrate how the nRF24L01's IRQ (Interrupt Request) pin can be
 * configured to detect when data is received, or when data has transmitted
 * successfully, or when data has failed to transmit.
 *
 * This example was written to be used on 2 devices acting as "nodes".
 * Use `ctrl+c` to quit at any time.
 */
#include <ctime>       // time()
#include <iostream>    // cin, cout, endl
#include <string>      // string, getline()
#include <time.h>      // CLOCK_MONOTONIC_RAW, timespec, clock_gettime()
#include <RF24/RF24.h> // RF24, RF24_PA_LOW, delay(), pinMode(), INPUT, attachInterrupt(), INT_EDGE_FALLING

using namespace std;

// We will be using the nRF24L01's IRQ pin for this example
#ifdef MRAA
    #define IRQ_PIN 18 // GPIO24
#elif defined(RF24_WIRINGPI)
    #define IRQ_PIN 5 // GPIO24
#else
    #define IRQ_PIN 24 // GPIO24
#endif

// this example is a sequential program. so we need to wait for the event to be handled
volatile bool got_interrupt = false; // used to signify that the event started

/****************** Linux ***********************/
// Radio CE Pin, CSN Pin, SPI Speed
// CE Pin uses GPIO number with BCM and SPIDEV drivers, other platforms use their own pin numbering
// CS Pin addresses the SPI bus number at /dev/spidev<a>.<b>
// ie: RF24 radio(<ce_pin>, <a>*10+<b>); spidev1.0 is 10, spidev1.1 is 11 etc..
#define CSN_PIN 0
#ifdef MRAA
    #define CE_PIN 15 // GPIO22
#elif defined(RF24_WIRINGPI)
    #define CE_PIN 3 // GPIO22
#else
    #define CE_PIN 22
#endif
// Generic:
RF24 radio(CE_PIN, CSN_PIN);
/****************** Linux (BBB,x86,etc) ***********************/
// See http://nRF24.github.io/RF24/pages.html for more information on usage
// See https://github.com/eclipse/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV

// For this example, we'll be using a payload containing
// a string that changes on every transmission. (successful or not)
// Make a couple arrays of payloads & an iterator to traverse them
const uint8_t tx_pl_size = 5;
const uint8_t ack_pl_size = 4;
uint8_t pl_iterator = 0;
// The " + 1" compensates for the c-string's NULL terminating 0
char tx_payloads[4][tx_pl_size + 1] = {"Ping ", "Pong ", "Radio", "1FAIL"};
char ack_payloads[3][ack_pl_size + 1] = {"Yak ", "Back", " ACK"};

void interruptHandler();         // prototype to handle the interrupt request (IRQ) pin
void setRole();                  // prototype to set the node's role
void master();                   // prototype of the TX node's behavior
void slave();                    // prototype of the RX node's behavior
void ping_n_wait();              // prototype that sends a payload and waits for the IRQ pin to get triggered
void printRxFifo(const uint8_t); // prototype to print entire contents of RX FIFO with 1 buffer

int main(int argc, char** argv)
{

    // perform hardware check
    if (!radio.begin()) {
        cout << "radio hardware is not responding!!" << endl;
        return 0; // quit now
    }

    // Let these addresses be used for the pair
    uint8_t address[2][6] = {"1Node", "2Node"};
    // It is very helpful to think of an address as a path instead of as
    // an identifying device destination

    // to use different addresses on a pair of radios, we need a variable to
    // uniquely identify which address this radio will use to transmit
    bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

    // print example's name
    cout << argv[0] << endl;

    // Set the radioNumber via the terminal on startup
    cout << "Which radio is this? Enter '0' or '1'. Defaults to '0' ";
    string input;
    getline(cin, input);
    radioNumber = input.length() > 0 && (uint8_t)input[0] == 49;

    // to use ACK payloads, we need to enable dynamic payload lengths
    radio.enableDynamicPayloads(); // ACK payloads are dynamically sized

    // Acknowledgement packets have no payloads by default. We need to enable
    // this feature for all nodes (TX & RX) to use ACK payloads.
    radio.enableAckPayload();

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

    // set the TX address of the RX node into the TX pipe
    radio.openWritingPipe(address[radioNumber]); // always uses pipe 0

    // set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

    // For debugging info
    // radio.printDetails();       // (smaller) function that prints raw register values
    // radio.printPrettyDetails(); // (larger) function that prints human readable data

    // setup the digital input pin connected to the nRF24L01's IRQ pin
    pinMode(IRQ_PIN, INPUT);

    // register the interrupt request (IRQ) to call our
    // Interrupt Service Routine (ISR) callback function interruptHandler()
    attachInterrupt(IRQ_PIN, INT_EDGE_FALLING, &interruptHandler);
    // IMPORTANT: do not call radio.available() before calling
    // radio.whatHappened() when the interruptHandler() is triggered by the
    // IRQ pin FALLING event. According to the datasheet, the pipe information
    // is unreliable during the IRQ pin FALLING transition.

    // ready to execute program now
    setRole(); // calls master() or slave() based on user input
    return 0;
} // main

/**
 * set this node's role from stdin stream.
 * this only considers the first char as input.
 */
void setRole()
{
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
    }               // while
} // setRole

/**
 * act as the transmitter to show 3 different IRQ events by sending 4 payloads:
 * 1. Successfully receive ACK payload first
 * 2. Successfully transmit on second
 * 3. Send a third payload to fill RX node's RX FIFO (supposedly making RX node unresponsive)
 * 4. intentionally fail transmit on the fourth
 */
void master()
{
    pl_iterator = 0; // reset the iterator for the following tests done in master()

    // Test the "data ready" event with the IRQ pin
    cout << "\nConfiguring IRQ pin to ignore the 'data sent' event\n";
    radio.maskIRQ(true, false, false); // args = "data_sent", "data_fail", "data_ready"
    cout << "   Pinging RX node for 'data ready' event..." << endl;
    ping_n_wait(); // transmit a payload and detect the IRQ pin
    pl_iterator++; // increment iterator for next test

    // Test the "data sent" event with the IRQ pin
    cout << "\nConfiguring IRQ pin to ignore the 'data ready' event\n";
    radio.maskIRQ(false, false, true); // args = "data_sent", "data_fail", "data_ready"
    cout << "   Pinging RX node for 'data sent' event..." << endl;
    radio.flush_tx(); // flush payloads from any failed prior test
    ping_n_wait();    // transmit a payload and detect the IRQ pin
    pl_iterator++;    // increment iterator for next test

    // Use this iteration to fill the RX node's FIFO which sets us up for the next test.
    // write() uses virtual interrupt flags that work despite the masking of the IRQ pin
    radio.maskIRQ(1, 1, 1); // disable IRQ masking for this step

    cout << "\nSending 1 payload to fill RX node's FIFO. IRQ pin is neglected.\n";
    // write() will call flush_tx() on 'data fail' events
    if (radio.write(&tx_payloads[pl_iterator], tx_pl_size))
        cout << "RX node's FIFO is full; it is not listening any more" << endl;
    else {
        cout << "Transmission failed or timed out. Continuing anyway." << endl;
        radio.flush_tx();
    }
    pl_iterator++; // increment iterator for next test

    // test the "data fail" event with the IRQ pin
    cout << "\nConfiguring IRQ pin to reflect all events\n";
    radio.maskIRQ(0, 0, 0); // args = "data_sent", "data_fail", "data_ready"
    cout << "   Pinging inactive RX node for 'data fail' event..." << endl;
    ping_n_wait(); // transmit a payload and detect the IRQ pin

    // CE pin is still HIGH which consumes more power. Example is now idling so...
    radio.stopListening(); // ensure CE pin is LOW
    // stopListening() also calls flush_tx() when ACK payloads are enabled

    if (radio.available()) {
        printRxFifo(ack_pl_size); // doing this will flush the RX FIFO
    }
} // master

/**
 * act as the receiver
 */
void slave()
{

    // let IRQ pin only trigger on "data_ready" event in RX mode
    radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready"

    // Fill the TX FIFO with 3 ACK payloads for the first 3 received
    // transmissions on pipe 0.
    radio.writeAckPayload(1, &ack_payloads[0], ack_pl_size);
    radio.writeAckPayload(1, &ack_payloads[1], ack_pl_size);
    radio.writeAckPayload(1, &ack_payloads[2], ack_pl_size);

    radio.startListening();            // put radio in RX mode
    time_t startTimer = time(nullptr); // start a timer
    while (time(nullptr) - startTimer < 6 && !radio.rxFifoFull()) {
        // use 6 second timeout & wait till RX FIFO is full
    }
    delay(100);            // wait for ACK payload to finish transmitting
    radio.stopListening(); // also discards unused ACK payloads

    if (radio.available()) {
        printRxFifo(tx_pl_size);
    }
    else {
        cout << "Timeout was reached. Going back to setRole()" << endl;
    }
} // slave

/**
 * pings the receiver with a non-blocking startWrite(), then waits till
 * the IRQ pin is triggered
 */
void ping_n_wait()
{
    got_interrupt = false;

    // use the non-blocking call to write a payload and begin transmission
    // the "false" argument means we are expecting an ACK packet response
    radio.startFastWrite(tx_payloads[pl_iterator], tx_pl_size, false);
    uint32_t timer = millis();
    while (!got_interrupt) {
        if (millis() - timer > 500) {
            cout << "\tIRQ NOT received" << endl;
            break;
        }
        /*
         * IRQ pin is LOW when activated. Otherwise it is always HIGH
         * Wait in this empty loop until IRQ pin is activated.
         *
         * In this example, the "data fail" event is always configured to
         * trigger the IRQ pin active. Because the auto-ACK feature is on by
         * default, we don't need a timeout check to prevent an infinite loop.
         */
    }
    // print IRQ status and all masking flags' states

    cout << "\tIRQ pin is actively LOW" << endl; // show that this function was called

    bool tx_ds, tx_df, rx_dr;                // declare variables for IRQ masks
    radio.whatHappened(tx_ds, tx_df, rx_dr); // get values for IRQ masks
    // whatHappened() clears the IRQ masks also. This is required for
    // continued TX operations when a transmission fails.
    // clearing the IRQ masks resets the IRQ pin to its inactive state (HIGH)

    cout << "\tdata_sent: " << tx_ds;          // print "data sent" mask state
    cout << ", data_fail: " << tx_df;          // print "data fail" mask state
    cout << ", data_ready: " << rx_dr << endl; // print "data ready" mask state

    if (tx_df)            // if TX payload failed
        radio.flush_tx(); // clear all payloads from the TX FIFO

    // print if test passed or failed. Unintentional fails mean the RX node was not listening.
    if (pl_iterator == 0)
        cout << "   'Data Ready' event test " << (rx_dr ? "passed" : "failed") << endl;
    else if (pl_iterator == 1)
        cout << "   'Data Sent' event test " << (tx_ds ? "passed" : "failed") << endl;
    else if (pl_iterator == 3)
        cout << "   'Data Fail' event test " << (tx_df ? "passed" : "failed") << endl;

    got_interrupt = false;
}

/**
 * when the IRQ pin goes active LOW.
 * Here we just set a flag to unblock ping_n_wait()
 */
void interruptHandler()
{
    got_interrupt = true; // ready to continue
}

/**
 * Print the entire RX FIFO with one buffer. This will also flush the RX FIFO.
 * @param pl_size used to determine received payload size. Remember that the
 * payload sizes are declared as tx_pl_size and ack_pl_size.
 */
void printRxFifo(const uint8_t pl_size)
{
    char rx_fifo[pl_size * 3 + 1]; // assuming RX FIFO is full; declare a buffer to hold it all
    if (radio.rxFifoFull()) {
        rx_fifo[pl_size * 3] = 0;          // add a NULL terminating char to use as a c-string
        radio.read(&rx_fifo, pl_size * 3); // this clears the RX FIFO (for this example)
    }
    else {
        uint8_t i = 0;
        while (radio.available()) {
            radio.read(&rx_fifo + (i * pl_size), pl_size);
            i++;
        }
        rx_fifo[i * pl_size] = 0; // add a NULL terminating char to use as a c-string
    }

    // print the entire RX FIFO with 1 buffer
    cout << "Complete RX FIFO: " << rx_fifo << endl;
}
