#!/bin/sh

# Connect p6 to receiver, p4 to sender

jam p4 p6 || exit 1
./runtest.py /dev/tty.usbserial-A600eHIs || exit 1
./runtest.py /dev/tty.usbserial-A40081RP || exit 1
exit 0
