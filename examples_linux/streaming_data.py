"""
Example of library usage for streaming multiple payloads.
"""
import time
from RF24 import RF24, RF24_PA_LOW

# RPi.GPIO will show a warning if any pin is setup() that is already been
# setup() for use without calling cleanup() first
GPIO.cleanup()  # call this now in case it wasn't called on last program exit

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

# For this example, we will use different addresses
# An address need to be a buffer protocol object (bytearray)
address = [b"1Node", b"2Node"]
# It is very helpful to think of an address as a path instead of as
# an identifying device destination

# to use different addresses on a pair of radios, we need a variable to
# uniquely identify which address this radio will use to transmit
# 0 uses address[0] to transmit, 1 uses address[1] to transmit
radio_number = bool(int(input("Which radio is this ('0' or '1')? ")))

# initialize the nRF24L01 on the spi bus
if not radio.begin():
    raise OSError("nRF24L01 hardware isn't responding")

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# set TX address of RX node into the TX pipe
radio.openWritingPipe(address[radio_number])  # always uses pipe 0

# set RX address of TX node into an RX pipe
radio.openReadingPipe(1, address[not radio_number])  # using pipe 1

# for debugging
radio.printDetails()


def make_buffer(buf_iter, size=32):
    """return a list of payloads"""
    # we'll use `size` for the number of payloads in the list and the
    # payloads' length
    # prefix payload with a sequential letter to indicate which
    # payloads were lost (if any)
    buff = bytes([buf_iter + (65 if 0 <= buf_iter < 26 else 71)])
    for j in range(size - 1):
        char = bool(j >= (size - 1) / 2 + abs((size - 1) / 2 - buf_iter))
        char |= bool(j < (size - 1) / 2 - abs((size - 1) / 2 - buf_iter))
        buff += bytes([char + 48])
    return buff


def master(count=1, size=32):
    """Uses all 3 levels of the TX FIFO `RF24.writeFast()`"""
    if size < 6:
        print("setting size to 6;", size, "is not allowed for this test.")
        size = 6

    # save on transmission time by setting the radio to only transmit the
    #  number of bytes we need to transmit
    radio.setPayloadSize(size)  # the default is the maximum 32 bytes

    radio.stopListening()  # ensures the nRF24L01 is in TX mode
    for c in range(count):  # transmit the same payloads this many times
        radio.flush_tx()  # clear the TX FIFO so we can use all 3 levels
        # NOTE the write_only parameter does not initiate sending
        buf_iter = 0  # iterator of payloads for the while loop
        failures = 0  # keep track of manual retries
        start_timer = time.monotonic() * 1000  # start timer
        while buf_iter < size:  # cycle through all the payloads
            buf = make_buffer(buf_iter, size)  # make a payload
            if not radio.writeFast(buf):
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
            buf_iter += 1
        end_timer = time.monotonic() * 1000  # end timer
        print(
            "Transmission took {} ms with {} failures detected.".format(
                end_timer - start_timer,
                failures
            )
        )


def slave(timeout=5, size=32):
    """Stops listening after a `timeout` with no response"""
    # set address of TX node into an RX pipe. NOTE you MUST specify

    # save on transmission time by setting the radio to only transmit the
    #  number of bytes we need to transmit
    radio.setPayloadSize(size)  # the default is the maximum 32 bytes

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
