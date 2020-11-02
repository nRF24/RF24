"""
Simple example of detecting (and verifying) the IRQ (interrupt) pin on the
nRF24L01
"""
import time
import RPi.GPIO as GPIO
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

# initialize the nRF24L01 on the spi bus
if not radio.begin():
    print("nRF24L01 hardware isn't responding")
    exit()  # quit now

# this example uses the ACK payload to trigger the IRQ pin active for
# the "on data received" event
radio.enableAckPayload()  # enable ACK payloads

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# for debugging
radio.printDetails()

# address needs to be in a buffer protocol object (bytearray is preferred)
address = b"1Node"
# It is very helpful to think of an address as a path instead of as
# an identifying device destination

# select your digital input pin that's connected to the IRQ pin on the nRF24L01
irq_pin = 12

# setup GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(irq_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# For this example, we'll be using a payload containing
# a string that changes on every transmission. (successful or not)
# Make a couple tuples of payloads & an iterator to traverse them
pl_iterator = [0]  # use a 1-item list instead of python's global keyword
tx_payloads = (b"Ping ", b"Pong ", b"Radio", b"1FAIL")
ack_payloads = (b"Yak ", b"Back", b" ACK")


def interrupt_handler():
    """This function is called when IRQ pin is detected active LOW"""
    print("IRQ pin went active LOW.")
    tx_ds, tx_df, rx_dr = radio.whatHappened()   # update IRQ status flags
    print("\ttx_ds: {}, tx_df: {}, rx_dr: {}".format(tx_ds, tx_df, rx_dr))
    if pl_iterator[0] == 0 and rx_dr:
        print(
            "'data ready' event test {}".format(
                "passed" if rx_dr else "failed"
            )
        )
    elif pl_iterator[0] == 1:
        print(
            "'data sent' event test {}".format(
                "passed" if tx_ds else "failed"
            )
        )
    elif pl_iterator[0] == 2:
        print(
            "'data fail' event test {}".format(
                "passed" if tx_df else "failed"
            )
        )


def _wait_for_irq():
    """wait till irq_pin goes active, print IRQ status
    flags."""
    while GPIO.input(irq_pin) == GPIO.HIGH:
        # IRQ pin is LOW when activated. Otherwise it is always HIGH
        # Wait in this empty loop until IRQ pin is activated.
        #
        # In this example, the "data fail" event is always configured to
        # trigger the IRQ pin active. Because the auto-ACK feature is on by
        # default, we don't need a timeout check to prevent an infinite loop.
        pass
    interrupt_handler()


def master():
    """Transmits 3 times: successfully receive ACK payload first, successfully
    transmit on second, and intentionally fail transmit on the third"""
    radio.stopListening()  # ensures the nRF24L01 is in TX mode
    radio.openWritingPipe(address)  # set address of RX node into a TX pipe

    # on data ready test
    print("\nConfiguring IRQ pin to only ignore 'on data sent' event")
    radio.maskIRQ(True, False, False)  # args = tx_ds, tx_df, rx_dr
    print("    Pinging slave node for an ACK payload...", end=" ")
    pl_iterator[0] = 0
    radio.startWrite(tx_payloads[0], False)  # False means expecting an ACK
    _wait_for_irq()

    # on "data sent" test
    print("\nConfiguring IRQ pin to only ignore 'on data ready' event")
    radio.maskIRQ(False, False, True)  # args = tx_ds, tx_df, rx_dr
    print("    Pinging slave node again...             ", end=" ")
    pl_iterator[0] = 1
    radio.startWrite(tx_payloads[1], False)  # False means expecting an ACK
    _wait_for_irq()

    # trigger slave node to exit by filling the slave node's RX FIFO
    print("\nSending one extra payload to fill RX FIFO on slave node.")
    if radio.write(tx_payloads[2]):
        # when send_only parameter is True, send() ignores RX FIFO usage
        print("Slave node should not be listening anymore.")
    else:
        print("Slave node was unresponsive.")

    # on "data fail" test
    print("\nConfiguring IRQ pin to go active for all events.")
    radio.maskIRQ(False, False, False)  # args = tx_ds, tx_df, rx_dr
    print("    Sending a ping to inactive slave node...", end=" ")
    radio.flush_tx()  # just in case any previous tests failed
    pl_iterator[0] = 2
    radio.startWrite(tx_payloads[3], False)  # False means expecting an ACK
    _wait_for_irq()
    radio.flush_tx()  # flush artifact payload in TX FIFO from last test
    # all 3 ACK payloads received were 4 bytes each, and RX FIFO is full
    # so, fetching 12 bytes from the RX FIFO also flushes RX FIFO
    print("\nComplete RX FIFO:", radio.read(12))


def slave(timeout=6):  # will listen for 6 seconds before timing out
    """Only listen for 3 payload from the master node"""
    # setup radio to recieve pings, fill TX FIFO with ACK payloads
    radio.openReadingPipe(0, address)
    radio.writeAckPayload(0, ack_payloads[0])
    radio.writeAckPayload(0, ack_payloads[1])
    radio.writeAckPayload(0, ack_payloads[2])
    radio.startListening()  # start listening & clear irq_dr flag
    start_timer = time.monotonic()  # start timer now
    while not radio.rxFifoFull() and time.monotonic() - start_timer < timeout:
        # if RX FIFO is not full and timeout is not reached, then keep waiting
        pass
    time.sleep(0.5)  # wait for last ACK payload to transmit
    radio.stopListening()  # put radio in TX mode & discard any ACK payloads
    if radio.available():  # if RX FIFO is not empty (timeout did not occur)
        # all 3 payloads received were 5 bytes each, and RX FIFO is full
        # so, fetching 15 bytes from the RX FIFO also flushes RX FIFO
        print("Complete RX FIFO:", radio.read(15))


print(
    """\
    nRF24L01 Interrupt pin test.\n\
    Make sure the IRQ pin is connected to the RPi GPIO12\n\
    Run slave() on receiver\n\
    Run master() on transmitter"""
)
