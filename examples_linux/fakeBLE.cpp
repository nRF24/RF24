/*
 * See documentation at https://tmrh20.github.io/RF24
 * See License information at root directory of this library
 * Author: Brendan Doherty (2bndy5)
 */

/**
 * A simple example of using the nRF24L01 transceiver as a BLE advertising
 * beacon.
 *
 * Original research was done by Dmitry Grinberg; his research can be found at
 * http://dmitry.gr/index.php?r=05.Projects&proj=11.%20Bluetooth%20LE%20fakery
 *
 * Some of this example's code has been taken from Dmitry Grinberg's research,
 * while other bits of code has been derived from the
 * BTLE library by Florian Echtler. If this example seems to limited for your
 * projects needs, we highly recommend Florian Echtler's BTLE library, which
 * can be found in the Arduino IDE and directly on github at
 * https://github.com/floe/BTLE
 */
#include <ctime>       // time()
#include <iostream>    // cin, cout, endl
#include <iomanip>     // setw, setfill
#include <RF24/RF24.h> // RF24, RF24_PA_LOW, RF24_1MBPS, delay()
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

// BLE only operates on 3 specified frequencies channels. It usually employ a
// technique called "channel hopping"
const uint8_t frequency[3] = {2, 26, 80}; // translates {37, 38, 39} per BLE specs
uint8_t currentChannel = 0;               // used for "channel hopping"

// Because the nRF24L01 transceiver wasn't designed for BLE advertisements,
// this technique has some limits. The members of the following struct that
// are not declared as `const` can be adjusted (except checksum).
struct PayloadStruct
{
    const uint8_t deviceFlags = 0x42; // iPhone & Android compatible
    uint8_t blePayloadLen = 27;       // excluding device flags, this byte, and CRC24 at end
    uint8_t mac[6] = {0};             // an arbitrary 6 byte MAC address
    const uint8_t profileFlagsChunkLen = 2;
    const uint8_t profileFlagsChunkType = 1;
    const uint8_t profileFlags = 5; // 5 = discoverable & non-connectable
    const uint8_t nameChunkLen = 4;
    const uint8_t nameChunkType = 8;   // 8 means chunk describes a "short name"
    uint8_t name[3] = {'n', 'R', 'F'}; // must be 3 bytes long in this example
    const uint8_t BatteryServiceChunkLen = 4;
    const uint8_t BatteryServiceChunkType = 0x16; // Battery service data header
    const uint8_t BatteryServiceUUID_lowByte = 0x0F;
    const uint8_t BatteryServiceUUID_highByte = 0x18;
    uint8_t batteryPercent; // we can set this in loop()
    const uint8_t temperatureServiceChunkLen = 7;
    const uint8_t temperatureServiceChunkType = 0x16; // Temperature service data header
    const uint8_t temperatureServiceUUID_lowByte = 0x09;
    const uint8_t temperatureServiceUUID_highByte = 0x18;
    int8_t temperatureInC[4] = {0};           // we set this with temperatureData()
    uint8_t checksum[3] = {0x55, 0x55, 0x55}; // we set this with crc24()
};
PayloadStruct payload; // instantiate the payload

const uint8_t PACKET_LEN = 32;
// we need a buffer to manipulate the data without altering the payload values
uint8_t packet[PACKET_LEN]; // allocate 32 bytes for copying the payload data

void temperatureData(float celsius);
void crc(uint8_t* data, uint8_t len, uint8_t* checksum);
void swapBuf(uint8_t* data, uint8_t len);
void whiten(uint8_t* data, uint8_t len);

bool setup()
{

    // initialize the transceiver on the SPI bus
    if (!radio.begin()) {
        cout << "nRF24L01 is not responding!!" << endl;
        return false;
    }

    // print example's introductory prompt
    cout << "RF24/examples/FakeBLE" << endl;
    cout << "Advertising" << endl;

    // initialize the random number generator and use it to set the MAC address
    // randomSeed(analogRead(A3));  // analog input pin A3 is open/unconnected
    // for (uint8_t i = 0; i < 6; ++i) {
    //   payload.mac[i] = random(255);  // use a random byte
    // }

    // or make the mac address consistent
    const char* mac = "nRF24L"; // using a preset address
    memcpy(payload.mac, mac, 6);

    payload.batteryPercent = 85;
    temperatureData(42.0);

    memcpy(packet, &payload, 32);
    crc(packet, 29, packet + 29);
    cout << "packet: [";
    for (uint8_t i = 0; i < PACKET_LEN; ++i) {
        cout << hex << setw(2) << setfill('0') << (unsigned int)packet[i];
        if (i < (PACKET_LEN - 1)) {
            cout << " ";
        }
    }
    cout << "]" << endl;

    // Set the PA Level low to try preventing power supply related problems
    // because these examples are likely run with nodes in close proximity to
    // each other. BLE specifications allow this to be changed.
    radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default.

    // The following functions disable the features that are incompatible with BLE specifications
    radio.disableDynamicPayloads(); // disable dynamic payloads
    radio.setAutoAck(false);        // disable auto-ack feature
    radio.disableCRC();             // disable CRC checking
    radio.setRetries(0, 0);         // disable auto-retry feature

    // the following functions configure the nRF24L01 to be compatible with BLE
    // specifications.
    radio.setDataRate(RF24_1MBPS);
    radio.setAddressWidth(4);
    const uint8_t bleAddress[] = {0x6B, 0x7D, 0x91, 0x71};
    radio.stopListening(); // powerUp() into TX mode
    radio.openWritingPipe(bleAddress);
    radio.setChannel(frequency[currentChannel]); // we will manage this in the loop()

    return true;
} // setup

