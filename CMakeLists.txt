cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(RF24_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# add the RF24 core library
add_library(RF24 RF24.h)

target_link_libraries(RF24_examples PUBLIC RF24)

# Add pico examples
add_subdirectory(examples_pico)

# Add Linux examples
#add_subdirectory(examples_linux)
