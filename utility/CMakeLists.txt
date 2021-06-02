# This file defines what we will call a utility driver
# It is chosen based upon the driver the user specifies
# or (if unspecified) based on supported 3rd party libs that are presently installed

# The idea here is to create a variable holding the name of a supported
# 3rd party library that that will be linked to the RF24 library
# This is passed to target_link_libraries() in top-level CMakeLists.txt
set(RF24_LINKED_DRIVER "")
set(RF24_DRIVER OFF CACHE STRING "override automatic configuration of RF24's utility driver.
    Specify 1 of the following supported drivers (ie -DRF24_DRIVER=SPIDEV):
    wiringPi
    RPi
    SPIDEV
    MRAA
    LittleWire"
    )

###########################
# detect pre-existing (locally installed) 3rd party libraries
###########################

# detect installed libraries despite what RF24_DRIVER is set to
# this is always done for cross-compiling purposes
find_library(LibMRAA mraa)
find_library(LibWiringPi wiringPi)
find_library(LibLittleWire littlewire-spi)
execute_process(COMMAND ls /dev/spidev*
    OUTPUT_VARIABLE SPIDEV_EXISTS
    ERROR_VARIABLE CHECK_SPIDEV_ERROR
    )

include(../cmake/detectCPU.cmake) # sets the variable SOC accordingly

if(${RF24_DRIVER} STREQUAL "OFF") # invokes automatic configuration
    if("${SOC}" STREQUAL "BCM2708" OR "${SOC}" STREQUAL "BCM2709" OR "${SOC}" STREQUAL "BCM2835")
        set(RF24_DRIVER RPi CACHE STRING "using folder /utility/RPi" FORCE)
    elseif(NOT ${LibMRAA} STREQUAL "LibMRAA-NOTFOUND")
        set(RF24_DRIVER MRAA CACHE STRING "using folder /utility/MRAA" FORCE)
    elseif(NOT ${LibWiringPi} STREQUAL "LibWiringPi-NOTFOUND")
        set(RF24_DRIVER wiringPi CACHE STRING "using folder /utility/wiringPi" FORCE)
    elseif(NOT ${LibLittleWire} STREQUAL "LibLittleWire-NOTFOUND")
        set(RF24_DRIVER LittleWire CACHE STRING "using folder /utility/LittleWire" FORCE)
    elseif(SPIDEV_EXISTS) # should be a list if SPI is enabled on RPi
        set(RF24_DRIVER SPIDEV CACHE STRING "using folder /utility/SPIDEV" FORCE)
    endif()
endif()

###########################
### declare the appropriate sources and install rules based on driver selected
###########################
if ("${RF24_DRIVER}" STREQUAL  "wiringPi") # Use wiringPi
    set(RF24_LINKED_DRIVER ${LibWiringPi} PARENT_SCOPE)
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
    if(CHECK_SPIDEV_ERROR)
        message(WARNING "Detecting /dev/spidev* failed - continuing anyway. Please make sure SPI is enabled.")
    endif()
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
    set(RF24_LINKED_DRIVER ${LibMRAA} PARENT_SCOPE)
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
    set(RF24_LINKED_DRIVER ${LibLittleWire} PARENT_SCOPE)
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
else() # No valid/supported driver selected nor detected... this is vital
    message(FATAL_ERROR "No valid/supported driver selected or auto-detection failed to resolve one.
        Please specify 1 of the following supported drivers (ie `-D RF24_DRIVER=SPIDEV`):
        \twiringPi
        \tRPi
        \tSPIDEV
        \tMRAA
        \tLittleWire"
        )
endif()

# copy the includes file to the project source directory's utility folder
copy_includes(${CMAKE_SOURCE_DIR}/utility/${RF24_DRIVER}/includes.h)
message(STATUS "Using driver: ${RF24_DRIVER}")
