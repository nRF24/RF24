"""
Simple example of detecting (and verifying) the IRQ (interrupt) pin on the
nRF24L01

See documentation at https://nRF24.github.io/RF24
"""

import time
from RF24 import RF24, RF24_PA_LOW, RF24_DRIVER

try:
    import gpiod
    from gpiod.line import Edge
except ImportError as exc:
    raise ImportError(
        "This script requires gpiod installed for observing the IRQ pin. Please run\n"
        "\n    pip install gpiod\n\nMore details at https://pypi.org/project/gpiod/"
    ) from exc

try:  # try RPi5 gpio chip first
    chip_path = "/dev/gpiochip4"
    chip = gpiod.Chip(chip_path)
except FileNotFoundError:  # fall back to gpio chip for RPi4 or older
    chip_path = "/dev/gpiochip0"
    chip = gpiod.Chip(chip_path)
finally:
    print(__file__)  # print example name
    # print gpio chip info
    info = chip.get_info()
    print(f"Using {info.name} [{info.label}] ({info.num_lines} lines)")


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

# select your digital input pin that's connected to the IRQ pin on the nRF24L01
IRQ_PIN = 24

# For this example, we will use different addresses
# An address need to be a buffer protocol object (bytearray)
address = [b"1Node", b"2Node"]
# It is very helpful to think of an address as a path instead of as
# an identifying device destination

# to use different addresses on a pair of radios, we need a variable to
# uniquely identify which address this radio will use to transmit
# 0 uses address[0] to transmit, 1 uses address[1] to transmit
radio_number = bool(
    int(input("Which radio is this? Enter '0' or '1'. Defaults to '0' ") or 0)
)

# initialize the nRF24L01 on the spi bus
if not radio.begin():
    raise OSError("nRF24L01 hardware isn't responding")

# this example uses the ACK payload to trigger the IRQ pin active for
# the "on data received" event
radio.enableDynamicPayloads()  # ACK payloads are dynamically sized
radio.enableAckPayload()  # enable ACK payloads

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# set the TX address of the RX node into the TX pipe
radio.openWritingPipe(address[radio_number])  # always uses pipe 0

# set the RX address of the TX node into a RX pipe
radio.openReadingPipe(1, address[not radio_number])  # using pipe 1

# for debugging, we have 2 options that print a large block of details
# (smaller) function that prints raw register values
# radio.printDetails()
# (larger) function that prints human readable data
# radio.printPrettyDetails()

# For this example, we'll be using a payload containing
# a string that changes on every transmission. (successful or not)
# Make a couple tuples of payloads & an iterator to traverse them
pl_iterator = [0]  # use a 1-item list instead of python's global keyword
tx_payloads = (b"Ping ", b"Pong ", b"Radio", b"1FAIL")
ack_payloads = (b"Yak ", b"Back", b" ACK")


def interrupt_handler():
    """This function is called when IRQ pin is detected active LOW"""
    print("\tIRQ pin went active LOW.")
    tx_ds, tx_df, rx_dr = radio.whatHappened()  # update IRQ status flags
    print(f"\ttx_ds: {tx_ds}, tx_df: {tx_df}, rx_dr: {rx_dr}")
    if pl_iterator[0] == 0:
        print("    'data ready' event test", ("passed" if rx_dr else "failed"))
    elif pl_iterator[0] == 1:
        print("    'data sent' event test", ("passed" if tx_ds else "failed"))
    elif pl_iterator[0] == 2:
        print("    'data fail' event test", ("passed" if tx_df else "failed"))


# setup IRQ GPIO pin
irq_line = gpiod.request_lines(
    path=chip_path,
    consumer="RF24_interrupt_py-example",  # optional
    config={IRQ_PIN: gpiod.LineSettings(edge_detection=Edge.FALLING)},
)


def _wait_for_irq(timeout: float = 5):
    """Wait till IRQ_PIN goes active (LOW).
    IRQ pin is LOW when activated. Otherwise it is always HIGH
    """
    # wait up to ``timeout`` seconds for event to be detected.
    if not irq_line.wait_edge_events(timeout):
        print(f"\tInterrupt event not detected for {timeout} seconds!")
        return False
    # read event from kernel buffer
    for event in irq_line.read_edge_events():
        if event.line_offset == IRQ_PIN and event.event_type is event.Type.FALLING_EDGE:
            return True
    return False


