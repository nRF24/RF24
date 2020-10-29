"""!
Simple example of using the library to transmit
and retrieve custom automatic acknowledgment payloads.
"""
import time
import struct
import RPi.GPIO as GPIO
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

# initialize the nRF24L01 on the spi bus
radio.begin()

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# to enable the custom ACK payload feature
radio.enableAckPayload()

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# addresses needs to be in a buffer protocol object (bytearray)
address = b"1Node"

# using the python keyword global is bad practice. Instead we'll use a 1 item
# list to store our integer number for the payloads' counter
counter = [0]


def master(count=5):  # count = 5 will only transmit 5 packets
    """Transmits a payload every second and prints the ACK payload"""
    radio.stopListening()  # put radio in TX mode
    radio.openWritingPipe(address)  # set address of RX node into a TX pipe

    while count:
        # construct a payload to send
        buffer = b"Hello \x00" + struct.pack("<I", counter[0])

        # send the payload and prompt
        start_timer = time.monotonic() * 1000  # start timer
        result = radio.write(buffer)  # save the report
        end_timer = time.monotonic() * 1000  # stop timer
        print("Sent:", buffer, end=" ")
        if result:
            # print timer results upon transmission success
            print("Transmission took", end_timer - start_timer, end=" ")
            if radio.available():
                # print the received ACK that was automatically sent
                result = radio.read(radio.getDynamicPayloadSize())
                print("ms Received:", result)
                counter[0] += 1  # increment payload counter
        else:
            print("Transmission failed or timed out")
        time.sleep(1)  # let the RX node prepare a new ACK payload
        count -= 1


def slave(count=5):
    """Prints the received value and sends an ACK payload"""
    # set address of TX node into an RX pipe. NOTE you MUST specify
    # which pipe number to use for RX; we'll be using pipe 0
    radio.openReadingPipe(0, address)
    radio.startListening()  # put radio into RX mode, power it up

    # setup the first transmission's ACK payload
    buffer = b"World \x00" + struct.pack("<i", counter[0])
    # we must set the ACK payload data and corresponding
    # pipe number [0,5]
    radio.writeAckPayload(0, buffer)  # load ACK for first response

    start = time.monotonic()  # start timer
    while count and (time.monotonic() - start) < 6:  # use 6 second timeout
        if radio.available():
            count -= 1
            # fetch the received packet's payload
            rx = radio.radio(radio.getDynamicPayloadSize())
            # increment counter from received payload
            counter[0] = struct.unpack("<i", rx[7:])[0] + 1
            print("Received: {} Sent: {}".format(rx, buffer))
            start = time.monotonic()  # reset timer
            if count:  # Going again?
                # build a new ACK
                buffer = b"World \x00" + struct.pack("<i", counter[0])
                radio.writeAckPayload(0, buffer)  # load ACK for next response

    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put radio in TX mode & flush unused ACK payloads


print(
    """\
    nRF24L01 ACK test\n\
    Run slave() on receiver\n\
    Run master() on transmitter"""
)
