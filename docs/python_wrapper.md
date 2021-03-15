# Python Wrapper
By [mz-fuzzy](https://github.com/mz-fuzzy)

# Prerequisites

## RF24
The RF24 lib needs to be built in C++ & installed for the python wrapper to wrap it <br>
See [Linux Installation](md_docs_linux_install.html) and [Linux/RPi General](md_docs_rpi_general.html)

## Python2
```shell
sudo apt-get install python-dev libboost-python-dev python-setuptools python-rpi.gpio
```

## Python3
```shell
sudo apt-get install python3-dev libboost-python-dev python3-setuptools python3-rpi.gpio
```

# Installation:
1. For python3 in Raspbian, it's needed to manually link python boost library, like this:
   ```shell
   sudo ln -s $(ls /usr/lib/arm-linux-gnueabihf/libboost_python3-py3*.so | tail -1) /usr/lib/arm-linux-gnueabihf/libboost_python3.so
   ```
2. Build the library. From the rf24libs/RF24/pyRF24 directory:
   ```shell
   ./setup.py build
   ```
   or
   ```shell
   python3 setup.py build
   ```
@note Build takes several minutes on arm-based machines. Machines with RAM less than 1GB may need to increase amount of swap for build.

3. Install the library
   ```shell
   sudo ./setup.py install
   ```
   or
   ```shell
   sudo python3 setup.py install
   ```
   See the additional [Platform Support pages](pages.html) for information on connecting your hardware.

   See the included [*.py files in the "examples_linux" folder](examples.html) for usage information.

4. Running the Example:
   Edit the getting_started.py example to configure the appropriate pins per the [Linux/RPi General](md_docs_rpi_general.html) documentation.
   ```shell
   nano getting_started.py
   ```
   Configure another device, Arduino or RPi with the [getting_started.py example](examples_linux_2getting_started_8py-example.html)<br>
   Run the example
   ```shell
   sudo python getting_started.py
   ```
   or
   ```shell
   sudo python3 getting_started.py
   ```
