# This file defines what we will call a utility driver
# It is chosen based upon the driver the user specifies
# or (if unspecified) based on supported 3rd party libs that are presently installed

# The idea here is to create a variable holding the name of a supported
# 3rd party library that that will be linked to the RF24 library
# This is passed to target_link_libraries() in top-level CMakeLists.txt
set(RF24_LINKED_DRIVER "")
option(RF24_DRIVER
    "override automatic configuration of RF24's utility driver.
    Specify 1 of the following supported drivers (ie -DRF24_DRIVER=SPIDEV):
    \n\twiringPi\n\tRPi\n\tSPIDEV\n\tMRAA\n\tLittleWire"
    OFF
    )

###########################
# detect pre-existing (locally installed) 3rd party libraries
###########################
include(../cmake/detectCPU.cmake) # sets the variable SOC accordingly

if(${RF24_DRIVER} STREQUAL "OFF") # invokes automatic configuration
    find_library(LibMRAA mraa)
    find_library(LibWiringPi wiringPi)
    find_library(LibLittleWire littlewire-spi)

    if("${SOC}" STREQUAL "BCM2708" OR "${SOC}" STREQUAL "BCM2709" OR "${SOC}" STREQUAL "BCM2835")
        set(RF24_DRIVER RPi)
    elseif(NOT ${LibMRAA} STREQUAL "LibMRAA-NOTFOUND")
        set(RF24_DRIVER MRAA)
    elseif(NOT ${LibWiringPi} STREQUAL "LibWiringPi-NOTFOUND")
        set(RF24_DRIVER wiringPi)
    elseif(NOT ${LibLittleWire} STREQUAL "LibLittleWire-NOTFOUND")
        set(RF24_DRIVER LittleWire)
    else()
        set(RF24_DRIVER SPIDEV)
    endif()
endif()

###########################
### declare the appropriate sources and install rules based on driver selected
###########################
if ("${RF24_DRIVER}" STREQUAL  "wiringPi") # Use wiringPi
    set(RF24_LINKED_DRIVER wiringPi PARENT_SCOPE)
    add_compile_options(-pthread)
    set(RF24_DRIVER_SOURCES
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/spi.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/RF24_arch_config.h
        PARENT_SCOPE
        )
    install(FILES
            ${RF24_DRIVER}/includes.h
            ${RF24_DRIVER}/spi.h
            ${RF24_DRIVER}/RF24_arch_config.h
        DESTINATION include/RF24/utility/${RF24_DRIVER}
        )
elseif("${RF24_DRIVER}" STREQUAL "RPi") # use RPi
    set(RF24_DRIVER_SOURCES
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/bcm2835.c
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/spi.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/compatibility.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/RF24_arch_config.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/interrupt.cpp
        PARENT_SCOPE
        )
    install(FILES
            ${RF24_DRIVER}/includes.h
            ${RF24_DRIVER}/bcm2835.h
            ${RF24_DRIVER}/spi.h
            ${RF24_DRIVER}/compatibility.h
            ${RF24_DRIVER}/RF24_arch_config.h
            ${RF24_DRIVER}/interrupt.h
        DESTINATION include/RF24/utility/${RF24_DRIVER}
        )
elseif("${RF24_DRIVER}" STREQUAL "SPIDEV") # use SPIDEV
    set(RF24_DRIVER_SOURCES
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/gpio.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/spi.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/compatibility.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/RF24_arch_config.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/interrupt.cpp
        PARENT_SCOPE
        )
    install(FILES
            ${RF24_DRIVER}/includes.h
            ${RF24_DRIVER}/gpio.h
            ${RF24_DRIVER}/spi.h
            ${RF24_DRIVER}/compatibility.h
            ${RF24_DRIVER}/RF24_arch_config.h
            ${RF24_DRIVER}/interrupt.h
        DESTINATION include/RF24/utility/${RF24_DRIVER}
        )
elseif("${RF24_DRIVER}" STREQUAL "MRAA") # use MRAA
    set(RF24_LINKED_DRIVER mraa PARENT_SCOPE)
    set(RF24_DRIVER_SOURCES
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/gpio.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/spi.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/compatibility.cpp
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/RF24_arch_config.h
        PARENT_SCOPE
        )
    install(FILES
            ${RF24_DRIVER}/includes.h
            ${RF24_DRIVER}/gpio.h
            ${RF24_DRIVER}/spi.h
            ${RF24_DRIVER}/compatibility.h
            ${RF24_DRIVER}/RF24_arch_config.h
        DESTINATION include/RF24/utility/${RF24_DRIVER}
        )
elseif("${RF24_DRIVER}" STREQUAL "LittleWire") # use LittleWire
    set(RF24_LINKED_DRIVER littlewire-spi PARENT_SCOPE)
    set(RF24_DRIVER_SOURCES
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h
        ${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/RF24_arch_config.h
        PARENT_SCOPE
        )
    install(FILES
            ${RF24_DRIVER}/includes.h
            ${RF24_DRIVER}/RF24_arch_config.h
        DESTINATION include/RF24/utility/${RF24_DRIVER}
        )
else() # No valid/supported driver selected... this is bad
    message(FATAL_ERROR "No valid/supported driver selected! "
        "Please specify 1 of the following supported drivers (ie -DRF24_DRIVER=SPIDEV):"
        "\n\twiringPi\n\tRPi\n\tSPIDEV\n\tMRAA\n\tLittleWire"
    )
endif()

# copy the includes file to the project source directory's utility folder
copy_includes(${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h)
message(STATUS "Using driver: ${RF24_DRIVER}")
