/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of streaming data from 1 nRF24L01 transceiver to another.
 *
 * This example was written to be used on 2 devices acting as "nodes".
 * Use `ctrl+c` to quit at any time.
 */
#include <cmath>       // abs()
#include <ctime>       // time()
#include <cstring>     // strcmp()
#include <iostream>    // cin, cout, endl
#include <string>      // string, getline()
#include <time.h>      // CLOCK_MONOTONIC_RAW, timespec, clock_gettime()
#include <RF24/RF24.h> // RF24, RF24_PA_LOW, delay()

using namespace std;

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

// For this example, we'll be sending 32 payloads each containing
// 32 bytes of data that looks like ASCII art when printed to the serial
// monitor. The TX node and RX node needs only a single 32 byte buffer.
#define SIZE 32            // this is the maximum for this example. (minimum is 1)
char buffer[SIZE + 1];     // for the RX node
unsigned int counter = 0;  // for counting the number of received payloads
void makePayload(uint8_t); // prototype to construct a payload dynamically
void setRole();            // prototype to set the node's role
void master();             // prototype of the TX node's behavior
void slave();              // prototype of the RX node's behavior
void printHelp(string);    // prototype to function that explain CLI arg usage

// custom defined timer for evaluating transmission time in microseconds
struct timespec startTimer, endTimer;
uint32_t getMicros(); // prototype to get elapsed time in microseconds

int main(int argc, char** argv)
{

    // perform hardware check
    if (!radio.begin()) {
        cout << "radio hardware is not responding!!" << endl;
        return 0; // quit now
    }

    // add a NULL terminating 0 for printing as a c-string
    buffer[SIZE] = 0;

    // Let these addresses be used for the pair of nodes used in this example
    uint8_t address[2][6] = {"1Node", "2Node"};
    //             the TX address^ ,  ^the RX address
    // It is very helpful to think of an address as a path instead of as
    // an identifying device destination

    // to use different addresses on a pair of radios, we need a variable to
    // uniquely identify which address this radio will use to transmit
    bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

    bool foundArgNode = false;
    bool foundArgRole = false;
    bool role = false;
    if (argc > 1) {
        // CLI args are specified
        if ((argc - 1) % 2 != 0) {
            // some CLI arg doesn't have an option specified for it
            printHelp(string(argv[0])); // all args need an option in this example
            return 0;
        }
        else {
            // iterate through args starting after program name
            int a = 1;
            while (a < argc) {
                bool invalidOption = false;
                if (strcmp(argv[a], "-n") == 0 || strcmp(argv[a], "--node") == 0) {
                    // "-n" or "--node" has been specified
                    foundArgNode = true;
                    if (argv[a + 1][0] - 48 <= 1) {
                        radioNumber = (argv[a + 1][0] - 48) == 1;
                    }
                    else {
                        // option is invalid
                        invalidOption = true;
                    }
                }
                else if (strcmp(argv[a], "-r") == 0 || strcmp(argv[a], "--role") == 0) {
                    // "-r" or "--role" has been specified
                    foundArgRole = true;
                    if (argv[a + 1][0] - 48 <= 1) {
                        role = (argv[a + 1][0] - 48) == 1;
                    }
                    else {
                        // option is invalid
                        invalidOption = true;
                    }
                }
                if (invalidOption) {
                    printHelp(string(argv[0]));
                    return 0;
                }
                a += 2;
            } // while
            if (!foundArgNode && !foundArgRole) {
                // no valid args were specified
                printHelp(string(argv[0]));
                return 0;
            }
        } // else
    }     // if

    // print example's name
    cout << argv[0] << endl;

    if (!foundArgNode) {
        // Set the radioNumber via the terminal on startup
        cout << "Which radio is this? Enter '0' or '1'. Defaults to '0' ";
        string input;
        getline(cin, input);
        radioNumber = input.length() > 0 && (uint8_t)input[0] == 49;
    }

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit a float
    radio.setPayloadSize(SIZE); // default value is the maximum 32 bytes

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

    // ready to execute program now
    if (!foundArgRole) { // if CLI arg "-r"/"--role" was not specified
        setRole();       // calls master() or slave() based on user input
    }
    else {                         // if CLI arg "-r"/"--role" was specified
        role ? master() : slave(); // based on CLI arg option
    }
    return 0;
}

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
} // setRole()

