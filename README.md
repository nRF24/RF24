This is a fork from **http://tmrh20.github.io/RF24** which can be build as a static library for Atmel Studio 7.

Not all files are needed.

Just copy the following structure into a GCC Static Library project in AS7:
```
utility\
  ATXMega256D3\
    compatibility.c
    compatibility.h
    gpio.cpp
    gpio.h
    gpio_helper.c
    gpio_helper.h
    includes.h
    RF24_arch_config.h
    spi.cpp
    spi.h
nRF24L01.h
printf.h
RF24.cpp
RF24.h
RF24_config.h
```

Only ATXMega256D3 is supported right now!

** For further information please see http://tmrh20.github.io/RF24 for all documentation**
