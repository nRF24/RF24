/*
 * Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 * Updated 2020 TMRh20
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

/**
 * Channel scanner and continuous carrier wave output
 * 
 * There are 126 channels available, 1MHz wide, starting at 2400MHz. This example will scan through all 126 channels, 
 * listening for 128 microseconds on each channel for a carrier wave. The more carrier waves detected during the channel sweep, the 
 * higher the hexadecimal value displayed under that channel on the serial monitor. The channel numbers are displayed in hexiecimal in
 * a header two lines tall, where 0x00 is on the left and 0x7D is on the right.
 *
 * While any 2.4GHz device can trigger this carrier wave detection, a second NRF24L01+ device can be configured to outptu a constant 
 * carrier wave by sending the character "g" over the serial monitor. Output power and channel can be adjusted in the #defines below.
 *
 * Originally inspired by cpixip,
 * See https://forum.arduino.cc/t/poor-mans-2-4-ghz-scanner/54846/39
*/

#include "RF24.h"

#define CARRIER_POWER RF24_PA_LOW  //can be RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
#define CARRIER_CHANNEL 40         //0-125

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 for CE and CSN
RF24 radio(5, 6);

// Channel info
const uint8_t num_channels = 126;
uint8_t values[num_channels];  //number of times a value is detected on each channel during the scan

const int num_reps = 100;  //number of times to scan through channels
bool constCarrierMode = 0;

void setup(void) {

  // Print preamble
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println(F("rRF24/examples/scanner/"));

  // Setup and configure rf radi
  /*
  if(!radio.begin())
  {
    Serial.println("Can't connect to radio");
    while(1);
  }

  */

  radio.setAutoAck(false);
  radio.stopListening();
  radio.printDetails();

  // Print out header, high then low digit
  for(uint8_t i = 0; i < num_channels; i++) {
    Serial.print(i >> 4, HEX);
  }
  Serial.println();

  for(uint8_t i = 0; i < num_channels; i++) {
    Serial.print(i & 0xf, HEX);
  }
  Serial.println();
}

// Loop
void loop(void) {
  //check for g to begin carrier wave output
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'g') {
      constCarrierMode = 1;
      radio.stopListening();
      delay(2);
      Serial.println("Starting Carrier Out, send \"e\" to return to scanning");
      radio.startConstCarrier(CARRIER_POWER, CARRIER_CHANNEL);
    } else if (c == 'e') {
      constCarrierMode = 0;
      radio.stopConstCarrier();
      Serial.println("Stopping Carrier Out");
    }
  }

  if (constCarrierMode == 0) {
    // Clear measurement values
    memset(values, 0, sizeof(values));

    // Iterate through every channel sequentially, num_reps times
    for (uint8_t i = 0; i < num_reps; i++) {
      for (uint8_t channel = 0; channel < num_channels; channel++) {
        // Select this channel
        radio.setChannel(channel);

        //128uS is the minimum listen time required to detect a valid carrier wave
        radio.startListening();
        delayMicroseconds(128);
        radio.stopListening();

        // Did we get a carrier?
        if (radio.testCarrier()) {
          ++values[channel];
        }
      }
    }

    // Print out channel measurements, mapped to a single hex digit
    for(uint8_t i = 0; i < num_channels; i++){
      if (values[i])
        Serial.print(min(0xf, values[i]), HEX);
      else
        Serial.print(F("-"));
    }
    Serial.println();
  }
}
