# # Include this file if you want to use the RF24 library
# # in YOUR (STM32Cube) project.
# # NOTE: This is preliminary support for CMake (which is not typically used in STM32Cube IDE)

cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_library(rf24 INTERFACE
    ../../RF24.cpp
    ${CMAKE_CURRENT_LIST_DIR}/RF24_arch_config.h
    ${CMAKE_CURRENT_LIST_DIR}/spi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gpio.cpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility.cpp
)

# STM32_ARCH option set in RF24/CMakeLists.txt
target_compile_definitions(rf24 PUBLIC -DSTM32 -D${STM32_ARCH})

# STM32CubeHalIncludes array/variable set in the project's CMakeLists.txt
target_include_directories(rf24 PRIVATE . ${STM32CubeHalIncludes} ../Core/Inc)

target_compile_options(rf24 PRIVATE -Ofast)

# STM32CubeHal library discovery in project's CMakeLists.txt
target_link_libraries(rf24 PRIVATE STM32CubeHal)
