"""A scanner example that uses the python `rich` module to provide
a user-friendly output."""
import time
from typing import List

try:
    from rich.table import Table
    from rich.console import Console
    from rich.progress import BarColumn, Progress, TextColumn
    from rich.live import Live
    from rich.prompt import Prompt, IntPrompt
    from rich.style import Style
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
DATA_RATE = (
    int(Prompt.ask("Choose the data rate", choices=["1", "2", "3"], default="1")) - 1
)
radio.setDataRate(available_rates[DATA_RATE])

DURATION = IntPrompt.ask("Enter the scan duration (in whole seconds)")
SELECTED_RATE = offered_rates[DATA_RATE]

CACHE_MAX = 5  # the depth of history to calculate peaks
history = [[False] * CACHE_MAX] * 126  # for tracking peak decay on each channel
signals = [False] * 126  # for tracking the signal count on each channel
totals = [0] * 126  # for the total signal count on each channel

# create table of progress bars (labeled by frequency channel in MHz)
table = Table.grid(padding=(0, 1))
progress_bars: List[Progress] = [None] * 126
for i in range(21):  # 21 rows
    row = []
    for j in range(i, i + (21 * 6), 21):  # 6 columns
        COLOR = "white" if int(j / 21) % 2 else "yellow"
        progress_bars[j] = Progress(
            TextColumn("{task.description}", style=Style(color=COLOR)),
            BarColumn(style=Style(color=COLOR)),
            TextColumn("{task.fields[signals]}", style=Style(color=COLOR)),
        )
        # add only 1 task for each progress bar
        progress_bars[j].add_task(f"{2400 + (j)}", total=CACHE_MAX, signals="-")
        row.append(progress_bars[j])
    table.add_row(*row)


def scan_channel(channel: int) -> bool:
    """Scan a specified channel and report if a signal was detected."""
    radio.channel = channel
    radio.startListening()
    time.sleep(0.00013)
    result = radio.testRPD()
    radio.stopListening()
    return result


def scan(duration: int = DURATION):
    """Perform scan."""
    timeout = time.monotonic() + duration
    console.print(
        f"Scanning all channels using {SELECTED_RATE} for",
        f"{duration} seconds. Channel labels are in MHz.",
    )
    with Live(table, refresh_per_second=1000):
        try:
            while time.monotonic() < timeout:
                for chl, p_bar in enumerate(progress_bars):
                    # save the latest in history (FIFO ordering)
                    history[chl] = history[chl][1:] + [signals[chl]]

                    # refresh the latest
                    signals[chl] = scan_channel(chl)

                    # update total signal count for the channel
                    totals[chl] += int(signals[chl])

                    p_bar.update(
                        p_bar.task_ids[0],
                        completed=history[chl].count(True),
                        signals="-" if not totals[chl] else totals[chl],
                    )
        except KeyboardInterrupt:
            console.print(" Keyboard interrupt detected. Powering down radio.")
            radio.powerDown()


if __name__ == "__main__":
    scan()
    radio.powerDown()
else:
    console.print("Enter `scan()` to run a scan.")
    console.print("Change data rate using `radio.setDataRate(RF24_**BPS)`")
