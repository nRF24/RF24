"""
A simple example of sending data from 1 nRF24L01 transceiver to another
with manually transmitted (non-automatic) Acknowledgement (ACK) payloads.
This example still uses ACK packets, but they have no payloads. Instead the
acknowledging response is sent with `write()`. This tactic allows for more
updated acknowledgement payload data, where actual ACK payloads' data are
outdated by 1 transmission because they have to loaded before receiving a
transmission.

This example was written to be used on 2 devices acting as 'nodes'.
"""
import sys
import argparse
import time
from RF24 import RF24, RF24_PA_LOW


parser = argparse.ArgumentParser(
    description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
)
parser.add_argument(
    "-n",
    "--node",
    type=int,
    choices=range(2),
    help="the identifying radio number (or node ID number)",
)
parser.add_argument(
    "-r",
    "--role",
    type=int,
    choices=range(2),
    help="'1' specifies the TX role. '0' specifies the RX role.",
)

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
# See http://nRF24.github.io/RF24/pages.html for more information on usage
# See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
# See https://www.kernel.org/doc/Documentation/spi/spidev for more
# information on SPIDEV

# using the python keyword global is bad practice. Instead we'll use a 1 item
# list to store our integer number for the payloads' counter
counter = [0]


def master():
    """Transmits a message and an incrementing integer every second, then
    wait for a response for up to 200 ms.
    """
    radio.stopListening()  # put radio in TX mode
    failures = 0
    while failures < 6:
        # use bytes() to pack our counter data into the payload
        # NOTE b"\x00" byte is a c-string's NULL terminating 0
        buffer = b"Hello \x00" + bytes(counter)
        start_timer = time.monotonic_ns()  # start timer
        result = radio.write(buffer)
        if not result:
            failures += 1
            print("Transmission failed or timed out")
        else:
            radio.startListening()  # put radio in RX mode
            timout = time.monotonic() * 1000 + 200  # use 200 ms timeout
            # declare a variable to save the incoming response
            while not radio.available() and time.monotonic() * 1000 < timout:
                pass  # wait for incoming payload or timeout
            radio.stopListening()  # put radio in TX mode
            end_timer = time.monotonic_ns()  # end timer
            decoded = buffer[:6].decode("utf-8")
            print(
                f"Transmission successful. Sent: {decoded}{counter[0]}.",
                end=" ",
            )
            has_payload, pipe_number = radio.available_pipe()
            if has_payload:
                # grab the incoming payload
                received = radio.read(radio.payloadSize)
                # NOTE received[7:8] discards NULL terminating 0
                counter[0] = received[7:8][0]  # save the counter
                decoded = bytes(received[:6]).decode("utf-8")
                print(
                    f"Received {radio.payloadSize} bytes",
                    f"on pipe {pipe_number}: {decoded}{counter[0]}.",
                    f"Round-trip delay: {(end_timer - start_timer) / 1000} us.",
                )
            else:
                print("No response received.")
        time.sleep(1)  # make example readable by slowing down transmissions
    print(failures, "failures detected. Leaving TX role.")


def slave(timeout: int = 6):
    """Listen for any payloads and print the transaction

    :param int timeout: The number of seconds to wait (with no transmission)
        until exiting function.
    """
    radio.startListening()  # put radio in RX mode

    start_timer = time.monotonic()  # start a timer to detect timeout
    while (time.monotonic() - start_timer) < timeout:
        # receive `count` payloads or wait 6 seconds till timing out
        has_payload, pipe_number = radio.available_pipe()
        if has_payload:
            received = radio.read(radio.payloadSize)  # fetch the payload
            # NOTE received[7:8] discards NULL terminating 0
            # increment the counter from received payload
            counter[0] = received[7:8][0] + 1 if received[7:8][0] < 255 else 0
            # use bytes() to pack our counter data into the payload
            # NOTE b"\x00" byte is a c-string's NULL terminating 0
            buffer = b"World \x00" + bytes(counter)
            radio.stopListening()  # put radio in TX mode
            radio.writeFast(buffer)  # load response into TX FIFO
            # keep retrying to send response for 150 milliseconds
            result = radio.txStandBy(150)  # save response's result
            # NOTE txStandBy() flushes TX FIFO on transmission failure
            radio.startListening()  # put radio back in RX mode
            # print the payload received payload
            decoded = bytes(received[:6]).decode("utf-8")
            print(
                f"Received {radio.payloadSize} bytes"
                f"on pipe {pipe_number}: {decoded}{received[7:8][0]}.",
                end=" ",
            )
            if result:  # did response succeed?
                # print response's payload
                decoded = buffer[:6].decode("utf-8")
                print(f"Sent: {decoded}{counter[0]}")
            else:
                print("Response failed or timed out")
            start_timer = time.monotonic()  # reset the timeout timer

    print("Nothing received in", timeout, "seconds. Leaving RX role")
    # recommended behavior is to keep in TX mode while idle
    radio.stopListening()  # put the radio in TX mode


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

    args = parser.parse_args()  # parse any CLI args

    # initialize the nRF24L01 on the spi bus
    if not radio.begin():
        raise RuntimeError("radio hardware is not responding")

    # For this example, we will use different addresses
    # An address need to be a buffer protocol object (bytearray)
    address = [b"1Node", b"2Node"]
    # It is very helpful to think of an address as a path instead of as
    # an identifying device destination

    print(sys.argv[0])  # print example name

    # to use different addresses on a pair of radios, we need a variable to
    # uniquely identify which address this radio will use to transmit
    # 0 uses address[0] to transmit, 1 uses address[1] to transmit
    radio_number = args.node  # uses default value from `parser`
    if args.node is None:  # if '--node' arg wasn't specified
        radio_number = bool(
            int(input("Which radio is this? Enter '0' or '1'. Defaults to '0' ") or 0)
        )

    # set the Power Amplifier level to -12 dBm since this test example is
    # usually run with nRF24L01 transceivers in close proximity of each other
    radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

    # set the TX address of the RX node into the TX pipe
    radio.openWritingPipe(address[radio_number])  # always uses pipe 0

    # set the RX address of the TX node into a RX pipe
    radio.openReadingPipe(1, address[not radio_number])  # using pipe 1

    # To save time during transmission, we'll set the payload size to be only
    # what we need. For this example, we'll be using a byte for the
    # payload counter and 7 bytes for the payload message
    radio.payloadSize = 8

    # for debugging, we have 2 options that print a large block of details
    # (smaller) function that prints raw register values
    # radio.printDetails()
    # (larger) function that prints human readable data
    # radio.printPrettyDetails()

    try:
        if args.role is None:  # if not specified with CLI arg '-r'
            while set_role():
                pass  # continue example until 'Q' is entered
        else:  # if role was set using CLI args
            # run role once and exit
            if bool(args.role):
                master()
            else:
                slave()
    except KeyboardInterrupt:
        print(" Keyboard Interrupt detected. Powering down radio.")
        radio.powerDown()
