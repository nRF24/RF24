"""A scanner example written in python using the std lib's ncurses wrapper.

This is a good diagnostic tool to check whether you're picking a
good channel for your application.

See documentation at https://nRF24.github.io/RF24
"""

import curses
import time
from typing import List, Tuple, Any

from RF24 import RF24, RF24_1MBPS, RF24_2MBPS, RF24_250KBPS, RF24_DRIVER

########### USER CONFIGURATION ###########
# CE Pin uses GPIO number with RPi and SPIDEV drivers, other drivers use
# their own pin numbering
# CS Pin corresponds the SPI bus number at /dev/spidev<a>.<b>
# ie: radio = RF24(<ce_pin>, <a>*10+<b>)
# where CS pin for /dev/spidev1.0 is 10, /dev/spidev1.1 is 11 etc...
CSN_PIN = 0  # GPIO8 aka CE0 on SPI bus 0: /dev/spidev0.0
if RF24_DRIVER == "MRAA":
    CE_PIN = 15  # for GPIO22
elif RF24_DRIVER == "wiringPi":
    CE_PIN = 3  # for GPIO22
else:
    CE_PIN = 22
radio = RF24(CE_PIN, CSN_PIN)


OFFERED_DATA_RATES = ["1 Mbps", "2 Mbps", "250 kbps"]
AVAILABLE_RATES = [RF24_1MBPS, RF24_2MBPS, RF24_250KBPS]
TOTAL_CHANNELS = 126
CACHE_MAX = 5  # the depth of history to calculate peaks

# To detect noise, we'll use the worst addresses possible (a reverse engineering
# tactic). These addresses are designed to confuse the radio into thinking that the
# RF signal's preamble is part of the packet/payload.
noise_address = [
    b"\x55\x55",
    b"\xaa\xaa",
    b"\x0a\xaa",
    b"\xa0\xaa",
    b"\x00\xaa",
    b"\xab\xaa",
]


class ChannelHistory:
    def __init__(self) -> None:
        #: FIFO for tracking peak decays
        self._history: List[bool] = [False] * CACHE_MAX
        #: for the total signal counts
        self.total: int = 0

    def push(self, value: bool) -> int:
        """Push a scan result's value into history while returning the sum of cached
        signals found. This function also increments the total signal count accordingly.
        """
        self._history = self._history[1:] + [value]
        self.total += value
        return self._history.count(True)


#: An array of histories for each channel
stored = [ChannelHistory() for _ in range(TOTAL_CHANNELS)]


class ProgressBar:  # pylint: disable=too-few-public-methods
    """This represents a progress bar using a curses window object."""

    def __init__(  # pylint: disable=too-many-arguments,invalid-name
        self,
        x: int,
        y: int,
        cols: int,
        std_scr: Any,  # type: curses.window,
        label: str,
        color: int,
    ):
        self.x, self.y, self.width, self.win, self.color = (x, y, cols, std_scr, color)
        self.win.move(self.y, self.x)
        self.win.attron(curses.color_pair(self.color))
        self.win.addstr(label)  # always labeled in MHz (4 digits)
        for _ in range(self.width - 8):  # draw the empty bar
            self.win.addch(curses.ACS_HLINE)
        self.win.addstr(" - ")  # draw the initial signal count
        self.win.attroff(curses.color_pair(self.color))

    def update(self, completed: int, signal_count: int):
        """Update the progress bar."""
        count = " - "
        if signal_count:
            count = " %X " % min(0xF, signal_count)
        filled = (self.width - 8) * completed / CACHE_MAX
        offset_x = 5
        self.win.move(self.y, self.x + offset_x)
        for i in range(offset_x, self.width - 3):
            bar_filled = i < (filled + offset_x)
            bar_color = 5 if bar_filled else self.color
            self.win.attron(curses.color_pair(bar_color))
            self.win.addch("=" if bar_filled else curses.ACS_HLINE)
            self.win.attroff(curses.color_pair(bar_color))
        self.win.attron(curses.color_pair(self.color))
        self.win.addstr(count)
        self.win.attroff(curses.color_pair(self.color))


