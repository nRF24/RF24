# Arduino
RF24 is fully compatible with Arduino boards.

See http://www.arduino.cc/en/Reference/Board and http://arduino.cc/en/Reference/SPI for more information

RF24 makes use of the standard hardware SPI pins (MISO, MOSI, SCK) and requires two additional pins, to control
the chip-select and chip-enable functions.

```cpp
RF24 radio(ce_pin, cs_pin);
```
These pins must be chosen and designated by the user and can use any
available pins.

## Alternate SPI Support

RF24 supports alternate SPI methods, in case the standard hardware SPI pins are otherwise unavailable.

### Software Driven SPI
Software driven SPI is provided by the [DigitalIO library](https://github.com/greiman/DigitalIO>).

Setup:
1. Install the digitalIO library
2. Open RF24_config.h in a text editor.
   Uncomment the line
   ```cpp
   #define SOFTSPI
   ```
   or add the build flag/option
   ```shell
   -DSOFTSPI
   ```
3. In your sketch, add
   ```cpp
   #include DigitalIO.h
   ```

@note Note: Pins are listed as follows and can be modified by editing the RF24_config.h file.
```cpp
#define SOFT_SPI_MISO_PIN 16
#define SOFT_SPI_MOSI_PIN 15
#define SOFT_SPI_SCK_PIN 14
```
Or add the build flag/option
```shell
-DSOFT_SPI_MISO_PIN=16 -DSOFT_SPI_MOSI_PIN=15 -DSOFT_SPI_SCK_PIN=14
```

### Alternate Hardware (UART) Driven  SPI
The Serial Port (UART) on Arduino can also function in SPI mode, and can double-buffer data, while the
default SPI hardware cannot.

The SPI_UART library is available at https://github.com/TMRh20/Sketches/tree/master/SPI_UART

Enabling:
1. Install the SPI_UART library
2. Edit RF24_config.h and uncomment
   ```cpp
   #define SPI_UART
   ```
3. In your sketch, add
   ```cpp
   #include <SPI_UART.h>
   ```

SPI_UART SPI Pin Connections:
| NRF |Arduino Uno Pin|
|----:|:--------------|
| MOSI| TX(0)         |
| MISO| RX(1)         |
| SCK | XCK(4)        |
| CE  | User Specified|
| CSN | User Specified|


@note SPI_UART on Mega boards requires soldering to an unused pin on the chip. <br>See
https://github.com/TMRh20/RF24/issues/24 for more information on SPI_UART.
