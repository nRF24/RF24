"""
A simple example of sending data from 1 nRF24L01 transceiver to another
with Acknowledgement (ACK) payloads attached to ACK packets.

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
        print(" Keyboard Interrupt detected. Exiting...")
        radio.powerDown()
        sys.exit()
