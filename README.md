# Optimized High Speed Arduino driver for nRF24L01 2.4GHz Wireless Transceiver
  
Design Goals: This library is designed to be...  
  
* More compliant with the manufacturer specified operation of the chip  
* More reliable and feature rich  
* Easy for beginners to use  
* Consumed with a public interface that's similiar to other Arduino standard libraries  
* Built against the standard SPI library.   
  
March 2014: Optimization begun  
April 2014: Optimization nearing completion    
* The library has been tweaked to allow full use of the FIFO buffers for maximum transfer speeds  
* Changes to read() functionality have increased reliability and response  
* Extended timeout periods have been added to aid in noisy or otherwise unreliable environments  
* Delays have been removed where possible to ensure maximum efficiency  
* Arduino Due fully supported with extended SPI functions
* More! See the links below and class documentation for more info.  
  
Please refer to:  
  
* [Documentation Main Page](http://tmrh20.github.io/)  
* [Class Reference]( http://tmrh20.github.io/RF24/classRF24.html)  
* [Source Code](https://github.com/tmrh20/RF24)  
* [Downloads](https://github.com/TMRh20/RF24/archive/master.zip)  
* [Chip Datasheet](http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf)  
  
This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or  
the SPI hardware will go into 'slave' mode.  

