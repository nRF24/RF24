This is library to use the nrf24l01 on the raspberry pi.

- It was based on the arduino lib from J. Coliz <maniacbug@ymail.com>.
( https://github.com/maniacbug/RF24 ) 

- The library was berryfied by Purinda Gunasekara <purinda@gmail.com>.

- Made into a dynamic linked library by Arco van Geest <arco@appeltaart.mine.nu>
( https://github.com/gnulnulf/RF24 ) 

I'm using the following pins for nRF24L01 and RPi

RPi GPIO 9  (Pin 21) to nRF Pin 7 (MISO)
RPi GPIO 10 (Pin 19) to nRF Pin 6 (MOSI)
RPi GPIO 11 (Pin 23) to nRF Pin 5 (SCK)
RPi GPIO 23 (Pin 16) to nRF Pin 3 (CE)
RPi GPIO 24 (Pin 18) to nRF Pin 4 (CSN)
RPi 3.3V (Pin 17)    to nRF Pin 2 (Vcc)
RPi Gnd  (Pin 25)    to nRF Pin 1 (Gnd)
 
If you do not wish to change the pinout, pls make sure this line is as below :-

RF24 radio("/dev/spidev0.0",8000000,24)

Examples
========

I've written the RPi codes as a hub listening to sensor data from Arduino remote nodes 
Filename : rpi-hub.cpp

Stanley Seow
stanleyseow@gmail.com
http://arduino-for-beginner.blogspot.com


