# Optimized High Speed Arduino/Rapsberry Pi/LittleWire driver for nRF24L01 2.4GHz Wireless Transceiver
  
Design Goals: This library is designed to be...  
  
* More compliant with the manufacturer specified operation of the chip, while allowing advanced users
* to work outside the reccommended operation. 
* Utilize the capabilities of the radio to their full potential via Arduino
* More reliable and feature rich  
* Easy for beginners to use, with well documented examples and features 
* Consumed with a public interface that's similiar to other Arduino standard libraries  
* Built against the standard SPI library.   
  
April 2014: Official Release: Still some work to do, but most benefits have been realized

* The library has been tweaked to allow full use of the FIFO buffers for maximum transfer speeds
* Changes to read() and available () functionality have increased reliability and response
* Extended timeout periods have been added to aid in noisy or otherwise unreliable environments
* Delays have been removed where possible to ensure maximum efficiency
* Full Due support with extended SPI functions
* ATTiny 24/44/84 25/45/85 now supported.
* More! See the links below and class documentation for more info.
  
Please refer to:  
  
* [Documentation Main Page](http://tmrh20.github.io/)  
* [Class Reference]( http://tmrh20.github.io/RF24/classRF24.html)  
* [Source Code](https://github.com/tmrh20/RF24)  
* [Downloads](https://github.com/TMRh20/RF24/archive/master.zip)  
* [Chip Datasheet](http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf)  
  
This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or  
the SPI hardware will go into 'slave' mode.  
  
Supported Boards:  
  
* Uno, Nano, etc (328 based boards)  
* Mega Types (2560, 1280, etc)  
* ARM (Arduino Due) via extended SPI methods 
* ATTiny 24/44/84 25/45/85  
* Raspberry Pi
* See the [documentation](http://tmrh20.github.io/) for more info

## µC Pin layout

The table below shows how to connect the the pins of the NRF24L01(+) to different boards.
CE and CSN are configurable.

| PIN | NRF24L01 | Arduino UNO | ATtiny25/45/85 [0] | ATtiny44/84 [1] | LittleWire [2]
|-----|----------|-------------|--------------------|-----------------|--------------
|  1  |   GND    |   GND       |     pin 4          |    pin 14       | GND
|  2  |   VCC    |   3.3V      |     pin 8          |    pin  1       | regulator 3.3V required
|  3  |   CE     |   digIO 7   |     pin 2          |    pin 12       | pin to 3.3V
|  4  |   CSN    |   digIO 8   |     pin 3          |    pin 11       | RESET
|  5  |   SCK    |   digIO 13  |     pin 7          |    pin  9       | SCK
|  6  |   MOSI   |   digIO 11  |     pin 6          |    pin  7       | MOSI
|  7  |   MISO   |   digIO 12  |     pin 5          |    pin  8       | MISO
|  8  |   IRQ    |      -      |        -           |         -       | -

[0] https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/attiny85-use-hints

[1] http://highlowtech.org/?p=1695

[2] http://littlewire.cc/

### LittleWire

In order to connect it directly to your LittleWire powered device (ATtiny85-based), you need

* on the hardware side: regulated 3.3 volts by using some DC-DC converter like TSC295033
* [LittleWire Wrapper library](https://github.com/lnxbil/LittleWireSPI) by [lnxbil](https://github.com/lnxbil) to bridge SPI to the computer.

## Raspberry Pi

### Configuration:  
   
 Library functions are mostly the same.  
 See the included examples for RPi specific usage  
 
### Raspberry Pi - Possible pre-configuration:  
If SPI is not already enabled, load it on boot:   

    sudo raspi-config  

A. Update the tool via the menu as required  
B. Select Advanced and enable the SPI kernel module      
C. Update other software and libraries:  

     sudo apt-get update  
     sudo apt-get upgrade  


#New: RPi RF24 Library Installer for all RF24 libraries

A. Download the install.sh file from http://tmrh20.github.io/RF24Installer/RPi/install.sh

    wget http://tmrh20.github.io/RF24Installer/RPi/install.sh  	

B. Make it executable:

    chmod +x install.sh  

C. Run it and choose your options:  

    ./install.sh  

D. Run an example file from one of the libraries:

    cd rf24libs/RF24/examples_RPi  
    make  
    sudo ./gettingstarted  
    


### RPi - RF24 Quick-Start  
     

A. Make a directory to contain the RF24 and possibly RF24Network lib and enter it:  

    mkdir ~/rf24libs  
    cd ~/rf24libs  

B.  Clone the RF24 Repo  

    git clone https://github.com/tmrh20/RF24.git RF24  

C.  Change to the new RF24 directory    

    cd RF24  

D. Build the library, and run an example file:  

    sudo make install
    cd examples_RPi  
    make  
    sudo ./gettingstarted  
  

### RPi - RF24Network Quick-Start  

A. Enter the same directory that contains the RF24 library folder  

    cd ~/rf24libs  

B. Clone the RF24Network Repo  

    git clone https://github.com/tmrh20/RF24Network.git RF24Network  

C. Copy the RF24Network folder to the current directory, and delete the rest  

    cd RF24Network  

D. Build the library  

    sudo make install
    cd examples_RPi  
    make  
    sudo ./helloworld_rx   OR   sudo ./helloworld_tx  
  

### Connection Info

Using pin 15/GPIO 22 for CE, pin 24/GPIO8 (CE0) for CSN

Can use either RPi CE0 or CE1 pins for radio CSN.
Choose any RPi output pin for radio CE pin.

**Constructor:**

    RF24 radio(RPI_V2_GPIO_P1_15,BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);
    or
    RF24 radio(RPI_V2_GPIO_P1_15,BCM2835_SPI_CS1, BCM2835_SPI_SPEED_8MHZ);
	
	RPi B+:
	RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);
	or
	RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_26, BCM2835_SPI_SPEED_8MHZ);

**Pins:**  

| PIN | NRF24L01 |    RPI     | RPi -P1 Connector |
|-----|----------|------------|-------------------|
|  1  |   GND    | rpi-gnd    |     (25)          |
|  2  |   VCC    | rpi-3v3    |     (17)          |
|  3  |   CE     | rpi-gpio22 |     (15)          |
|  4  |   CSN    | rpi-gpio8  |     (24)          |
|  5  |   SCK    | rpi-sckl   |     (23)          |
|  6  |   MOSI   | rpi-mosi   |     (19)          |
|  7  |   MISO   | rpi-miso   |     (21)          |
|  8  |   IRQ    |    -       |       -           |
  
  
See http://www.airspayce.com/mikem/bcm2835/index.html for BCM2835 class documentation.  
Note: The BCM library has been customized slightly to allow use of hardware CE pins not
in use for SPI, and to include a millis() function.  
   
****************
  
Based on the arduino lib from J. Coliz <maniacbug@ymail.com>.  
the library was berryfied by Purinda Gunasekara <purinda@gmail.com>.  
then forked from github stanleyseow/RF24 to https://github.com/jscrane/RF24-rpi  
Network lib also based on https://github.com/farconada/RF24Network

Currently optimized and aligned with Arduino fork of libraries by TMRh20:  
https://github.com/tmrh20/RF24/RPi and https://github.com/tmrh20/RF24Network/RPi  
Documentation: http://tmrh20.github.io
