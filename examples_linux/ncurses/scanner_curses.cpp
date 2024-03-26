/*
 Copyright (C) 2022 Brendan Doherty <2bndy5@gmail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Channel scanner
 *
 * Example to detect interference on the various channels available.
 * This is a good diagnostic tool to check whether you're picking a
 * good channel for your application.
 *
 * See documentation at https://nRF24.github.io/RF24
 */
#include <cstdio>   // sprintf()
#include <string>   // string, getline()
#include <ctime>    // time_t, time(), difftime()
#include <iostream> // cout, endl, flush, cin
#include <iomanip>  // setprecision()
#include <ncurses.h>
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
const uint8_t MAX_CHANNELS = 126; // 0-125 are supported
const uint8_t CACHE_MAX = 5;      // maximum depth of history for calculating peaks per channel

struct ChannelHistory
{
    unsigned int total = 0; // the summary of signal counts for the channel

    /**
     * Push new scan result for a channel into the history.
     * This function also increments the total signal count accordingly.
     * @returns The count of cached signals found (including pushed result)
     */
    uint8_t push(bool value)
    {
        uint8_t sum = value;
        total += value;
        for (uint8_t i = 0; i < CACHE_MAX - 1; ++i) {
            history[i] = history[i + 1];
            sum += history[i];
        }
        history[CACHE_MAX - 1] = value;
        return sum;
    }

private:
    bool history[CACHE_MAX]; // a cache of history for the channel
};
ChannelHistory stored[MAX_CHANNELS];

// To detect noise, we'll use the worst addresses possible (a reverse engineering tactic).
// These addresses are designed to confuse the radio into thinking
// that the RF signal's preamble is part of the packet/payload.
const uint8_t noiseAddress[][6] = {{0x55, 0x55}, {0xAA, 0xAA}, {0x0A, 0xAA}, {0xA0, 0xAA}, {0x00, 0xAA}, {0xAB, 0xAA}};

unsigned int passesCount = 0; // count of passes for each scan of the entire spectrum

WINDOW* win; // curses base window object

// function prototypes

uint8_t initRadio();
void initCurses();
void deinitCurses();
void initBars();
bool scanChannel(uint8_t);
uint8_t historyPush(uint8_t index, bool value);

class ProgressBar
{

private:
    const int x, y, w, color;

public:
    ProgressBar(int cols, int rows, int width, string label, int color_index)
        : x(cols), y(rows), w(width), color(color_index)
    {
        attron(COLOR_PAIR(color));
        mvaddstr(y, x, label.c_str());
        addch(' ');
        for (uint8_t i = 0; i < w - 8; ++i)
            addch(ACS_HLINE);
        addstr(" - ");
        attroff(COLOR_PAIR(color));
    };

    void update(int completed, int sig_count)
    {
        int filled = (w - 8) * completed / CACHE_MAX;
        int offset_x = 5;
        move(y, x + offset_x);
        for (int i = offset_x; i < w - 3; ++i) {
            bool bar_filled = i < (filled + offset_x);
            int bar_color = bar_filled ? 5 : color;
            attron(COLOR_PAIR(bar_color));
            addch(bar_filled ? '=' : ACS_HLINE);
            attroff(COLOR_PAIR(bar_color));
        }
        attron(COLOR_PAIR(color));
        printw(" %x ", sig_count);
        attroff(COLOR_PAIR(color));
    };
};

// our table of progress bars used to represent channels in the curses window
ProgressBar* table[MAX_CHANNELS];

int main(int argc, char** argv)
{
    // print example's name
    cout << argv[0] << endl;

    // Setup the radio
    if (!radio.begin()) {
        cout << "Radio hardware not responding!" << endl;
        return 1;
    }
    uint8_t d_rate = initRadio();
    char bpsUnit = d_rate > 2 ? 'k' : 'M';

    string input = "";
    int duration = 0;
    while (!input.length()) {
        cout << "Enter the duration (in seconds) of the scan: ";
        getline(cin, input);
        if (input.length()) {
            duration = stoi(input);
            if (!duration)
                input.clear();
        }
    }

    // create out interface
    initCurses();
    initBars();
    mvaddstr(0, 0, "Channels are labeled in MHz.");
    mvaddstr(1, 0, "Signal counts are clamped to a single hexadecimal digit.");

    uint8_t channel = 0;
    time_t start = time(nullptr);
    while (static_cast<int>(difftime(time(nullptr), start)) < duration) {
        mvprintw(2,
                 0,
                 "Scanning for %3d seconds at %d %cbps",
                 static_cast<int>(difftime(start + duration, time(nullptr))),
                 static_cast<int>(d_rate),
                 bpsUnit);

        bool foundSignal = scanChannel(channel);
        uint8_t cachedCount = stored[channel].push(foundSignal);

        // output the summary/snapshot for this channel
        if (stored[channel].total) {
            // make changes to the screen
            table[channel]->update(static_cast<int>(cachedCount), rf24_min(stored[channel].total, 0xF));
        }

        refresh();
        if (channel + 1 == MAX_CHANNELS) {
            channel = 0;
            ++passesCount;
        }
        else {
            ++channel;
        }
    }

    deinitCurses();
    return 0;
}

