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
#include <SPI.h>
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(6, 5); // using pin 7 for the CE pin, and pin 8 for the CSN pin

// BLE only operates on 3 specified frequencies channels. It usually employ a
// technique called "channel hopping"
const uint8_t frequency[3] = {2, 26, 80}; // translates {37, 38, 39} per BLE
uint8_t currentChannel = 0;               // used for "channel hopping"

// Because the nRF24L01 transceiver wasn't designed for BLE advertisements,
// this technique has some limits. The members of the following struct that
// are not declared as `const` can be adjusted (except checksum).
struct PayloadStruct {
  const uint8_t header[2] = {0x42, 27};                   // iPhone & Android compatible
  uint8_t mac[6];                                         // an arbitrary 6 byte MAC address
  const uint8_t flags[3] = {0x02, 0x01, 0x05};            // 0x05 = discoverable & non-connectable
  const uint8_t namePrefix[2] = {0x04, 0x08};             // appears as "short name"
  uint8_t name[3] = {'n', 'R', 'F'};                      // must be 3 bytes long in this example
  const uint8_t prefixBatt[4] = {0x04, 0x16, 0x0F, 0x18}; // Battery service data header
  uint8_t batteryPercent;                                 // we can set this in loop()
  const uint8_t prefixTemp[4] = {0x07, 0x16, 0x09, 0x18}; // temperature service data header
  int8_t temperatureInC[4];                               // we set this with temperatureData()
  uint8_t checksum[3] = {0x55, 0x55, 0x55};               // we set this with crc24()
};
PayloadStruct payload;                                    // instantiate the payload

// we a buffer to manipulate the data without altering the payload values
uint8_t packet[32]; // allocate 32 bytes for copying the payload data

void temperatureData(float celcius);
void crc(uint8_t *data, uint8_t len, uint8_t* checksum);
void swapbuf(uint8_t *data, uint8_t len);
void whiten(uint8_t *data, uint8_t len);

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("nRF24L01 is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  // print example's introductory prompt
  Serial.println(F("RF24/examples/FakeBLE"));
  Serial.println(F("Advertising"));


  // initialize the random number generator and use it to set the MAC address
  // randomSeed(analogRead(A3));     // analog input pin A3 is open/unconnected
  // for (uint8_t i = 0; i < 6; ++i)
  //   payload.mac[i] = random(255); // use a random byte

  // or make the mac address consistent
  uint8_t mac[] = {0xa1, 0xb2, 0xc3, 0xd4, 0xe5, 0xf6};
  for (uint8_t i = 0; i < 6; ++i)
    payload.mac[i] = mac[i]; // use a preset address

  payload.batteryPercent = 85;
  temperatureData(42.0);

  memcpy(packet, &payload, 32);
  crc(packet, 28, packet + 29);
  for (uint8_t i = 0; i < 32; ++i) {
    Serial.print("packet[");
    Serial.print(i);
    Serial.print("]");
    Serial.println(packet[i], HEX);
  }

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other. BLE specifications allow this to be changed.
  radio.setPALevel(RF24_PA_LOW);               // RF24_PA_MAX is default.

  // The following functions disable the features that are incompatible with BLE specifications
  radio.disableDynamicPayloads();              // disable dynamic payloads
  radio.setAutoAck(false);                     // disable auto-ack feature
  radio.disableCRC();                          // disable CRC checking
  radio.setRetries(0, 0);                      // disable auto-retry feature

  // the following functions configure the nRF24L01 to be compatible with BLE
  // specifications.
  radio.setDataRate(RF24_1MBPS);
  radio.setAddressWidth(4);
  radio.openWritingPipe(0x6B7D9171);
  radio.setChannel(frequency[currentChannel]); // we will manage this in the loop()
  radio.stopListening();                       // powerUp() into TX mode
} // setup

