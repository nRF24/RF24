# Linux Installation
Generic Linux devices are supported via SPIDEV, MRAA, RPi native via BCM2835, or using LittleWire.

@note The SPIDEV option should work with most Linux systems supporting spi userspace device. <br>

## Automated Install
**Designed & Tested on RPi** - Defaults to SPIDEV on devices supporting it

1. Install prerequisites if there are any (MRAA, LittleWire libraries, setup SPI device etc)
2. Download the install.sh file from http://tmrh20.github.io/RF24Installer/RPi/install.sh
   ```shell
   wget http://tmrh20.github.io/RF24Installer/RPi/install.sh
   ```
3. Make it executable
   ```shell
   chmod +x install.sh
   ```
4. Run it and choose your options
   ```shell
   ./install.sh
   ```
5. Run an example from one of the libraries
   ```shell
   cd rf24libs/RF24/examples_linux
   ```
   Edit the gettingstarted example, to set your pin configuration
   ```shell
   nano gettingstarted.cpp
   make
   sudo ./gettingstarted
   ```
## Manual Install
@warning Cross-compiling (& remotely installing) the RF24 library when using CMake won't work.
This also applies to the [python wrapper](md_docs_python_wrapper.html).

1. Install prerequisites if there are any (MRAA, LittleWire libraries, setup SPI device etc)
   If you intend to use CMake, then it mamy need to be installed (`sudo apt-get install cmake`).

   @note See the [MRAA](http://iotdk.intel.com/docs/master/mraa/index.html) documentation for
   more info on installing MRAA <br>
2. Make a directory to contain the RF24 and possibly RF24Network lib and enter it
   ```shell
   mkdir ~/rf24libs
   cd ~/rf24libs
   ```
3. Clone the [RF24 repo](https://github.com/nRF24/RF24)
   ```shell
   git clone https://github.com/nRF24/RF24.git RF24
   ```
4. Change to the new RF24 directory
   ```shell
   cd RF24
   ```
   If using CMake, you need to also create a build directory inside the RF24 directory and navigate to it.
   ```shell
   mkdir build
   cd build
   ```
5. Configure build environment using
   - If using CMake<br>
   ```shell
   cmake .. -D RF24_DRIVER=SPIDEV
   ```
   Instead of using `SPIDEV` driver (recommended), you can also specify the `RPi`, `wiringPi`,
   `MRAA`, or `LittleWire` as alternative drivers. If the `RF24_DRIVER` option is not specified,
   then it will be automatically configured based on the detected CPU or installed libraries
   (defaults to `SPIDEV` when auto-detection fails).
   - If not using CMake, run
   ```shell
   ./configure
   ```
   This script auto-detectes device and build environment.<br>
   For overriding auto-detections, use command-line switches, see
   ```shell
   ./configure --help
   ```
   for description.
6. Build and install the library
   ```shell
   make
   sudo make install
   ```
7. Build the examples <br>
   Make sure the pins used in the examples match the pins you used to connect the radio module
   ```shell
   nano examples_linux/gettingstarted.cpp
   ```
   or if in the CMake build directory
   ```shell
   nano ../examples_linux/gettingstarted.cpp
   ```
   and edit the pin numbers as directed in the [linux/RPi general documation](md_docs_rpi_general.html)

   - If using CMake, you need to clear the build directory you used to build & install the library
      <br> **It is VERY IMPORTANT that you only delete the files in the build directory.**
      <br> DO NOT DELETE THE FILES IN THE RF24 DIRECTORY!<br>
   ```shell
   rm -r ./*
   ```
      Now you are ready to build the examples.
   ```shell
   cmake ../examples_linux
   make
   ```
      If you are using the `MRAA` or `wiringPi` drivers, then you need to specify the `RF24_DRIVER`
      option again.
   ```shell
   cmake ../examples_linux -D RF24_DRIVER=wiringPi
   make
   ```
   - If not using CMake
   ```shell
   cd examples_linux
   make
   ```
8. Run an example file
   ```shell
   sudo ./gettingstarted
   ```

### Build using SPIDEV

1. Make sure that spi device support is enabled and /dev/spidev\<a\>.\<b\> is present
2. Manual Install using SPIDEV:
   ```shell
   ./configure --driver=SPIDEV
   make
   sudo make install
   ```
3. See the gettingstarted example for an example of pin configuration