/** init radio according to user-specified data rate */
uint8_t initRadio()
{
    uint8_t returnVal = 0;
    // set the data rate
    cout << "Select your Data Rate. "
         << "Enter '1' for 1 Mbps, '2' for 2 Mbps, '3' for 250 kbps. "
         << "Defaults to 1Mbps: ";
    string dataRate = "";
    getline(cin, dataRate);
    if (dataRate.length() >= 1 && static_cast<char>(dataRate[0]) == '2') {
        cout << "Using 2 Mbps." << endl;
        radio.setDataRate(RF24_2MBPS);
        returnVal = 2;
    }
    else if (dataRate.length() >= 1 && static_cast<char>(dataRate[0]) == '3') {
        cout << "Using 250 kbps." << endl;
        radio.setDataRate(RF24_250KBPS);
        returnVal = 250;
    }
    else {
        cout << "Using 1 Mbps." << endl;
        radio.setDataRate(RF24_1MBPS);
        returnVal = 1;
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

    return returnVal;
}

/** scan the specified channel and increment signal count accordingly */
bool scanChannel(uint8_t channel)
{
    // Select this channel
    radio.setChannel(channel);

    // Listen for a little
    radio.startListening();
    delayMicroseconds(130);
    // for some reason, this flag is more accurate on Linux when still in RX mode.
    bool foundSignal = radio.testRPD();
    radio.stopListening();

    // Did we get a signal?
    if (foundSignal || radio.testRPD() || radio.available()) {
        radio.flush_rx(); // discard packets of noise
        return true;
    }
    return false;
}

/** init the curses interface */
void initCurses()
{
    win = initscr(); // Start curses mode
    noecho();
    cbreak();
    start_color();
    use_default_colors();
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_WHITE, -1);
}

/** de-init the curses interface & show total signal counts */
void deinitCurses()
{
    nocbreak();
    echo();
    endwin();

    // print out the total signal counts (if any)
    uint8_t active_channels = 0; // the sum of channels with detected noise
    uint8_t digitW = 0;
    unsigned int tmp = passesCount;
    while (tmp) {
        digitW += 1;
        tmp /= 10;
    }

    for (uint8_t channel = 0; channel < MAX_CHANNELS; ++channel) {
        if (stored[channel].total) {
            active_channels++;
            float noiseRatio = static_cast<float>(stored[channel].total) / passesCount * 100;
            cout << "  "
                 << setfill(' ')
                 << setw(3)
                 << static_cast<unsigned int>(channel)
                 << ": "
                 << setw(digitW)
                 << static_cast<unsigned int>(stored[channel].total)
                 << " / "
                 << passesCount
                 << " ("
                 << setprecision(3)
                 << noiseRatio
                 << " %)"
                 << endl;
        }
    }
    cout << static_cast<unsigned int>(active_channels)
         << " channels detected signals after "
         << passesCount
         << " passes."
         << endl;
}

/** init arrays for the history and progress bars */
void initBars()
{
    // init our progress bars
    int bar_w = COLS / 6; // total progress bar width (including all contents)

    for (uint8_t i = 0; i < 21; ++i) {    // 21 rows
        for (uint8_t j = 0; j < 6; ++j) { // 6 columns

            uint8_t channel = j * 21 + i;
            table[channel] = new ProgressBar(
                bar_w * j,                 // x
                i + 3,                     // y
                bar_w,                     // width
                to_string(2400 + channel), // label
                j % 2 ? 7 : 3              // 3 is yellow, 7 is white
            );
        }
    }
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
