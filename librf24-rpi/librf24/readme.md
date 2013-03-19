this is library to use the nrf24l01 on the raspberry pi.

it's based on the arduino lib from J. Coliz <maniacbug@ymail.com>.
the library was berryfied by Purinda Gunasekara <purinda@gmail.com>.

examples
========
you need to set the library path:
cd examples
export LD_LIBRARY_PATH=.
./pingtest

In my examples I used /dev/spidev0.0 and GPIO25
I have a model 1 rpi so you should check if the pins are on the same spot
nrf-vcc = rpi-3v3 (1)
nrf-gnd = rpi-gnd (6)
nrf-ce =  rpi-ce0 (24)
nrf-csn = rpi-gpio25 (22)
nrf-sck = rpi-sckl (23)
nrf-mo = rpi-mosi (19)
nrf-mi = rpi-miso (21)

known issues
============
spidev0.0 or spidev0.1 doesn't seem to work. 

contact
=======
Arco van Geest <arco@appeltaart.mine.nu>


