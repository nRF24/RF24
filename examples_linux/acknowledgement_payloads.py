"""
A simple example of sending data from 1 nRF24L01 transceiver to another
with Acknowledgement (ACK) payloads attached to ACK packets.

This example was written to be used on 2 devices acting as 'nodes'.

See documentation at https://nRF24.github.io/RF24
"""

import time
from RF24 import RF24, RF24_PA_LOW, RF24_DRIVER

print(__file__)  # print example name

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

# For this example, we will use different addresses
# An address need to be a buffer protocol object (bytearray)
address = [b"1Node", b"2Node"]
# It is very helpful to think of an address as a path instead of as
# an identifying device destination

radio_number = bool(
    int(input("Which radio is this? Enter '0' or '1'. Defaults to '0' ") or 0)
)

# ACK payloads are dynamically sized.
radio.enableDynamicPayloads()  # to use ACK payloads

# to enable the custom ACK payload feature
radio.enableAckPayload()

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# set the TX address of the RX node for use on the TX pipe (pipe 0)
radio.stopListening(address[radio_number])

# set the RX address of the TX node into a RX pipe
radio.openReadingPipe(1, address[not radio_number])  # using pipe 1

# for debugging, we have 2 options that print a large block of details
# (smaller) function that prints raw register values
# radio.printDetails()
# (larger) function that prints human readable data
# radio.printPrettyDetails()

# using the python keyword global is bad practice. Instead we'll use a
# 1 item list to store our integer number for the payloads' counter
counter = [0]


def master():
    """Transmits a message and an incrementing integer every second."""
    radio.stopListening()  # put radio in TX mode
    failures = 0
    while failures < 6:
        # construct a payload to send
        buffer = b"Hello \x00" + bytes(counter)

        # send the payload and prompt
        start_timer = time.monotonic_ns()  # start timer
        result = radio.write(buffer)  # save the report
        end_timer = time.monotonic_ns()  # stop timer
        if result:
            # print timer results upon transmission success
            decoded = buffer[:6].decode("utf-8")
            print(
                "Transmission successful! Time to transmit:",
                f"{int((end_timer - start_timer) / 1000)} us.",
                f"Sent: {decoded}{counter[0]}",
                end=" ",
            )
            has_payload, pipe_number = radio.available_pipe()
            if has_payload:
                # print the received ACK that was automatically sent
                length = radio.getDynamicPayloadSize()
                response = radio.read(length)
                decoded = bytes(response[:6]).decode("utf-8")
                print(
                    f"Received {length} on pipe {pipe_number}:",
                    f"{decoded}{response[7:8][0]}",
                )
                # increment counter from received payload
                if response[7:8][0] < 255:
                    counter[0] = response[7:8][0] + 1
                else:
                    counter[0] = 0
            else:
                print("Received an empty ACK packet")
        else:
            failures += 1
            print("Transmission failed or timed out")
        time.sleep(1)  # let the RX node prepare a new ACK payload
    print(failures, "failures detected. Leaving TX role.")


def slave(timeout: int = 6):
    """Listen for any payloads and print the transaction

    :param int timeout: The number of seconds to wait (with no transmission)
        until exiting function.
    """
    radio.startListening()  # put radio in RX mode

    # setup the first transmission's ACK payload
    buffer = b"World \x00" + bytes(counter)
    # we must set the ACK payload data and corresponding
    # pipe number [0,5]
    radio.writeAckPayload(1, buffer)  # load ACK for first response

    start_timer = time.monotonic()  # start timer
    while (time.monotonic() - start_timer) < timeout:
        has_payload, pipe_number = radio.available_pipe()
        if has_payload:
            length = radio.getDynamicPayloadSize()  # grab the payload length
            received = radio.read(length)  # fetch 1 payload from RX FIFO
            # increment counter from received payload
            counter[0] = received[7:8][0] + 1 if received[7:8][0] < 255 else 0
            decoded = [bytes(received[:6]).decode("utf-8")]
            decoded.append(buffer[:6].decode("utf-8"))
            print(
                f"Received {length} bytes on pipe {pipe_number}:",
                f"{decoded[0]}{received[7:8][0]}",
                f"Sent: {decoded[1]}{buffer[7:8][0]}",
            )
            buffer = b"World \x00" + bytes(counter)  # build a new ACK payload
            radio.writeAckPayload(1, buffer)  # load ACK for next response
            start_timer = time.monotonic()  # reset timer

    print("Nothing received in", timeout, "seconds. Leaving RX role")
    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put radio in TX mode & flush unused ACK payloads


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
            "*** Enter 'T' for transmitter role.\n"
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
    print("    Run slave() on receiver\n    Run master() on transmitter")
