## Include this file if you want to use the RF24 library
## in YOUR (ESP-IDF) project.
## See examples_esp/CMakeLists.txt to see how it could be done

cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Define the RF24 core library
add_library(RF24 STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../../RF24.cpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spi.cpp
)

target_include_directories(RF24 PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../
)

# REQUIRES esp_driver_gpio
# REQUIRES esp_driver_spi
