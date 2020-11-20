"""
Simple example of using the RF24 class to transmit and respond with
acknowledgment (ACK) transmissions. Notice that the auto-ack feature is
enabled, but this example doesn't use automatic ACK payloads because automatic
ACK payloads' data will always be outdated by 1 transmission. Instead, this
example uses a call and response paradigm.
"""
import time
import struct
from RF24 import RF24, RF24_PA_LOW


########### USER CONFIGURATION ###########
# See https://github.com/TMRh20/RF24/blob/master/pyRF24/readme.md
# Radio CE Pin, CSN Pin, SPI Speed
# CE Pin uses GPIO number with BCM and SPIDEV drivers, other platforms use
# their own pin numbering
# CS Pin addresses the SPI bus number at /dev/spidev<a>.<b>
# ie: RF24 radio(<ce_pin>, <a>*10+<b>); spidev1.0 is 10, spidev1.1 is 11 etc..

# Generic:
radio = RF24(22, 0)
# RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and
# set 'this->device = "/dev/spidev0.0";;' or as listed in /dev

# using the python keyword global is bad practice. Instead we'll use a 1 item
# list to store our integer number for the payloads' counter
counter = [0]

# For this example, we will use different addresses
# An address need to be a buffer protocol object (bytearray)
address = [b"1Node", b"2Node"]
# It is very helpful to think of an address as a path instead of as
# an identifying device destination

# to use different addresses on a pair of radios, we need a variable to
# uniquely identify which address this radio will use to transmit
# 0 uses address[0] to transmit, 1 uses address[1] to transmit
radio_number = bool(
    int(
        input(
            "Which radio is this? Enter '0' or '1'. Defaults to '0' "
        ) or 0
    )
)

# initialize the nRF24L01 on the spi bus
if not radio.begin():
    raise RuntimeError("radio is not responding")

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# set the TX address of the RX node into the TX pipe
radio.openWritingPipe(address[radio_number])  # always uses pipe 0

# set the RX address of the TX node into a RX pipe
radio.openReadingPipe(1, address[not radio_number])  # using pipe 1

# To save time during transmission, we'll set the payload size to be only what
# we need. For this example, we'll be using a byte for the payload counter and
# 7 bytes for the payload message
radio.payloadSize = 8

# for debugging, we have 2 options that print a large block of details
# radio.printDetails();  # (smaller) function that prints raw register values
# radio.printPrettyDetails();  # (larger) function that prints human readable data


def master(count=5):
    """Transmits a message and an incrementing integer every second, then
    wait for a response for up to 200 ms.

    :param int count: The number of payloads to transmit (failed or
        successful).
    """
    radio.stopListening()  # ensures the nRF24L01 is in TX mode

    while count:  # only transmit `count` packets
        # use bytes() to pack our counter data into the payload
        # NOTE b"\x00" byte is a c-string's NULL terminating 0
        buffer = b"Hello \x00" + bytes(counter)
        start_timer = time.monotonic_ns()  # start timer
        result = radio.write(buffer)
        if not result:
            print("Transmission failed or timed out")
        else:
            radio.startListening()
            timout = time.monotonic() * 1000 + 200  # use 200 ms timeout
            # declare a variable to save the incoming response
            while not radio.available() and time.monotonic() * 1000 < timout:
                pass  # wait for incoming payload or timeout
            radio.stopListening()
            end_timer = time.monotonic_ns()  # end timer
            print(
                "Transmission successful. Sent: {}{}.".format(
                    buffer[:6].decode("utf-8"),
                    counter[0]
                ),
                end=" "
            )
            has_payload, pipe_number = radio.available_pipe()
            if has_payload:
                # grab the incoming payload
                received = radio.read(radio.payloadSize)
                # NOTE received[7:8] discards NULL terminating 0
                counter[0] = received[7:8][0]  # save the counter
                print(
                    "Received {} bytes on pipe {}: {}{}. "
                    "Round-trip delay: {} us.".format(
                        radio.payloadSize,
                        pipe_number,
                        bytes(received[:6]).decode("utf-8"),
                        counter[0],
                        (end_timer - start_timer) / 1000
                    )
                )
            else:
                print("No response received.")
        time.sleep(1)  # make example readable by slowing down transmissions
        count -= 1


def slave(timeout=6):
    """Listen for any payloads and print the transaction

    :param int timeout: The number of seconds to wait (with no transmission)
        until exiting function.
    """
    radio.startListening()  # put radio into RX mode and power up

    start_timer = time.monotonic()  # start a timer to detect timeout
    while (time.monotonic() - start_timer) < timeout:
        # receive `count` payloads or wait 6 seconds till timing out
        has_payload, pipe_number = radio.available_pipe()
        if has_payload:
            received = radio.read(radio.payloadSize)  # fetch the payload
            # NOTE received[7:8] discards NULL terminating 0
            counter[0] = received[7:8][0] + 1  # increment the counter
            # use bytes() to pack our counter data into the payload
            # NOTE b"\x00" byte is a c-string's NULL terminating 0
            buffer = b"World \x00" + bytes(counter)
            # save response's result
            result = radio.write(buffer)
            # print the payload received payload
            print(
                "Received {} bytes on pipe {}: {}{}.".format(
                    radio.payloadSize,
                    pipe_number,
                    bytes(received[:6]).decode("utf-8"),
                    received[7:8][0]
                ),
                end=" "
            )
            if result:  # did response succeed?
                # print response's payload
                print(
                    "Sent: {}{}".format(
                        buffer[:6].decode("utf-8"),
                        counter[0]
                    )
                )
            else:
                print("Response failed or timed out")
            start_timer = time.monotonic()  # reset the timeout timer

    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put the nRF24L01 is in TX mode


print(
    """\
    RF24/examples_linux/manual_acknowledgements\n\
    Run slave() on receiver\n\
    Run master() on transmitter"""
)
