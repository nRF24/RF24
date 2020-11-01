"""
Example of library usage for streaming multiple payloads.
"""
import time
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


def make_buffers(size=32):
    """return a list of payloads"""
    buffers = []
    # we'll use `size` for the number of payloads in the list and the
    # payloads' length
    for i in range(size):
        # prefix payload with a sequential letter to indicate which
        # payloads were lost (if any)
        buff = bytes([i + (65 if 0 <= i < 26 else 71)])
        for j in range(size - 1):
            char = bool(j >= (size - 1) / 2 + abs((size - 1) / 2 - i))
            char |= bool(j < (size - 1) / 2 - abs((size - 1) / 2 - i))
            buff += bytes([char + 48])
        buffers.append(buff)
        del buff
    return buffers


def master(count=1, size=32):
    """Uses all 3 levels of the TX FIFO `RF24.writeFast()`"""
    if size < 6:
        print("setting size to 6;", size, "is not allowed for this test.")
        size = 6
    buf = make_buffers(size)  # make a list of payloads
    radio.stopListening()  # ensures the nRF24L01 is in TX mode
    radio.openWritingPipe(address)  # set address of RX node into a TX pipe
    for c in range(count):  # transmit the same payloads this many times
        radio.flush_tx()  # clear the TX FIFO so we can use all 3 levels
        # NOTE the write_only parameter does not initiate sending
        buf_iter = 0  # iterator of payloads for the while loop
        failures = 0  # keep track of manual retries
        start_timer = time.monotonic() * 1000  # start timer
        while buf_iter < size:  # cycle through all the payloads
            if radio.writeFast(buf[buf_iter], size):
                # reception failed; we need to reset the irq_rf flag
                failures += 1  # increment manual retries
                radio.reUseTX()
                if failures > 99 and buf_iter < 7 and c < 2:
                    # we need to prevent an infinite loop
                    print(
                        "Make sure slave() node is listening."
                        " Quiting master_fifo()"
                    )
                    buf_iter = size + 1  # be sure to exit the while loop
                    radio.flush_tx()  # discard all payloads in TX FIFO
                    break
        end_timer = time.monotonic() * 1000  # end timer
        print(
            "Transmission took {} ms with {} failures detected.".format(
                end_timer - start_timer,
                failures
            )
        )


def slave(timeout=5):
    """Stops listening after a `timeout` with no response"""
    # set address of TX node into an RX pipe. NOTE you MUST specify
    # which pipe number to use for RX, we'll be using pipe 0
    radio.openReadingPipe(0, address)  # pipe number options range [0,5]
    radio.startListening()  # put radio into RX mode and power up
    count = 0  # keep track of the number of received payloads
    start_timer = time.monotonic()  # start timer
    while time.monotonic() < start_timer + timeout:
        if radio.available():
            count += 1
            # retreive the received packet's payload
            length = radio.getDynamicPayloadSize()
            receive_payload = radio.read(length)
            print("Received: {} - {}".format(receive_payload, count))
            start_timer = time.monotonic()  # reset timer on every RX payload

    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put the nRF24L01 is in TX mode


print(
    """\
    RF24/examples_linux/streaming_data.py\n\
    Run slave() on receiver\n\
    Run master() on transmitter to use all 3 levels of the TX FIFO."""
)
