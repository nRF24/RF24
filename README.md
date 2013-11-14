# Arduino driver for nRF24L01 2.4GHz Wireless Transceiver

Design Goals: This library is designed to be...

* Maximally compliant with the intended operation of the chip
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

### Some notes about the SI24R01 "power enhanced version 2.4G wireless module"

The SI24R01 chip on these modules is apparently a Chinese clone of the NRF24L01+. Sometimes, when you buy an nRF24L01+ module (particularly on eBay), you will actually get an SI24R01 module instead. Below is some slightly cleaned up information found about this chip on a [Chinese reseller site](http://www.wayengineer.com/index.php?main_page=product_info&products_id=3442).

> SI24R01 and NRF24L01 are completely compatible (SPI register, definition timing, the state diagram), which can communicate with each other, support NRF24L01+ all communication functions.

> 1: 7dBm output power
> SI24R1 default mode output power is 2~3dBm, if you want to output 7dBm, the register address 0x06 (RF_SETUP) the lowest register write 1 (NRF24L01+ without the use of the bit, the default is 0), namely 0x06 register a minimum of four to 1111

Translation: you can actually broadcast at up to 7dBm with this module if you set bit 0 in RF_SETUP to 1. For the nRF24L01+, this bit is marked as obsolete/don't care, so it shouldn't hurt to set it.

> 2: SI24R1 emission problem
> Launch operation mode of SI24R1 and NRF24L01+ exactly the same, cause problems: if the register is powerdown mode operation, higher CE to at least 2ms, because the powerdown model of crystal does not work, crystal is from close to emission data need about 2ms. If the standbyI mode to drop-down CE high, that is not problem, CE only needs a pulse of 10us, because under the mode of standbyI crystal is the work (current is very small, only dozen microamperes)

Translation: the transition from power-down to standby-I mode will take longer at about 2 ms on these modules, as opposed to 1.5 ms on the nRF24L01+.
