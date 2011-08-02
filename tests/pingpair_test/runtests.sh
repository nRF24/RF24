#!/bin/sh

# Connect p6 to receiver, p4 to sender
# WARNING: Test config 2 only works with PLUS units.

jam p4 p6 || exit 1
./runtest.py /dev/tty.usbserial-A600eHIs 1 & 
./runtest.py /dev/tty.usbserial-A40081RP 1 || ( kill `jobs -p` && exit 1 )
kill `jobs -p`
./runtest.py /dev/tty.usbserial-A600eHIs 2 & 
./runtest.py /dev/tty.usbserial-A40081RP 2 ||  ( kill `jobs -p` && exit 1 )
kill `jobs -p`
./runtest.py /dev/tty.usbserial-A600eHIs 3 & 
./runtest.py /dev/tty.usbserial-A40081RP 3 || ( kill `jobs -p` && exit 1 ) 
kill `jobs -p`
exit 0
