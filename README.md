# Arduino & Raspberry Pi driver for nRF24L01(+) 2.4GHz Wireless Transceiver

Design Goals: 

* Maximally compliant with the intended operation of the chip
* Easy for beginners to use
* Consumed with a public interface that's similiar to other Arduino standard libraries
* Built against the standard SPI library. 
* Support popular platform

* Modifications to the RF24 library in this fork is backward compatible. A single
  enhancement which may cause issue, is code which relies on the driver to power down the
  radio, as a side effect. The radio is no longer powered down after each transmit. Rather,
  the application must take responsibility for power management. Normally this is
  achieved by use of powerDown and powerUp. If you wish to maximize power efficiency,
  you must call powerDown after transmit (write, startWrite).

Please refer to links :

* [Blog on setting up both Arduino UNO & Raspberry Pi] (http://arduino-for-beginners.blogspot.com/2013/02/setup-nordic-nrf24l01-rf-modules-to.html)
* [Documentation Main Page](http://maniacbug.github.com/RF24)
* [RF24 Class Documentation](http://maniacbug.github.com/RF24/classRF24.html)
* [Source Code](https://github.com/maniacbug/RF24)
* [Downloads](https://github.com/maniacbug/RF24/archives/master)
* [nRF24L01+ datasheet](http://www.nordicsemi.com/eng/nordic/download_resource/8765/2/27999719 )


# Optimized High Speed Arduino driver for nRF24L01 2.4GHz Wireless Transceiver
  
Design Goals: This library is designed to be...  
  
* More compliant with the manufacturer specified operation of the chip, while allowing advanced users
* to work outside the reccommended operation. 
* Utilize the capabilities of the radio to their full potential via Arduino
* More reliable and feature rich  
* Easy for beginners to use, with well documented examples and features 
* Consumed with a public interface that's similiar to other Arduino standard libraries  
* Built against the standard SPI library.   
  
April 2014: Official Release: Still some work to do, but most benefits have been realized
>>>>>>> 327f0609cf7b52b70accccc175b5809dd5074704

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