/**
 * make this node act as the transmitter
 */
void master()
{
    radio.stopListening(); // put radio in TX mode

    unsigned int failures = 0; // keep track of failures
    uint8_t i = 0;
    clock_gettime(CLOCK_MONOTONIC_RAW, &startTimer); // start the timer
    while (i < SIZE) {
        makePayload(i);
        if (!radio.writeFast(&buffer, SIZE)) {
            failures++;
            radio.reUseTX();
        }
        else {
            i++;
        }

        if (failures >= 100) {
            // most likely no device is listening for the data stream
            cout << "Too many failures detected. ";
            cout << "Aborting at payload " << buffer[0];
            break;
        }
    } // while

    uint32_t elapsedTime = getMicros(); // end the timer
    cout << "Time to transmit data = ";
    cout << elapsedTime;         // print the timer result
    cout << " us. " << failures; // print number of retries
    cout << " failures detected. Leaving TX role." << endl;
} // master

/**
 * make this node act as the receiver
 */
void slave()
{

    counter = 0;
    radio.startListening();                   // put radio in RX mode
    time_t startTimer = time(nullptr);        // start a timer
    while (time(nullptr) - startTimer < 6) {  // use 6 second timeout
        if (radio.available()) {              // is there a payload
            radio.read(&buffer, SIZE);        // fetch payload from FIFO
            cout << "Received: " << buffer;   // print the payload's value
            cout << " - " << counter << endl; // print the counter
            counter++;                        // increment counter
            startTimer = time(nullptr);       // reset timer
        }
    }
    radio.stopListening(); // use TX mode for idle behavior

    cout << "Nothing received in 6 seconds. Leaving RX role." << endl;
}

/**
 * Make a single payload based on position in stream.
 * This example employs this function to save on memory allocated.
 */
void makePayload(uint8_t i)
{

    // let the first character be an identifying alphanumeric prefix
    // this lets us see which payload didn't get received
    buffer[0] = i + (i < 26 ? 65 : 71);
    for (uint8_t j = 0; j < SIZE - 1; ++j) {
        char chr = j >= (SIZE - 1) / 2 + abs((SIZE - 1) / 2 - i);
        chr |= j < (SIZE - 1) / 2 - abs((SIZE - 1) / 2 - i);
        buffer[j + 1] = chr + 48;
    }
}

/**
 * Calculate the elapsed time in microseconds
 */
uint32_t getMicros()
{
    // this function assumes that the timer was started using
    // `clock_gettime(CLOCK_MONOTONIC_RAW, &startTimer);`

    clock_gettime(CLOCK_MONOTONIC_RAW, &endTimer);
    uint32_t seconds = endTimer.tv_sec - startTimer.tv_sec;
    uint32_t useconds = (endTimer.tv_nsec - startTimer.tv_nsec) / 1000;

    return ((seconds)*1000 + useconds) + 0.5;
}

/**
 * print a manual page of instructions on how to use this example's CLI args
 */
void printHelp(string progName)
{
    cout << "usage: " << progName << " [-h] [-n {0,1}] [-r {0,1}]\n\n"
         << "A simple example of streaming data from 1 nRF24L01 transceiver to another.\n"
         << "\nThis example was written to be used on 2 devices acting as 'nodes'.\n"
         << "\noptional arguments:\n  -h, --help\t\tshow this help message and exit\n"
         << "  -n {0,1}, --node {0,1}\n\t\t\tthe identifying radio number\n"
         << "  -r {0,1}, --role {0,1}\n\t\t\t'1' specifies the TX role."
         << " '0' specifies the RX role." << endl;
}
