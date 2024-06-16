"""
A simple example of sending data from as many as 6 nRF24L01 transceivers to
1 receiving transceiver. This technique is trademarked by
Nordic Semiconductors as "MultiCeiver".

This example was written to be used on up to 6 devices acting as TX nodes &
only 1 device acting as the RX node (that's a maximum of 7 devices).

See documentation at https://nRF24.github.io/RF24
"""

import time
import struct
from RF24 import RF24, RF24_PA_LOW, RF24_DRIVER

print(__file__)

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

# initialize the nRF24L01 on the spi bus
if not radio.begin():
    raise RuntimeError("radio hardware is not responding")

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# To save time during transmission, we'll set the payload size to be only what
# we need.
# 2 int occupy 8 bytes in memory using struct.pack()
# "ii" means 2 unsigned integers
radio.payloadSize = struct.calcsize("ii")

# for debugging, we have 2 options that print a large block of details
# radio.printDetails();  # (smaller) function that prints raw register values
# radio.printPrettyDetails();  # (larger) function that prints human readable data

# setup the addresses for all transmitting radio nodes
addresses = [
    b"\x78" * 5,
    b"\xf1\xb6\xb5\xb4\xb3",
    b"\xcd\xb6\xb5\xb4\xb3",
    b"\xa3\xb6\xb5\xb4\xb3",
    b"\x0f\xb6\xb5\xb4\xb3",
    b"\x05\xb6\xb5\xb4\xb3",
]
# It is very helpful to think of an address as a path instead of as
# an identifying device destination


def master(node_number):
    """start transmitting to the base station.

    :param int node_number: the node's identifying index (from the
        the `addresses` list). This is a required parameter
    """
    # According to the datasheet, the auto-retry features's delay value should
    # be "skewed" to allow the RX node to receive 1 transmission at a time.
    # So, use varying delay between retry attempts and 15 (at most) retry attempts
    radio.setRetries(
        ((node_number * 3) % 12) + 3, 15
    )  # maximum value is 15 for both args

    radio.stopListening()  # put radio in TX mode
    # set the TX address to the address of the base station.
    radio.openWritingPipe(addresses[node_number])
    counter = 0
    failures = 0
    while failures < 6:
        counter += 1
        # payloads will include the node_number and a payload ID character
        payload = struct.pack("<ii", node_number, counter)
        start_timer = time.monotonic_ns()
        report = radio.write(payload)
        end_timer = time.monotonic_ns()
        # show something to see it isn't frozen
        print(
            f"Transmission of payloadID {counter} as node {node_number}",
            end=" ",
        )
        if report:
            print(
                f"successful! Time to transmit = {(end_timer - start_timer) / 1000} us"
            )
        else:
            failures += 1
            print("failed or timed out")
        time.sleep(1)  # slow down the test for readability
    print(failures, "failures detected. Leaving TX role.")


def slave(timeout: int = 10):
    """Use the radio as a base station for listening to all nodes

    :param int timeout: The number of seconds to wait (with no transmission)
        until exiting function.
    """
    # write the addresses to all pipes.
    for pipe_n, addr in enumerate(addresses):
        radio.openReadingPipe(pipe_n, addr)
    radio.startListening()  # put radio in RX mode
    start_timer = time.monotonic()  # start timer
    while time.monotonic() - start_timer < timeout:
        has_payload, pipe_number = radio.available_pipe()
        if has_payload:
            # unpack payload
            node_id, payload_id = struct.unpack("<ii", radio.read(radio.payloadSize))
            # show the pipe number that received the payload
            print(
                f"Received {radio.payloadSize} bytes",
                f"on pipe {pipe_number} from node {node_id}.",
                f"PayloadID: {payload_id}",
            )
            start_timer = time.monotonic()  # reset timer with every payload

    print("Nothing received in", timeout, "seconds. Leaving RX role")
    radio.stopListening()


def set_role() -> bool:
    """Set the role using stdin stream. Timeout arg for slave() can be
    specified using a space delimiter (e.g. 'R 10' calls `slave(10)`)

    :return:
        - True when role is complete & app should continue running.
        - False when app should exit
    """
    user_input = (
        input(
            "*** Enter 'R' for receiver role.\n"
            "*** Enter a number in range [0, 5] to use a specific node ID for "
            "transmitter role.\n"
            "*** Enter 'Q' to quit example.\n"
        )
        or "?"
    )
    user_input = user_input.split()
    if user_input[0].upper().startswith("R"):
        if len(user_input) > 1:
            slave(int(user_input[1]))
        else:
            slave()
        return True
    if user_input[0].isdigit() and 0 <= int(user_input[0]) <= 5:
        master(int(user_input[0]))
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
        print(" Keyboard Interrupt detected. Powering down radio.")
        radio.powerDown()
else:
    print("    Run slave() on the receiver")
    print("    Run master(node_number) on a transmitter")
    print("        master()'s parameter, `node_number`, must be in range [0, 5]")
