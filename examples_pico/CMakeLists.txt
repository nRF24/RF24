add_executable(RF24_examples
    gettingStarted.cpp
    )

target_link_libraries(RF24_examples PUBLIC
    RF24
    pico_stdlib
    hardware_spi
    hardware_gpio
    )

# enable usb output, disable uart output
pico_enable_stdio_usb(RF24_examples 1)
pico_enable_stdio_uart(RF24_examples 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(RF24_examples)