void loop() {
  // broadcast BLE advertisement, hop channel, then wait till next try

  // set the service data
  payload.batteryPercent = 85; // must be a percentage in range [0, 100]
  temperatureData(42.0);        // degree of percision = 2 decimal places

  // prepare the payload for BLE compliance
  memcpy(packet, &payload, 32); // copy payload to a temporary buffer
  crc(packet, 29, packet + 29); // calculate checksum
  whiten(packet, 32);           // whiten (to avoid repeating bit patterns OTA)
  swapbuf(packet, 32);          // reverse the bit order

  // broadcast advertisement payload
  if (radio.write(&packet, 32)) {
    // print something to show the program isn't frozen
    // Serial.println('*');

    // hop to next frequency
    currentChannel += currentChannel < 2 ? 1 : -2; // increment frequency index
    radio.setChannel(frequency[currentChannel]);   // set new frequency
    delayMicroseconds(150);                        // let the change in channel settle

  } else {
    // due to all the features that disabled, we will never get here.
    // Serial.println(F("There must be a power supply problem.")); // if we do get here
  }

  // slow down transmissions so save power
  delay(500); // change this to your liking (preferrably in range [10, 10000] ms)
}

void temperatureData(float celcius) {
  // set the temperature as a 4 byte float
  payload.temperatureInC[3] = ((int8_t)(-2) & 0xFF); // exponent
  int32_t base = (int32_t)(celcius * 100);
  payload.temperatureInC[2] = (base & 0xFF0000) >> 16;
  payload.temperatureInC[1] = (base & 0xFF00) >> 8;
  payload.temperatureInC[0] = (base & 0xFF);
}

void crc(uint8_t *data, uint8_t len, uint8_t* dst) {
  // calculate CRC24 with according to BT Core Spec 4.0, Section 6.B.3.1.1

  uint8_t v, t, d;
  while (len--) {
    d = *data++;
    for (v = 0; v < 8; v++, d >>= 1) {
      t = dst[0] >> 7;
      dst[0] <<= 1;
      if (dst[1] & 0x80) dst[0] |= 1;
      dst[1] <<= 1;
      if (dst[2] & 0x80) dst[1] |= 1;
      dst[2] <<= 1;

      if (t != (d & 1)) {
        dst[2] ^= 0x5B;
        dst[1] ^= 0x06;
      }
    }
  }
  // for (uint8_t i = 0; i < 3; ++i) {
  //   Serial.print("calc'd crc[");
  //   Serial.print(i);
  //   Serial.print("]");
  //   Serial.println(dst[i], HEX);
  // }
}

void swapbuf(uint8_t *data, uint8_t len) {

  uint8_t *buffer = data;

  while (len--) {
    // reverse all the bits for each byte
    uint8_t a = *buffer;
    uint8_t v = 0;

    if (a & 0x80) v |= 0x01;
    if (a & 0x40) v |= 0x02;
    if (a & 0x20) v |= 0x04;
    if (a & 0x10) v |= 0x08;
    if (a & 0x08) v |= 0x10;
    if (a & 0x04) v |= 0x20;
    if (a & 0x02) v |= 0x40;
    if (a & 0x01) v |= 0x80;

    *(buffer++) = v;
  }
  // for (uint8_t i = 0; i < 31; ++i) {
  //   Serial.print("swapped[");
  //   Serial.print(i);
  //   Serial.print("]");
  //   Serial.println(packet[i], HEX);
  // }
}

void whiten(uint8_t *data, uint8_t len) {
  // whiten the payload so that there are less repeating bits (for OTA stability)

  // initialize LFSR with current channel, set bit 6
  uint8_t lfsr = (currentChannel + 37) | 0x40;

  while (len--) {
    uint8_t res = 0;
    // LFSR in "wire bit order"
    for (uint8_t i = 1; i; i <<= 1) {
      if (lfsr & 0x01) {
        lfsr ^= 0x88;
        res |= i;
      }
      lfsr >>= 1;
    }
    *(data++) ^= res;
  }
  // for (uint8_t i = 0; i < 31; ++i) {
  //   Serial.print("whitened[");
  //   Serial.print(i);
  //   Serial.print("]");
  //   Serial.println(packet[i], HEX);
  // }
}