def master():
    """Transmits 4 times and reports results

    1. successfully receive ACK payload first
    2. successfully transmit on second
    3. send a third payload to fill RX node's RX FIFO
       (supposedly making RX node unresponsive)
    4. intentionally fail transmit on the fourth
    """
    radio.stopListening()  # put radio in TX mode

    # on data ready test
    print("\nConfiguring IRQ pin to only ignore 'on data sent' event")
    radio.maskIRQ(True, False, False)  # args = tx_ds, tx_df, rx_dr
    print("    Pinging slave node for an ACK payload...")
    pl_iterator[0] = 0
    radio.startFastWrite(tx_payloads[0], False)  # False means expecting an ACK
    if _wait_for_irq():
        interrupt_handler()

    # on "data sent" test
    print("\nConfiguring IRQ pin to only ignore 'on data ready' event")
    radio.maskIRQ(False, False, True)  # args = tx_ds, tx_df, rx_dr
    print("    Pinging slave node again...")
    pl_iterator[0] = 1
    radio.startFastWrite(tx_payloads[1], False)  # False means expecting an ACK
    if _wait_for_irq():
        interrupt_handler()

    # trigger slave node to exit by filling the slave node's RX FIFO
    print("\nSending one extra payload to fill RX FIFO on slave node.")
    print("Disabling IRQ pin for all events.")
    radio.maskIRQ(True, True, True)  # args = tx_ds, tx_df, rx_dr
    if radio.write(tx_payloads[2]):
        print("Slave node should not be listening anymore.")
    else:
        print("Slave node was unresponsive.")

    # on "data fail" test
    print("\nConfiguring IRQ pin to go active for all events.")
    radio.maskIRQ(False, False, False)  # args = tx_ds, tx_df, rx_dr
    print("    Sending a ping to inactive slave node...")
    radio.flush_tx()  # just in case any previous tests failed
    pl_iterator[0] = 2
    radio.startFastWrite(tx_payloads[3], False)  # False means expecting an ACK
    if _wait_for_irq():
        interrupt_handler()
    radio.flush_tx()  # flush artifact payload in TX FIFO from last test
    # all 3 ACK payloads received were 4 bytes each, and RX FIFO is full
    # so, fetching 12 bytes from the RX FIFO also flushes RX FIFO
    print("\nComplete RX FIFO:", radio.read(12))


def slave(timeout=6):  # will listen for 6 seconds before timing out
    """Only listen for 3 payload from the master node"""
    # the "data ready" event will trigger in RX mode
    # the "data sent" or "data fail" events will trigger when we
    # receive with ACK payloads enabled (& loaded in TX FIFO)
    print("\nDisabling IRQ pin for all events.")
    radio.maskIRQ(True, True, True)  # args = tx_ds, tx_df, rx_dr
    # setup radio to receive pings, fill TX FIFO with ACK payloads
    radio.writeAckPayload(1, ack_payloads[0])
    radio.writeAckPayload(1, ack_payloads[1])
    radio.writeAckPayload(1, ack_payloads[2])
    radio.startListening()  # start listening & clear irq_dr flag
    start_timer = time.monotonic()  # start timer now
    while not radio.rxFifoFull() and time.monotonic() - start_timer < timeout:
        # if RX FIFO is not full and timeout is not reached, then keep waiting
        pass
    time.sleep(0.5)  # wait for last ACK payload to transmit
    radio.stopListening()  # put radio in TX mode & discard any ACK payloads
    if radio.available():  # if RX FIFO is not empty (timeout did not occur)
        # all 3 payloads received were 5 bytes each, and RX FIFO is full
        # so, fetching 15 bytes from the RX FIFO also flushes RX FIFO
        print("Complete RX FIFO:", radio.read(15))


def set_role():
    """Set the role using stdin stream. Timeout arg for slave() can be
    specified using a space delimiter (e.g. 'R 10' calls `slave(10)`)

    :return:
        - True when role is complete & app should continue running.
        - False when app should exit
    """
    user_input = (
        input(
            f"Make sure the IRQ pin is connected to the GPIO{IRQ_PIN}\n"
            "*** Enter 'R' for receiver role.\n"
            "*** Enter 'T' for transmitter role.\n"
            "*** Enter 'Q' to quit example.\n"
        )
        or "?"
    )
    user_input = user_input.split()
    if user_input[0].upper().startswith("R"):
        slave(*[int(x) for x in user_input[1:2]])
        return True
    if user_input[0].upper().startswith("T"):
        master()
        return True
    if user_input[0].upper().startswith("Q"):
        radio.powerDown()
        return False
    print(user_input[0], "is an unrecognized input. Please try again.")
    return set_role()


if __name__ == "__main__":
    try:
        while set_role():
            pass  # continue example until 'Q' is entered
    except KeyboardInterrupt:
        print(" Keyboard Interrupt detected. Exiting...")
        radio.powerDown()
else:
    print(
        f"Make sure the IRQ pin is connected to the GPIO{IRQ_PIN}",
        "Run slave() on receiver",
        "Run master() on transmitter",
        sep="\n",
    )
