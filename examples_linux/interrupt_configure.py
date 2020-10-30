"""!
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
ce_pin = 22
# Generic:
radio = RF24(ce_pin, 0)
# RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and
# set 'this->device = "/dev/spidev0.0";;' or as listed in /dev

# initialize the nRF24L01 on the spi bus
radio.begin()

# this example uses the ACK payload to trigger the IRQ pin active for
# the "on data received" event
radio.enableAckPayloads()  # enable ACK payloads

# set the Power Amplifier level to -12 dBm since this test example is
# usually run with nRF24L01 transceivers in close proximity of each other
radio.setPALevel(RF24_PA_LOW)  # RF24_PA_MAX is default

# address needs to be in a buffer protocol object (bytearray is preferred)
address = b"1Node"

# select your digital input pin that's connected to the IRQ pin on the nRF4L01
irq_pin = 12

# setup GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(irq_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(ce_pin, GPIO.OUT)


def interrupt_handler():
    """This function is called when IRQ pin is detected active LOW"""
    print("IRQ pin went active LOW.")
    tx_ds, tx_df, rx_dr = (False, False, False)
    radio.whatHappened(tx_ds, tx_df, rx_dr)  # update irq_d? status flags
    print("\ttx_ds: {}, tx_df: {}, rx_dr: {}".format(tx_ds, tx_df, rx_dr))


def _ping():
    """transmit 1 payload, wait till irq_pin goes active, print IRQ status
    flags."""
    # ce_pin is set HIGH by startFastWrite() telling radio to start sending
    time.sleep(0.00001)  # mandatory 10 microsecond pulse starts transmission
    GPIO.output(ce_pin, GPIO.LOW)  # end 10 us pulse; use 1 level from TX FIFO
    while GPIO.input(irq_pin) == GPIO.LOW:  # IRQ pin is active when LOW
        pass
    interrupt_handler()


def master():
    """Transmits 3 times: successfully receive ACK payload first, successfully
    transmit on second, and intentionally fail transmit on the third"""
    # set address of RX node into a TX pipe
    radio.openWritingPipe(address)
    # ensures the nRF24L01 is in TX mode
    radio.stopListening()
    # NOTE radio.power is automatically set to True on first call to
    # radio.write()
    # NOTE radio.write() internally calls radio.clear_status_flags() first

    # load 2 buffers into the TX FIFO; the last `False` leaves CE pin LOW
    radio.startFastWrite(b"Ping ", 5, False, False)
    radio.startFastWrite(b"Pong ", 5, False, False)

    # on data ready test
    print("\nConfiguring IRQ pin to only ignore 'on data sent' event")
    radio.maskIRQ(True, False, False)  # args = tx_ds, tx_df, rx_dr
    print("    Pinging slave node for an ACK payload...", end=" ")
    _ping()  # CE pin is managed by this function

    # on "data sent" test
    print("\nConfiguring IRQ pin to only ignore 'on data ready' event")
    radio.maskIRQ(False, False, True)  # args = tx_ds, tx_df, rx_dr
    print("    Pinging slave node again...             ", end=" ")
    _ping()  # CE pin is managed by this function

    # trigger slave node to exit by filling the slave node's RX FIFO
    print("\nSending one extra payload to fill RX FIFO on slave node.")
    if radio.write(b"Radio"):
        # when send_only parameter is True, send() ignores RX FIFO usage
        print("Slave node should not be listening anymore.")
    else:
        print("Slave node was unresponsive.")

    # on "data fail" test
    print("\nConfiguring IRQ pin to go active for all events.")
    radio.maskIRQ(False, False, False)  # args = tx_ds, tx_df, rx_dr
    print("    Sending a ping to inactive slave node...", end=" ")
    radio.flush_tx()  # just in case any previous tests failed
    radio.startFastWrite(b"Dummy", 5, False, True)  # True = sets CE pin HIGH
    _ping()  # CE pin is managed by this function
    radio.flush_tx()  # flush artifact payload in TX FIFO from last test
    # all 3 ACK payloads received were 4 bytes each, and RX FIFO is full
    # so, fetching 12 bytes from the RX FIFO also flushes RX FIFO
    print("\nComplete RX FIFO:", radio.recv(12))


def slave(timeout=6):  # will listen for 6 seconds before timing out
    """Only listen for 3 payload from the master node"""
    # setup radio to recieve pings, fill TX FIFO with ACK payloads
    radio.openReadingPipe(0, address)
    radio.writeAckPayload(0, b"Yak ")
    radio.writeAckPayload(0, b"Back")
    radio.writeAckPayload(0, b" ACK")
    radio.startListening()  # start listening & clear irq_dr flag
    start_timer = time.monotonic()  # start timer now
    while not radio.rxFifoFull() and time.monotonic() - start_timer < timeout:
        # if RX FIFO is not full and timeout is not reached, then keep waiting
        pass
    radio.stopListening()  # put radio in TX mode & discard any ACK payloads
    if radio.available():  # if RX FIFO is not empty (timeout did not occur)
        # all 3 payloads received were 5 bytes each, and RX FIFO is full
        # so, fetching 15 bytes from the RX FIFO also flushes RX FIFO
        print("Complete RX FIFO:", radio.read(15))


print(
    """\
    nRF24L01 Interrupt pin test.\n\
    Make sure the IRQ pin is connected to the MCU\n\
    Run slave() on receiver\n\
    Run master() on transmitter"""
)