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
radio_number = bool(
    int(
        input(
            "Which radio is this? Enter '0' or '1'. Defaults to '0' "
        ) or 0
    )
)

# initialize the nRF24L01 on the spi bus
if not radio.begin():
    raise OSError("nRF24L01 hardware isn't responding")

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# To save time during transmission, we'll set the payload size to be only what
# we need. A float value occupies 4 bytes in memory using len(struct.pack())
# "<b" means a little endian unsigned byte
# we also need an addition 7 bytes for the payload message
radio.setPayloadSize(len(struct.pack("<b", 0)) + 7)

# for debugging
radio.printDetails()

# using the python keyword global is bad practice. Instead we'll use a 1 item
# list to store our float number for the payloads sent
payload = [0]

def master(count=10):
    """Transmits a message and an incrementing integer every second"""
    radio.stopListening()  # ensures the nRF24L01 is in TX mode
    radio.openWritingPipe(address[0])  # set address of RX node into a TX pipe

    while count:  # only transmit `count` packets
        # use struct.pack to packetize your data into a usable payload
        # "<b" means a single little endian unsigned byte.
        # NOTE we added a b"\x00" byte as a c-string's NULL terminating 0
        buffer = b"Hello \x00" + struct.pack("<b", payload[0])
        start_timer = time.monotonic_ns()  # start timer
        result = radio.write(buffer)
        if not result:
            print("Transmission failed or timed out")
        else:
            radio.openReadingPipe(1, address[1])
            radio.startListening()
            timout = time.monotonic() * 1000 + 200  # use 200 ms timeout
            ack = b"\x00" * len(buffer)  # variable used for the response
            while ack[0] == 0 or time.monotonic() * 1000 < timout:
                if radio.available():
                    # get the response & save it to ack variable
                    ack = radio.read(radio.getPayloadSize())
                    radio.stopListening()
                    radio.openWritingPipe(address[0])
            end_timer = time.monotonic_ns()  # end timer
            print(
                "Transmission successful. Sent: {}{}.".format(
                    buffer[:6].decode("utf-8"),
                    payload[0]
                ),
                end=" "
            )
            if ack[0] == 0:
                print("No response received.")
            else:
                # decode response's text as an string
                # NOTE ack[:6] ignores the NULL terminating 0
                response = ack[:6].decode("utf-8")
                # use struct.unpack() to get the repsonse's appended int
                # NOTE ack[7:] discards NULL terminating 0, and
                # "<b" means its a single little endian unsigned byte
                payload[0] = struct.unpack("<b", ack[7:])[0]
                print(
                    "Received: {}{}. Roundtrip delay: {} us.".format(
                        response,
                        payload[0],
                        (end_timer - start_timer) / 1000
                    )
                )
        time.sleep(1)  # make example readable by slowing down transmissions
        count -= 1


def slave(count=10):
    """Polls the radio and prints the received value. This method expires
    after 6 seconds of no received transmission"""
    radio.openReadingPipe(1, address[0])  # set TX address to an RX pipe
    radio.startListening()  # put radio into RX mode and power up

    start_timer = time.monotonic()  # start a timer to detect timeout
    while count and (time.monotonic() - start_timer) < 6:
        # receive `count` payloads or wait 6 seconds till timing out
        has_payload, pipe_number = radio.available_pipe()
        if has_payload:
            count -= 1
            length = radio.getPayloadSize()  # grab the payload length
            received = radio.read(length)  # fetch 1 payload from RX FIFO
            # use struct.unpack() to get the payload's appended int
            # NOTE received[7:] discards NULL terminating 0, and
            # "<b" means its a single little endian unsigned byte
            payload[0] = struct.unpack("<b", received[7:])[0] + 1
            # use bytes() to packetize our data into a usable payload
            # NOTE b"\x00" byte is a c-string's NULL terminating 0
            buffer = b"World \x00" + bytes([payload[0]])
            # save response's result
            response = radio.write(buffer)
            # print the payload received and the response's payload
            print(
                "Received {} bytes on pipe {}: {}{}.".format(
                    length,
                    pipe_number,
                    received[:6].decode("utf-8"),
                    payload[0] - 1
                ),
                end=" "
            )
            if response:
                print(
                    "Sent: {}{}".format(
                        buffer[:6].decode("utf-8"),
                        payload[0]
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
