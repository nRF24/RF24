/*
 * See documentation at https://nRF24.github.io/RF24
 * See License information at root directory of this library
 * Author: Ehsan M.A. (epsi1on)
 */

/**
 * A simple example for troubleshoting connection to NRF24l01 locally.
 * simpley print details and try to call radion.begin() to see if connection to module is OK
 */

#include <ctime>       // time()
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

int main(int argc, char** argv)
{

    // perform hardware check
    if (!radio.begin()) {
        cout << "MCU and radio are not 'talking' successfully with each other. Verify pin connections and wiring." << endl;
        return 0; // quit now
    }
    else
    {
        cout << "Congrats!! MCU and radio are connected" << endl;
        cout << "Here is your NRF module details:" << endl;
    }


    radio.printPrettyDetails();

    return 0;
}
