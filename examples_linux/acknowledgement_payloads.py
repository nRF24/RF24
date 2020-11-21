"""
Simple example of using the library to transmit
and retrieve custom automatic acknowledgment payloads.
"""
import time
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
################## Linux (BBB,x86,etc) #########################
# See http://tmrh20.github.io/RF24/pages.html for more information on usage
# See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
# See https://www.kernel.org/doc/Documentation/spi/spidev for more
# information on SPIDEV

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

# ACK payloads are dynamically sized.
radio.enableDynamicPayloads()  # to use ACK payloads

# to enable the custom ACK payload feature
radio.enableAckPayload()

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# set the TX address of the RX node into the TX pipe
radio.openWritingPipe(address[radio_number])  # always uses pipe 0

# set the RX address of the TX node into a RX pipe
radio.openReadingPipe(1, address[not radio_number])  # using pipe 1

# for debugging, we have 2 options that print a large block of details
# radio.printDetails();  # (smaller) function that prints raw register values
# radio.printPrettyDetails();  # (larger) function that prints human readable data


def master(count=5):  # count = 5 will only transmit 5 packets
    """Transmits a message and an incrementing integer every second.

    :param int count: The number of payloads to transmit (failed or
        successful).
    """
    radio.stopListening()  # put radio in TX mode

    while count:
        # construct a payload to send
        buffer = b"Hello \x00" + bytes(counter)

        # send the payload and prompt
        start_timer = time.monotonic_ns()  # start timer
        result = radio.write(buffer)  # save the report
        end_timer = time.monotonic_ns()  # stop timer
        if result:
            # print timer results upon transmission success
            print(
                "Transmission successful! Time to transmit: "
                "{} us. Sent: {}{}".format(
                    int((end_timer - start_timer) / 1000),
                    buffer[:6].decode("utf-8"),
                    counter[0]
                ),
                end=" "
            )
            has_payload, pipe_number = radio.available_pipe()
            if has_payload:
                # print the received ACK that was automatically sent
                length = radio.getDynamicPayloadSize()
                response = radio.read(length)
                print(
                    "Received {} on pipe {}: {}{}".format(
                        length,
                        pipe_number,
                        bytes(response[:6]).decode("utf-8"),
                        response[7:8][0]
                    )
                )
                counter[0] += 1  # increment payload counter
            else:
                print("Received an empty ACK packet")
        else:
            print("Transmission failed or timed out")
        time.sleep(1)  # let the RX node prepare a new ACK payload
        count -= 1


def slave(timeout=6):
    """Listen for any payloads and print the transaction

    :param int timeout: The number of seconds to wait (with no transmission)
        until exiting function.
    """
    radio.startListening()  # put radio into RX mode, power it up

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
            counter[0] = received[7:8][0] + 1
            print(
                "Received {} bytes on pipe {}: {}{} Sent: {}{}".format(
                    length,
                    pipe_number,
                    bytes(received[:6]).decode("utf-8"),
                    received[7:8][0],
                    buffer[:6].decode("utf-8"),
                    buffer[7:8][0]
                )
            )
            buffer = b"World \x00" + bytes(counter)  # build a new ACK payload
            radio.writeAckPayload(1, buffer)  # load ACK for next response
            start_timer = time.monotonic()  # reset timer

    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put radio in TX mode & flush unused ACK payloads


print(
    """\
    nRF24L01 ACK test\n\
    Run slave() on receiver\n\
    Run master() on transmitter"""
)
