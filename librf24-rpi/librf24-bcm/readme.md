this is library to use the nrf24l01 on the raspberry pi.

it's based on the arduino lib from J. Coliz <maniacbug@ymail.com>.
the library was berryfied by Purinda Gunasekara <purinda@gmail.com>.
then forked from github stanleyseow/RF24 by myself

usage
=====

Get the repo, then go into the folder ./RF24/librf24-rpi/librf24-bcm
then issue

make ; make install

Then you can fire up the example, but do not forget to change the RF24 instance according to your connection

examples
========

In the examples I used and GPIO22 and CE1 on my ArduiPi board 
http://hallard.me/arduipi as follow

// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_26, BCM2835_SPI_SPEED_8MHZ);  

I have a model 1 rpi so you should check if the pins are on the same spot
NRF24L01   RPI       P1 Connector pin
nrf-vcc = rpi-3v3    (1)
nrf-gnd = rpi-gnd    (6)
nrf-ce  = rpi-gpio22 (15)
nrf-csn = rpi-ce1    (26)
nrf-sck = rpi-sckl   (23)
nrf-mo  = rpi-mosi   (19)
nrf-mi  = rpi-miso   (21)

known issues
============
none

contact
=======
Charles-Hendi Hallard (http://hallard.me)

