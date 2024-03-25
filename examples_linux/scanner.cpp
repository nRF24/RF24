/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.


 03/17/2013 : Charles-Henri Hallard (http://hallard.me)
              Modified to use with Arduipi board http://hallard.me/arduipi
                          Changed to use modified bcm2835 and RF24 library
 07/12/2022: Modified to be more promiscuous using reverse engineering tactics.
 */

/**
 * Channel scanner
 *
 * Example to detect interference on the various channels available.
 * This is a good diagnostic tool to check whether you're picking a
 * good channel for your application.
 *
 * Inspired by cpixip.
 * See https://forum.arduino.cc/t/poor-mans-2-4-ghz-scanner/54846
 *
 * See documentation at https://nRF24.github.io/RF24
 */

/*
 * How to read the output:
 * - The header is a list of supported channels in decimal written vertically.
 * - Each column corresponding to the vertical header is a hexadecimal count of
 *   detected signals (max is 15 or 'f').
 *
 * The following example
 *    000
 *    111
 *    789
 *    ~~~   <- just a divider between the channel's vertical labels and signal counts
 *    1-2
 * can be interpreted as
 * - 1 signal detected on channel 17
 * - 0 signals (denoted as '-') detected on channel 18
 * - 2 signals detected on channel 19
 *
 * Each line of signal counts represent 100 passes of the supported spectrum.
 */
#include <string>   // string, getline()
#include <iostream> // cout, endl, flush, cin
#include <RF24/RF24.h>

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

// Channel info
const uint8_t num_channels = 126; // 0-125 are supported
uint8_t values[num_channels];     // the array to store summary of signal counts per channel

// To detect noise, we'll use the worst addresses possible (a reverse engineering tactic).
// These addresses are designed to confuse the radio into thinking
// that the RF signal's preamble is part of the packet/payload.
const uint8_t noiseAddress[][6] = {{0x55, 0x55}, {0xAA, 0xAA}, {0x0A, 0xAA}, {0xA0, 0xAA}, {0x00, 0xAA}, {0xAB, 0xAA}};

const int num_reps = 100; // number of passes for each scan of the entire spectrum

void printHeader(); // prototype function for printing the channels' header

int main(int argc, char** argv)
{
    // print example's name
    cout << argv[0] << endl;

    // Setup the radio
    if (!radio.begin()) {
        cout << "Radio hardware not responding!" << endl;
        return 1;
    }

    // print a line that should not be wrapped
    cout << "\n!!! This example requires a width of at least 126 characters. "
         << "If this text uses multiple lines, then the output will look bad."
         << endl;

    // set the data rate
    cout << "Select your Data Rate. "
         << "Enter '1' for 1 Mbps, '2' for 2 Mbps, '3' for 250 kbps. "
         << "Defaults to 1Mbps."
         << endl;
    string dataRate = "";
    getline(cin, dataRate);
    if (dataRate.length() >= 1 && static_cast<char>(dataRate[0]) == '2') {
        cout << "Using 2 Mbps." << endl;
        radio.setDataRate(RF24_2MBPS);
    }
    else if (dataRate.length() >= 1 && static_cast<char>(dataRate[0]) == '3') {
        cout << "Using 250 kbps." << endl;
        radio.setDataRate(RF24_250KBPS);
    }
    else {
        cout << "Using 1 Mbps." << endl;
        radio.setDataRate(RF24_1MBPS);
    }

    // configure the radio
    radio.setAutoAck(false);  // Don't acknowledge arbitrary signals
    radio.disableCRC();       // Accept any signal we find
    radio.setAddressWidth(2); // A reverse engineering tactic (not typically recommended)
    for (uint8_t i = 0; i < 6; ++i) {
        radio.openReadingPipe(i, noiseAddress[i]);
    }

    // Get into standby mode
    radio.startListening();
    radio.stopListening();
    radio.flush_rx();
    // radio.printPrettyDetails();
    // print the vertical header
    printHeader();

    // forever loop
    while (1) {
        // Clear measurement values
        memset(values, 0, sizeof(values));

        // Scan all channels num_reps times
        int rep_counter = num_reps;
        while (rep_counter--) {

            for (int i = 0; i < num_channels; ++i) {

                // Select this channel
                radio.setChannel(i);

                // Listen for a little
                radio.startListening();
                delayMicroseconds(130);
                bool foundSignal = radio.testRPD();
                radio.stopListening();

                // Did we get a signal?
                if (foundSignal || radio.testRPD() || radio.available()) {
                    ++values[i];
                    radio.flush_rx(); // discard packets of noise
                }

                // output the summary/snapshot for this channel
                if (values[i]) {
                    // Print out channel measurements, clamped to a single hex digit
                    cout << hex << min(0xF, static_cast<int>(values[i])) << flush;
                }
                else {
                    cout << '-' << flush;
                }
            }
            cout << '\r' << flush;
        }
        cout << endl;
    }

    return 0;
}

void printHeader()
{
    // print the hundreds digits
    for (uint8_t i = 0; i < num_channels; ++i)
        cout << static_cast<int>(i / 100);
    cout << endl;

    // print the tens digits
    for (uint8_t i = 0; i < num_channels; ++i)
        cout << static_cast<int>((i % 100) / 10);
    cout << endl;

    // print the singles digits
    for (uint8_t i = 0; i < num_channels; ++i)
        cout << static_cast<int>(i % 10);
    cout << endl;

    // print the header's divider
    for (uint8_t i = 0; i < num_channels; ++i)
        cout << '~';
    cout << endl;
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
