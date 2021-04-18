cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# In YOUR project, include RF24's CMakeLists.txt
# giving the path depending on where the library
# is cloned to in your project
include(../CMakeLists.txt)

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
    interruptConfigure
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