void loop()
{
    // broadcast BLE advertisement, hop channel, then wait till next try

    // set the service data
    payload.batteryPercent = 85; // must be a percentage in range [0, 100]
    temperatureData(42.0);       // degree of precision = 2 decimal places

    // prepare the payload for BLE compliance
    memcpy(packet, &payload, 32); // copy payload to a temporary buffer
    crc(packet, 29, packet + 29); // calculate checksum
    whiten(packet, 32);           // whiten (to avoid repeating bit patterns OTA)
    swapBuf(packet, 32);          // reverse the bit order

    // broadcast advertisement payload
    if (radio.write(&packet, 32)) {
        // print something to show the program isn't frozen
        // cout << '*';

        // hop to next frequency
        currentChannel += currentChannel < 2 ? 1 : -2; // increment frequency index
        radio.setChannel(frequency[currentChannel]);   // set new frequency
        delayMicroseconds(150);                        // let the change in channel settle
    }
    else {
        // because auto-ack is disabled, we should never get here.
        cout << "There must be a power supply problem." << endl; // if we do get here
    }

    // slow down transmissions so save power
    delay(500); // change this to your liking (preferably in range [10, 10000] ms)
}

// set the temperature as a 4 byte float
void temperatureData(float celsius)
{
    payload.temperatureInC[3] = 0xFE; // exponent
    int32_t base = (int32_t)(celsius * 100);
    payload.temperatureInC[2] = (base & 0xFF0000) >> 16;
    payload.temperatureInC[1] = (base & 0xFF00) >> 8;
    payload.temperatureInC[0] = (base & 0xFF);
}

/// calculate CRC24 with according to BT Core Spec 4.0, Section 6.B.3.1.1
void crc(uint8_t* data, uint8_t len, uint8_t* dst)
{

    uint8_t v, t, d;
    while (len--) {
        d = *data++;
        for (v = 0; v < 8; v++, d >>= 1) {
            t = dst[0] >> 7;
            dst[0] <<= 1;
            if (dst[1] & 0x80)
                dst[0] |= 1;
            dst[1] <<= 1;
            if (dst[2] & 0x80)
                dst[1] |= 1;
            dst[2] <<= 1;

            if (t != (d & 1)) {
                dst[2] ^= 0x5B;
                dst[1] ^= 0x06;
            }
        }
    }
    swapBuf(dst, 3);

    cout << "crc: [";
    for (uint8_t i = 0; i < 3; ++i) {
        cout << hex << setw(2) << setfill('0') << (unsigned int)dst[i];
        if (i < 2) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

void swapBuf(uint8_t* data, uint8_t len)
{

    uint8_t* buffer = data;

    while (len--) {
        // reverse all the bits for each byte
        uint8_t a = *buffer;
        uint8_t v = 0;

        if (a & 0x80)
            v |= 0x01;
        if (a & 0x40)
            v |= 0x02;
        if (a & 0x20)
            v |= 0x04;
        if (a & 0x10)
            v |= 0x08;
        if (a & 0x08)
            v |= 0x10;
        if (a & 0x04)
            v |= 0x20;
        if (a & 0x02)
            v |= 0x40;
        if (a & 0x01)
            v |= 0x80;

        *(buffer++) = v;
    }
    cout << "swapped: [";
    for (uint8_t i = 0; i < PACKET_LEN; ++i) {
        cout << hex << setw(2) << setfill('0') << (unsigned int)packet[i];
        if (i < (PACKET_LEN - 1)) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

/// whiten the payload so that there are less repeating bits (for OTA stability)
void whiten(uint8_t* data, uint8_t len)
{

    // set whitening coefficient from current channel
    uint8_t coefficient = (currentChannel + 37) | 0x40;

    while (len--) {
        uint8_t res = 0;
        for (uint8_t i = 1; i; i <<= 1) {
            if (coefficient & 0x01) {
                coefficient ^= 0x88;
                res |= i;
            }
            coefficient >>= 1;
        }
        *(data++) ^= res;
    }
    cout << "whitened: [";
    for (uint8_t i = 0; i < PACKET_LEN; ++i) {
        cout << hex << setw(2) << setfill('0') << (unsigned int)packet[i];
        if (i < (PACKET_LEN - 1)) {
            cout << " ";
        }
    }
    cout << "]" << endl;
}

int main()
{
    if (!setup())
        return 1;
    while (true)
        loop();
}
