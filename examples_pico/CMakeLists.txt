
#[[ for each example, we have to perform the following
#make a target
add_executable(gettingStarted gettingStarted.cpp)

# link the necessary libs to the target
target_link_libraries(gettingStarted PUBLIC
    RF24
    pico_stdlib
    hardware_spi
    hardware_gpio
    )

# enable usb output, disable uart output
pico_enable_stdio_usb(gettingStarted 1)
pico_enable_stdio_uart(gettingStarted 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(gettingStarted)
]]

# iterate over a list of examples by name
set(EXAMPLES_LIST
    gettingStarted
    acknowledgementPayloads
    streamingData
    manualAcknowledgements
    multiceiverDemo
    )

foreach(example ${EXAMPLES_LIST})
    add_executable(${example} ${example}.cpp)

    target_link_libraries(${example} PUBLIC
        RF24
        pico_stdlib
        hardware_spi
        hardware_gpio
        )

    pico_enable_stdio_usb(${example} 1)
    pico_enable_stdio_uart(${example} 0)
    pico_add_extra_outputs(${example})
endforeach()