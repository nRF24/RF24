/*
 Copyright (C) 2022 Brendan Doherty <2bndy5@gmail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */
#include <cstdio>   // sprintf()
#include <string>   // string, getline()
#include <ctime>    // time_t, time(), difftime()
#include <iostream> // cout, endl, flush, cin
#include <queue>
#include <ncurses.h>
#include <RF24/RF24.h>

using namespace std;

/****************** Linux ***********************/
// Radio CE Pin, CSN Pin, SPI Speed
// CE Pin uses GPIO number with BCM and SPIDEV drivers, other platforms use their own pin numbering
// CS Pin addresses the SPI bus number at /dev/spidev<a>.<b>
// ie: RF24 radio(<ce_pin>, <a>*10+<b>); spidev1.0 is 10, spidev1.1 is 11 etc..

// Generic:
RF24 radio(22, 0);
/****************** Linux (BBB,x86,etc) ***********************/
// See http://nRF24.github.io/RF24/pages.html for more information on usage
// See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV

// Channel info
const uint8_t MAX_CHANNELS = 126;        // 0-125 are supported
unsigned int values[MAX_CHANNELS] = {0}; // the array to store summary of signal counts per channel
const int CACHE_MAX = 5;                 // maximum depth of history for calculating peaks per channel
queue<bool> history[MAX_CHANNELS];       // a cache of history for each channel

// we'll need a container to act as a buffer during history init and counting historic signals
queue<bool> temp = queue<bool>({0, 0, 0, 0, 0});

// To detect noise, we'll use the worst addresses possible (a reverse engineering tactic).
// These addresses are designed to confuse the radio into thinking
// that the RF signal's preamble is part of the packet/payload.
const uint8_t noiseAddress[][2] = {{0x55, 0x55}, {0xAA, 0xAA}};

unsigned int passesCount = 0; // count of passes for each scan of the entire spectrum

WINDOW* win; // curses base window object

// function prototypes
uint8_t initRadio();
void initCurses();
void initContainers();
void deinitCurses();
bool scanChannel(uint8_t);
int countHistory(uint8_t index);

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
            int bar_color = i < (filled + offset_x) ? 5 : color;
            attron(COLOR_PAIR(bar_color));
            addch(ACS_HLINE);
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
            if (!duration) input.clear();
        }
    }

    // create out interface
    initCurses();
    initContainers();
    mvaddstr(0, 0, "Channels are labeled in MHz.");
    mvaddstr(1, 0, "Signal counts are clamped to a single hexadecimal digit.");

    uint8_t i = 0;
    time_t start = time(nullptr);
    while (static_cast<int>(difftime(time(nullptr), start)) < duration) {
        mvprintw(2,
                 0,
                 "Scanning for %3d seconds at %d %cbps",
                 static_cast<int>(difftime(start + duration, time(nullptr))),
                 static_cast<int>(d_rate),
                 bpsUnit);

        bool foundSignal = scanChannel(i);
        history[i].pop();
        history[i].push(foundSignal);

        // output the summary/snapshot for this channel
        if (values[i]) {
            int cachedCount = countHistory(i);

            // Print changes to screen
            table[i]->update(cachedCount, rf24_min(values[i], 0xF));
        }

        refresh();
        if (i + 1 == MAX_CHANNELS) {
            i = 0;
            ++passesCount;
        }
        else {
            ++i;
        }
    }

    deinitCurses();
    return 0;
}

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
    radio.openReadingPipe(0, noiseAddress[0]);
    radio.openReadingPipe(1, noiseAddress[1]);

    // Get into standby mode
    radio.startListening();
    radio.stopListening();
    radio.flush_rx();
    // radio.printPrettyDetails();

    return returnVal;
}

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
    if (foundSignal || radio.testRPD()) {
        ++values[channel];
        radio.flush_rx(); // discard packets of noise
        return true;
    }
    return false;
}

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

void deinitCurses()
{
    nocbreak();
    echo();
    endwin();

    // print out the total signal counts (if any)
    uint8_t active_channels = 0; // the sum of channels with detected noise
    for (uint8_t i = 0; i < MAX_CHANNELS; ++i) {
        if (values[i]) {
            active_channels++;
            cout << "  "
                 << static_cast<unsigned int>(i)
                 << ": "
                 << static_cast<unsigned int>(values[i])
                 << endl;
        }
    }
    cout << static_cast<unsigned int>(active_channels)
         << " channels deteted signals after "
         << passesCount
         << " passes."
         << endl;
}

void initContainers()
{
    // fill our history with blanks
    for (uint8_t i = 0; i < MAX_CHANNELS; ++i) {
        history[i] = queue<bool>(temp);
    }

    // init our progress bars
    int bar_w = COLS / 6; // total progress bar width (including all contents)
    for (uint8_t i = 0; i < 21; ++i) {    // 21 rows
        for (uint8_t j = 0; j < 6; ++j) { // 6 columns

            int color = j % 2 ? 7 : 3; // 3 is yellow, 7 is white
            uint8_t channel = j * 21 + i;
            table[channel] = new ProgressBar(bar_w * j,                  // x
                                             i + 3,                      // y
                                             bar_w,                      // width
                                             to_string(2400 + channel), // label
                                             color);                     // color
        }
    }
}

int countHistory(uint8_t index)
{
    int sum = 0;
    // clear the temp buffer
    while (!temp.empty()) temp.pop();

    // move values of history into temp buffer, and count the historic signals
    while (!history[index].empty()) {
        temp.push(history[index].front());
        sum += static_cast<int>(history[index].front());
        history[index].pop();
    }

    // move values from buffer back into history
    while (!temp.empty()) {
        history[index].push(temp.front());
        temp.pop();
    }

    return sum;
}

// vim:ai:cin:sts=2 sw=2 ft=cpp
