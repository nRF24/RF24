#!/bin/sh

# Connect p6 to receiver, p4 to sender

jam p4 p6 || exit 1
./runtest.py /dev/tty.usbserial-A600eHIs 1 & 
./runtest.py /dev/tty.usbserial-A40081RP 1 || ( kill `jobs -p` && exit 1 ) 
kill `jobs -p`
exit 0
