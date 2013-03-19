Raspberry Pi RF24 libraries
===========================

This is the collection of libraries for RF24 / NRF24L01 wireless modules on the raspberry pi.

There are two folders with two different libraries :-

- librf24 	 This library/driver are ported from Arduino to beaglebone then to RPi
- librf24-bcm 	 This library/driver are further ported to use Broadcom bcm2835 using hardware SPI

Setup
=====
1. Change to the selected folder
2. Execute "make" and "sudo make install" to install the shared libraries
3. Change to examples folder, change to the correct connected pins and execte "make"



Known issues
============
- the current bcm2835 drivers still have some minor bugs

Links 
=====
- Forum links : http://www.raspberrypi.org/phpBB3/viewtopic.php?f=45&t=17061
- C library for Broadcom BCM 2835 http://www.open.com.au/mikem/bcm2835/index.html
- Maniacbug RF24 http://maniacbug.github.com/RF24/index.html
- RF24 Class Reference http://maniacbug.github.com/RF24/classRF24.html


Contact
=======
Stanley Seow ( stanleyseow@gmail.com )
https://github.com/stanleyseow/RF24

RF24 for RPi using gpio :-
Arco van Geest <arco@appeltaart.mine.nu> 
https://github.com/gnulnulf/RF24

RF24 for RPi using bcm2835 :-
Charles-Henri Hallard http://hallard.me/ 
https://github.com/hallard/RF24
