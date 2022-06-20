"""A scanner example that uses the python `rich` module to provide
a user-friendly output."""
import time
import math

try:
    from rich.table import Table
    from rich.console import Console
    from rich.progress import BarColumn, Progress, TextColumn
    from rich.live import Live
    from rich.prompt import Prompt, IntPrompt
except ImportError as exc:
    raise ImportError(
        "This example requires the python `rich` module installed."
        "\nInstall it using 'python3 -m pip install rich'"
    ) from exc
from RF24 import RF24, RF24_1MBPS, RF24_2MBPS, RF24_250KBPS

CSN_PIN = 0  # connected to GPIO8
CE_PIN = 22  # connected to GPIO22
radio = RF24(CE_PIN, CSN_PIN)

if not radio.begin():
    raise RuntimeError("Radio hardware not responding!")
radio.setAutoAck(False)

offered_rates = ["1 Mbps", "2 Mbps", "250 kbps"]
available_rates = [RF24_1MBPS, RF24_2MBPS, RF24_250KBPS]
console = Console()
for i, rate in enumerate(offered_rates):
    console.print(f"{i + 1}. {rate}")

# create table of progress bars (labeled by frequency channel in MHz)
table = Table.grid(padding=(0, 1))
totals = [0] * 126  # for the total signal count on each channel
signals = [0] * 126  # for tracking the signal count on each channel
CACHED_MAX = 5  # the depth of history to calculate averages with
history = [[0] * CACHED_MAX] * 126  # for tracking peak decay on each channel
progress_bars = [Progress()] * 126
for i in range(21):  # 21 rows
    row = []
    for j in range(i, i + (21 * 6), 21):  # 6 columns
        progress_bars[j] = Progress(
            TextColumn("{task.description}"), BarColumn(), TextColumn("{task.signals}")
        )
        progress_bars[j].add_task(f"{2400 + (j)}", signals=0)  # only 1 task for each
        row.append(progress_bars[j])
    table.add_row(*row)

DATA_RATE = (
    int(Prompt.ask("Choose the data rate", choices=["1", "2", "3"], default="1")) - 1
)
radio.setDataRate(available_rates[DATA_RATE])

DURATION = IntPrompt.ask("Enter the scan duration (in whole seconds)")
SELECTED_RATE = offered_rates[DATA_RATE]
console.print(
    f"Beginning scan using {SELECTED_RATE} for {DURATION} seconds.",
    "Channel labels are in MHz.",
)


def scan_channel(channel: int) -> int:
    """Scan a specified channel and report if a signal was detected."""
    radio.channel = channel
    radio.startListening()
    time.sleep(0.00013)
    result = radio.testRPD()
    radio.stopListening()
    return int(result)


def calc_peak(channel: int) -> int:
    """Get the average of the last 6 scans on a channel"""
    total = int(signals[channel])
    for val in history[channel]:
        total += val
    return math.ceil(total / (CACHED_MAX + 1))


# perform scan
TIMEOUT = time.monotonic() + DURATION
with Live(table, refresh_per_second=1000) as live:
    try:
        history_index: int = 0
        while time.monotonic() < TIMEOUT:
            for chl, bar in enumerate(progress_bars):
                # save the latest in history
                history[chl][history_index] = signals[chl]

                # refresh the latest
                signals[chl] = scan_channel(chl)

                # update total signal count for the channel
                totals[chl] += signals[chl]

                peak = calc_peak(chl)  # average latest with history
                bar.update(
                    bar.task_ids[0],
                    completed=signals[chl],
                    total=CACHED_MAX + 1,
                    signals=totals[chl],
                )
            # history is a list of cyclical arrays. Wrap iterator to 0 at CAHCED_MAX
            history_index = (
                0 if history_index == (CACHED_MAX - 1) else history_index + 1
            )
    except KeyboardInterrupt:
        console.print(" Keyboard interrupt detected. Powering down radio.")
        radio.powerDown()
