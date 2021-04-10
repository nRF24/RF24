cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(gettingStarted C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# add the RF24 core library
add_library(RF24 INTERFACE)
target_sources(RF24 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/RF24.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/rp2/gpio.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility/rp2/spi.cpp
    )

set_target_properties(RF24 PROPERTIES LINKER_LANGUAGE CXX)

# Add pico examples
add_subdirectory(examples_pico)

# Add Linux examples
#add_subdirectory(examples_linux)
