# Optimized High Speed Arduino driver for nRF24L01 2.4GHz Wireless Transceiver

Note: March 2014, this fork was just published and is still undergoing fine tuning. 

Class documenation is now available at http://tmrh20.github.io/RF24/class_r_f24.html

See http://TMRh20.blogspot.com for an overview of the new functionality.

Design Goals: This library is designed to be...

* More compliat with the manufacturer specified operation of the chip
* Utilize the capabilities of the radio to their full potential via Arduino 
* More reliable and feature rich
* Easy for beginners to use
* Consumed with a public interface that's similiar to other Arduino standard libraries
* Built against the standard SPI library. 

Please refer to:

* [Documentation Main Page](http://tmrh20.github.io/)
* [Class Reference]( http://tmrh20.github.io/RF24/class_r_f24.html)
* [Source Code](https://github.com/tmrh20/RF24)
* [Downloads](https://github.com/tmrh20/RF24/archives/master)
* [Chip Datasheet](http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf)

This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or
the SPI hardware will go into 'slave' mode.

