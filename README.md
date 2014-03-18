# Arduino driver for nRF24L01 2.4GHz Wireless Transceiver

Note: March 2014, this fork was just published and is still undergoing fine tuning.
The attached documentation is close but does NOT match the library.
See http://TMRh20.blogspot.com for usage information and updates. 
This readme will be updated once more is finalized.

Design Goals: This library is designed to be...

* Maximally compliant with the intended operation of the chip
* As efficient in operation as possible
* Easy for beginners to use
* Consumed with a public interface that's similiar to other Arduino standard libraries
* Built against the standard SPI library. 

Please refer to:

* [Documentation Main Page](http://maniacbug.github.com/RF24)
* [RF24 Class Documentation](http://maniacbug.github.com/RF24/classRF24.html)
* [Source Code](https://github.com/maniacbug/RF24)
* [Downloads](https://github.com/maniacbug/RF24/archives/master)
* [Chip Datasheet](http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf)

This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or
the SPI hardware will go into 'slave' mode.

