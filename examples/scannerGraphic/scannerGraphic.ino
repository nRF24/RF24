/*
 * Copyright (C) 2022 Brendan Doherty <2bndy5@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

/*
 * This example uses 1 of 2 different popular displays. To control which display to use,
 * comment/uncomment the lines below that define
 * - `SPI_DISPLAY`: This requires the "Adafruit ST7735 and ST7789 Library" installed
 * - `I2C_DISPLAY`: This requires the "Adafruit SSD1306" library installed
 * 
 * Use the Arduino Library manager to ensure the required libraries are installed.
 * By default, this sketch uses the SPI_DISPLAY (ST7789). Using both displays at the same
 * time is not supported by this sketch.
 * 
 * NOTES:
 *     The `SCREEN_HEIGHT` and `SCREEN_WIDTH` defines may need to be adjusted according
 *     to your display module's capability.
 *
 *     The SPI_DISPLAY ues its own pins defined by `TFT_CS`, `TFT_DC`, and the
 *     optional `TFT_RST` (see below). The SPI bus is shared between radio and display,
 *     so the display's CS pin must be connected as specified by `TFT_CS`.
 *     If your ST7789 display does not have a CS pin, then further modification must
 *     be made so it does not use the same SPI bus that the radio uses.
 * 
 *     `DEBUGGING` can be enabled (uncommented) to show Serial output. This is just a
 *     convenience for troubleshooting and advanced development. See our other
 *     RF24/scanner example that only uses the Serial Monitor instead of a graphic
 *     display.
 */
#include <Adafruit_GFX.h>  // dependency of Adafruit display libraries
#include "RF24.h"


/********************************************************************
 * Instantiate the radio and app-specific attributes
 ********************************************************************/

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);

// To detect noise, we'll use the worst addresses possible (a reverse engineering tactic).
// These addresses are designed to confuse the radio into thinking
// that the RF signal's preamble is part of the packet/payload.
const uint8_t noiseAddress[][2] = { { 0x55, 0x55 }, { 0xAA, 0xAA }, { 0xA0, 0xAA }, { 0xAB, 0xAA }, { 0xAC, 0xAA }, { 0xAD, 0xAA } };

// keep a cache of history for peak decay
const uint8_t CACHE_MAX = 4;
const uint8_t num_channels = 126;  // 0-125 are supported
bool history[num_channels][CACHE_MAX];

/********************************************************************
 * Instantiate the appropriate display
 ********************************************************************/

// uncomment either or none of the following to use the desired display:

// #define I2C_DISPLAY  // using the SSD1306
#define SPI_DISPLAY  // using ST7789

// create our `display` objects according to the above defines
#ifdef I2C_DISPLAY

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D  // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BLACK SSD1306_BLACK
#define WHITE SSD1306_WHITE
#define REFRESH ({ display.display(); })
#define CLEAR_DISPLAY ({ display.clearDisplay(); })

#elif defined(SPI_DISPLAY)

#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789

#define TFT_CS 2
#define TFT_RST -1  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 3

#define SCREEN_WIDTH 240   // TFT display width, in pixels
#define SCREEN_HEIGHT 135  // TFT display height, in pixels

// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define BLACK ST77XX_BLACK
#define WHITE ST77XX_WHITE
#define REFRESH
#define CLEAR_DISPLAY ({ display.fillScreen(BLACK); })

#endif  // if defined(I2C_DISPLAY) || defined(SPI_DISPLAY)

#define X_OFFSET (SCREEN_WIDTH - (num_channels + 2)) / 2

/********************************************************************
 * Configure debugging on Serial output
 ********************************************************************/

// #define DEBUGGING  // uncomment to enable Serial output

#ifdef DEBUGGING
#include "printf.h"
#define SERIAL_DEBUG(x) ({ x; })
#else
#define SERIAL_DEBUG(x)
#endif

/********************************************************************
 * Setup the app
 ********************************************************************/
void setup(void) {

#ifdef DEBUGGING
  // Print preamble
  Serial.begin(115200);
  while (!Serial) {
    // some boards need this to wait for Serial connection
  }
  Serial.println(F("RF24/examples/scannerGraphic"));
#endif

#ifdef I2C_DISPLAY
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    SERIAL_DEBUG(Serial.println(F("SSD1306 allocation failed")););
    while (true) {
      // Don't proceed, loop forever
    }
  }
#elif defined(SPI_DISPLAY)
  // use this initializer for a 1.14" 240x135 TFT:
  display.init(SCREEN_HEIGHT, SCREEN_WIDTH);  // Init ST7789 240x135
  display.setRotation(1);                     // put in landscape mode