def init_display(window) -> List[ProgressBar]:
    """Creates a table of progress bars (1 for each channel)."""
    progress_bars: List[ProgressBar] = [None] * TOTAL_CHANNELS
    bar_w = int(curses.COLS / 6)
    for i in range(21):  # 21 rows
        for j in range(i, i + (21 * 6), 21):  # 6 columns
            color = 7 if int(j / 21) % 2 else 3
            progress_bars[j] = ProgressBar(
                x=bar_w * int(j / 21),
                y=i + 3,
                cols=bar_w,
                std_scr=window,
                label=f"{2400 + (j)} ",
                color=color,
            )
    return progress_bars


def init_radio():
    """init the radio"""
    if not radio.begin():
        raise RuntimeError("Radio hardware not responding!")
    radio.setAutoAck(False)
    radio.disableCRC()
    radio.setAddressWidth(2)
    for pipe, address in enumerate(noise_address):
        radio.openReadingPipe(pipe, address)
    radio.startListening()
    radio.stopListening()
    radio.flush_rx()


def init_curses():
    """init the curses interface"""
    std_scr = curses.initscr()
    curses.noecho()
    curses.cbreak()
    curses.start_color()
    curses.use_default_colors()
    curses.init_pair(3, curses.COLOR_YELLOW, -1)
    curses.init_pair(5, curses.COLOR_MAGENTA, -1)
    curses.init_pair(7, curses.COLOR_WHITE, -1)
    return std_scr


def deinit_curses(spectrum_passes: int):
    """de-init the curses interface"""
    curses.nocbreak()
    curses.echo()
    curses.endwin()
    noisy_channels: int = 0
    digit_w = len(str(spectrum_passes))
    for channel, data in enumerate(stored):
        if data.total:
            count_padding = " " * (digit_w - len(str(data.total)))
            percentage = round(data.total / spectrum_passes * 100, 3)
            print(
                f"  {channel:>3}: {count_padding}{data.total} / {spectrum_passes} ({percentage} %)"
            )
            noisy_channels += 1
    print(
        f"{noisy_channels} channels detected signals out of {spectrum_passes}",
        "passes on the entire spectrum.",
    )


def get_user_input() -> Tuple[int, int]:
    """Get input parameters for the scan from the user."""
    for i, d_rate in enumerate(OFFERED_DATA_RATES):
        print(f"{i + 1}. {d_rate}")
    d_rate = input("Select your data rate [1, 2, 3] (defaults to 1 Mbps) ")
    duration = input("How long (in seconds) to perform scan? ")
    while not duration.isdigit():
        print("Please enter a positive number.")
        duration = input("How long (in seconds) to perform scan? ")
    return (
        max(1, min(3, 1 if not d_rate.isdigit() else int(d_rate))) - 1,
        abs(int(duration)),
    )


def scan_channel(channel: int) -> bool:
    """Scan a specified channel and report if a signal was detected."""
    radio.channel = channel
    radio.startListening()
    time.sleep(0.00013)
    found_signal = radio.testRPD()
    radio.stopListening()
    if found_signal or radio.testRPD() or radio.available():
        radio.flush_rx()
        return True
    return False


def main():
    spectrum_passes = 0
    data_rate, duration = get_user_input()
    print(f"Scanning for {duration} seconds at {OFFERED_DATA_RATES[data_rate]}")
    init_radio()
    radio.setDataRate(AVAILABLE_RATES[data_rate])
    try:
        std_scr = init_curses()
        timer_prompt = "Scanning for {:>3} seconds at " + OFFERED_DATA_RATES[data_rate]
        std_scr.addstr(0, 0, "Channels are labeled in MHz.")
        std_scr.addstr(1, 0, "Signal counts are clamped to a single hexadecimal digit.")
        bars = init_display(std_scr)
        channel, val = (0, False)
        end = time.monotonic() + duration
        while time.monotonic() < end:
            std_scr.addstr(2, 0, timer_prompt.format(int(end - time.monotonic())))
            val = scan_channel(channel)
            cache_sum = stored[channel].push(val)
            if stored[channel].total:
                bars[channel].update(cache_sum, stored[channel].total)
                std_scr.refresh()
            if channel + 1 == TOTAL_CHANNELS:
                channel = 0
                spectrum_passes += 1
            else:
                channel += 1
    finally:
        radio.powerDown()
        deinit_curses(spectrum_passes)


if __name__ == "__main__":
    main()
else:
    print("Run 'main()' to run the program.")
