/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of sending data from as many as 6 nRF24L01 transceivers to
 * 1 receiving transceiver. This technique is trademarked by
 * Nordic Semiconductors as "MultiCeiver".
 *
 * This example was written to be used on up to 6 devices acting as TX nodes &
 * only 1 device acting as the RX node (that's a maximum of 7 devices).
 * Use `ctrl+c` to quit at any time.
 */
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

// For this example, we'll be using 6 addresses; 1 for each TX node
// It is very helpful to think of an address as a path instead of as
// an identifying device destination
// Notice that the last byte is the only byte that changes in the last 5
// addresses. This is a limitation of the nRF24L01 transceiver for pipes 2-5
// because they use the same first 4 MSBytes from pipe 1.
uint8_t address[6][5] = {{0x78, 0x78, 0x78, 0x78, 0x78},
                         {0xF1, 0xB6, 0xB5, 0xB4, 0xB3},
                         {0xCD, 0xB6, 0xB5, 0xB4, 0xB3},
                         {0xA3, 0xB6, 0xB5, 0xB4, 0xB3},
                         {0x0F, 0xB6, 0xB5, 0xB4, 0xB3},
                         {0x05, 0xB6, 0xB5, 0xB4, 0xB3}};

// For this example, we'll be using a payload containing
// a node ID number and a single integer number that will be incremented
// on every successful transmission.
// Make a data structure to use as a payload.
struct PayloadStruct
{
    unsigned int nodeID;
    unsigned int payloadID;
};
PayloadStruct payload;

void setRole();            // prototype to set the node's role
void master(unsigned int); // prototype of a TX node's behavior
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

    // to use different addresses on a pair of radios, we need a variable to
    // uniquely identify which address this radio will use to transmit
    unsigned int nodeNumber = 'R'; // integers 0-5 = TX node; character 'R' or integer 82 = RX node

    bool foundArgNode = false;
    if (argc > 1) {
        if ((argc - 1) != 2) {
            // CLI arg "-n"/"--node" needs an option specified for it
            // only 1 arg is expected, so only traverse the first "--arg option" pair
            printHelp(string(argv[0]));
            return 0;
        }
        else if (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--node") == 0) {
            // "-n" or "--node" has been specified
            foundArgNode = true;
            if ((argv[2][0] - 48) < 6 && (argv[2][0] - 48) >= 0) {
                nodeNumber = argv[2][0] - 48;
            }
            else if (argv[2][0] == 'R' || argv[2][0] == 'r') {
                nodeNumber = 'R';
            }
            else {
                printHelp(string(argv[0]));
                return 0;
            }
        }
        else {
            // "-n"/"--node" arg was not specified
            printHelp(string(argv[0]));
            return 0;
        }
    }

    // print example's name
    cout << argv[0] << endl;

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other.
    radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

    // save on transmission time by setting the radio to only transmit the
    // number of bytes we need to transmit a float
    radio.setPayloadSize(sizeof(payload)); // 2x int datatype occupy 8 bytes

    // For debugging info
    // radio.printDetails();       // (smaller) function that prints raw register values
    // radio.printPrettyDetails(); // (larger) function that prints human readable data

    // ready to execute program now
    if (!foundArgNode) {
        setRole(); // calls master() or slave() based on user input
    }
    else {
        nodeNumber < 6 ? master(nodeNumber) : slave();
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
        cout << "*** Enter a number between 0 and 5 (inclusive) to act as\n";
        cout << "    a unique node number that transmits to the RX node.\n";
        cout << "*** PRESS 'R' to begin receiving from the other nodes\n";
        cout << "*** PRESS 'Q' to exit" << endl;
        getline(cin, input);
        if (input.length() >= 1) {
            unsigned int toNumber = (unsigned int)(input[0]) - 48;
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
    }               // while
} // setRole

/**
 * act as unique TX node identified by the `role` number
 */
void master(unsigned int role)
{
    // set the payload's nodeID & reset the payload's identifying number
    payload.nodeID = role;
    payload.payloadID = 0;

    // set the TX address of the RX node for use on the TX pipe (pipe 0)
    radio.stopListening(address[role]); // put radio in TX mode

    // According to the datasheet, the auto-retry features's delay value should
    // be "skewed" to allow the RX node to receive 1 transmission at a time.
    // So, use varying delay between retry attempts and 15 (at most) retry attempts
    radio.setRetries(((role * 3) % 12) + 3, 15); // maximum value is 15 for both args

    unsigned int failures = 0;
    while (failures < 6) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &startTimer);      // start the timer
        bool report = radio.write(&payload, sizeof(payload)); // transmit & save the report
        uint32_t timerElapsed = getMicros();                  // end the timer

        if (report) {
            // payload was delivered
            cout << "Transmission of PayloadID ";
            cout << payload.payloadID;             // print payload number
            cout << " as node " << payload.nodeID; // print node number
            cout << " successful! Time to transmit = ";
            cout << timerElapsed << " us" << endl; // print the timer result
        }
        else {
            // payload was not delivered
            failures++;
            cout << "Transmission failed or timed out" << endl;
        }
        payload.payloadID++; // increment payload number

        // to make this example readable in the terminal
        delay(1000); // slow transmissions down by 1 second
    }                // while
    cout << failures << " failures detected. Leaving TX role." << endl;
} // master

/**
 * act as the RX node that receives from up to 6 other TX nodes
 */
void slave()
{

    // Set the addresses for all pipes to TX nodes
    for (uint8_t i = 0; i < 6; ++i)
        radio.openReadingPipe(i, address[i]);

    radio.startListening(); // put radio in RX mode

    time_t startTimer = time(nullptr);       // start a timer
    while (time(nullptr) - startTimer < 6) { // use 6 second timeout
        uint8_t pipe;
        if (radio.available(&pipe)) {                             // is there a payload? get the pipe number that received it
            uint8_t bytes = radio.getPayloadSize();               // get the size of the payload
            radio.read(&payload, bytes);                          // fetch payload from FIFO
            cout << "Received " << (unsigned int)bytes;           // print the size of the payload
            cout << " bytes on pipe " << (unsigned int)pipe;      // print the pipe number
            cout << " from node " << payload.nodeID;              // print the payload's origin
            cout << ". PayloadID: " << payload.payloadID << endl; // print the payload's number
            startTimer = time(nullptr);                           // reset timer
        }
    }
    cout << "Nothing received in 6 seconds. Leaving RX role." << endl;
} // slave

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
    cout << "usage: " << progName << " [-h] [-n {0,1,2,3,4,5,r,R}]\n\n"
         << "A simple example of sending data from as many as 6 nRF24L01 transceivers to\n"
         << "1 receiving transceiver. This technique is trademarked by\n"
         << "Nordic Semiconductors as 'MultiCeiver'.\n"
         << "\nThis example was written to be used on up to 6 devices acting as TX nodes with\n"
         << "another device acting as a RX node (that's a total of 7 devices).\n"
         << "\noptional arguments:\n  -h, --help\t\tshow this help message and exit\n"
         << "  -n {0,1,2,3,4,5,r,R}, --node {0,1,2,3,4,5,r,R}"
         << "\n\t\t\t0-5 specifies the identifying node ID number for the TX role."
         << "\n\t\t\t'r' or 'R' specifies the RX role." << endl;
}
