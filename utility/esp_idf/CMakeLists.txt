## Include this file if you want to use the RF24 library
## in YOUR (ESP-IDF) project.

cmake_minimum_required(VERSION 3.16.0)

# Define the RF24 core library as a ESP-IDF component
idf_component_register(
    SRCS 
        "${CMAKE_CURRENT_LIST_DIR}/../../RF24.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/compatibility.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/gpio.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/spi.cpp"
    INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../"
    REQUIRES driver esp_timer # esp_driver_gpio esp_driver_spi
)