#endif

  // Clear the buffer
  CLEAR_DISPLAY;

  // Setup and configure rf radio
  if (!radio.begin()) {
    SERIAL_DEBUG(Serial.println(F("radio hardware not responding!")););
    display.setCursor(1, 1);
    display.setTextColor(WHITE);
    display.printf("radio hardware\nnot responding!");
    REFRESH;
    while (true) {
      // hold in an infinite loop
    }
  }
  displayChartAxis();

  radio.setAutoAck(false);   // Don't acknowledge arbitrary signals
  radio.disableCRC();        // accept any signal we find
  radio.setAddressWidth(2);  // a reverse engineering tactic (not typically recommended)
  for (uint8_t i = 0; i < 6; ++i) {
    radio.openReadingPipe(i, noiseAddress[i]);
  }

  // set the data rate
#ifdef DEBUGGING
  unsigned long inputTimeout = millis() + 7000;
  Serial.print(F("Select your Data Rate. "));
  Serial.println(F("Enter '1' for 1Mbps, '2' for 2Mbps, '3' for 250kbps. Defaults to 1 Mbps."));
  while (!Serial.available() && millis() < inputTimeout) {
    // Wait for user input. Timeout after 7 seconds.
  }
  char dataRate = !Serial.available() ? '1' : Serial.parseInt();
#else
  char dataRate = '1';
#endif
  if (dataRate == '2') {
    SERIAL_DEBUG(Serial.println(F("Using 2 Mbps.")););
    radio.setDataRate(RF24_2MBPS);
  } else if (dataRate == '3') {
    SERIAL_DEBUG(Serial.println(F("Using 250 kbps.")););
    radio.setDataRate(RF24_250KBPS);
  } else {  // dataRate == '1' or invalid values
    SERIAL_DEBUG(Serial.println(F("Using 1 Mbps.")););
    radio.setDataRate(RF24_1MBPS);
  }

  // Get into standby mode
  radio.startListening();
  radio.stopListening();
  radio.flush_rx();

  // initialize our history for showing cumulative peaks
  for (uint8_t i = 0; i < num_channels; ++i) {
    for (uint8_t j = 0; j < CACHE_MAX; ++j) {
      history[i][j] = false;
    }
  }
}

/********************************************************************
 * Make the app loop forever
 ********************************************************************/
void loop(void) {
  // Print out channel measurements, clamped to a single hex digit
  for (int i = 0; i < num_channels; ++i) {
    bool foundSignal = scanChannel(i);
    // uint8_t chart
    uint8_t historicCount = historyPush(i, foundSignal);
    uint8_t x = i + 1 + X_OFFSET;
    uint8_t chartHeight = SCREEN_HEIGHT - 10;
    display.drawLine(x, 0, x, chartHeight, BLACK);
    if (historicCount) {
      uint8_t barHeight = chartHeight * historicCount / CACHE_MAX;
      display.drawLine(x, SCREEN_HEIGHT - 10, x, SCREEN_HEIGHT - 10 - barHeight, WHITE);
    }
  }
  REFRESH;
}  // end loop()

/******************************************************************** 
 * Scan a specified channel and return the resulting flag
 ********************************************************************/
bool scanChannel(uint8_t channel) {
  radio.setChannel(channel);

  // Listen for a little
  radio.startListening();
  delayMicroseconds(130);
  bool foundSignal = radio.testRPD();
  radio.stopListening();

  // Did we get a signal?
  if (foundSignal || radio.testRPD() || radio.available()) {
    radio.flush_rx();  // discard packets of noise
    return true;
  }
  return false;
}

/********************************************************************
 * Push new scan result for a channel into the history.
 * @returns The count of historic signals found (including pushed result)
 ********************************************************************/
uint8_t historyPush(uint8_t channel, bool value) {
  uint8_t sum = 0;
  for (uint8_t i = 0; i < CACHE_MAX - 1; ++i) {
    history[channel][i] = history[channel][i + 1];
    sum += history[channel][i];
  }
  history[channel][CACHE_MAX - 1] = value;
  return sum + value;
}

/********************************************************************
 * Draw the chart axis and labels
 ********************************************************************/
void displayChartAxis() {
  // draw base line
  display.drawLine(X_OFFSET, SCREEN_HEIGHT - 8, X_OFFSET + 127, SCREEN_HEIGHT - 8, WHITE);

  // draw base line border
  display.drawLine(X_OFFSET, SCREEN_HEIGHT - 1, X_OFFSET, SCREEN_HEIGHT - 12, WHITE);
  display.drawLine(X_OFFSET + 127, SCREEN_HEIGHT - 1, X_OFFSET + 127, SCREEN_HEIGHT - 12, WHITE);

  // draw scalar marks
  for (uint8_t i = 0; i < CACHE_MAX; ++i) {
    uint8_t scalarHeight = (SCREEN_HEIGHT - 10) * i / CACHE_MAX;
    display.drawLine(X_OFFSET, scalarHeight, SCREEN_WIDTH - X_OFFSET, scalarHeight, WHITE);
  }

  // draw channel range labels
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(SCREEN_WIDTH - X_OFFSET - 21, SCREEN_HEIGHT - 7);
  display.print(125);
  display.setCursor(X_OFFSET + 2, SCREEN_HEIGHT - 7);
  display.print(0);

  // refresh display
  REFRESH;
}