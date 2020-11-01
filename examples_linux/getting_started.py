"""
Simple example of using the RF24 class.
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

# addresses needs to be in a buffer protocol object (bytearray)
address = b"1Node"
# It is very helpful to think of an address as a path instead of as
# an identifying device destination

# using the python keyword global is bad practice. Instead we'll use a 1 item
# list to store our float number for the payloads sent
payload = [0.0]

def master(count=5):  # count = 5 will only transmit 5 packets
    """Transmits an incrementing float every second"""
    radio.stopListening()  # ensures the nRF24L01 is in TX mode
    radio.openWritingPipe(address)  # set address of RX node into a TX pipe

    while count:
        # use struct.pack to packetize your data
        # into a usable payload
        buffer = struct.pack("<f", payload[0])
        # 'i' means a single 4 byte int value.
        # '<' means little endian byte order. this may be optional
        start_timer = time.monotonic_ns()  # start timer
        result = radio.write(buffer)
        end_timer = time.monotonic_ns()  # end timer
        if not result:
            print("Transmission failed or timed out")
        else:
            print(
                "Transmission successful! Time to Transmit: "
                "{} us. Sent: {}".format(
                    (end_timer - start_timer) / 1000,
                    payload[0]
                )
            )
            payload[0] += 0.01
        time.sleep(1)
        count -= 1


def slave(count=5):
    """Polls the radio and prints the received value. This method expires
    after 6 seconds of no received transmission"""
    # set address of TX node into an RX pipe. NOTE you MUST specify
    # which pipe number to use for RX, we'll be using pipe 0
    # pipe number options range [0,5]
    # the pipe numbers used during a transmission don't have to match
    radio.openReadingPipe(0, address)
    radio.startListening()  # put radio into RX mode and power up

    start = time.monotonic()
    while count and (time.monotonic() - start) < 6:
        has_payload, pipe_number = radio.available_pipe()
        if has_payload:
            count -= 1
            length = radio.getDynamicPayloadSize()  # grab the payload length
            # fetch 1 payload from RX FIFO
            rx = radio.read(length)  # also clears radio.irq_dr status flag
            # expecting a float, thus the format string "<f"
            # rx[:4] truncates padded 0s in case dynamic payloads are disabled
            payload[0] = struct.unpack("<f", rx[:4])[0]
            # print details about the received packet
            print(
                "{} bytes received on pipe {}: {}".format(
                    length,
                    pipe_number,
                    payload[0]
                )
            )
            start = time.monotonic()  # reset the timeout timer

    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put the nRF24L01 is in TX mode


print(
    """\
    RF24/examples_linux/getting_started\n\
    Run slave() on receiver\n\
    Run master() on transmitter"""
)
