# This file defines what we will call a utility library
# It is chosen based upon the driver the user specifies

# The idea here is to create a proxy library that is always linked to RF24
# The proxy library itself is linked the the specific, underlying driver library being used
add_library(rf24DriverUtility INTERFACE)
set (rf24_config_includes "")

if(NOT RF24_DRIVER)
    set(RF24_DRIVER SPIDEV)
endif()

# Use wiringPi
if ("${RF24_DRIVER}" STREQUAL  "wiringPi")
    add_subdirectory(wiringPi)
    target_link_libraries(rf24DriverUtility INTERFACE wiringPiDriver)
    set(rf24_config_includes ${CMAKE_SOURCE_DIR}/utility/wiringPi/includes.h)
# use RPi
elseif("${RF24_DRIVER}" STREQUAL "RPi")
    add_subdirectory(RPi)
    target_link_libraries(rf24DriverUtility INTERFACE RPiDriver)
    set(rf24_config_includes ${CMAKE_SOURCE_DIR}/utility/RPi/includes.h)
# use SPIDEV
elseif("${RF24_DRIVER}" STREQUAL "SPIDEV")
    add_subdirectory(SPIDEV)
    target_link_libraries(rf24DriverUtility INTERFACE SPIDEVDriver)
    set(rf24_config_includes ${CMAKE_SOURCE_DIR}/utility/SPIDEV/includes.h)
# use MRAA
elseif("${RF24_DRIVER}" STREQUAL "MRAA")
    add_subdirectory(MRAA)
    target_link_libraries(rf24DriverUtility INTERFACE MRAADriver)
    set(rf24_config_includes ${CMAKE_SOURCE_DIR}/utility/MRAA/includes.h)
# use LittleWire
elseif("${RF24_DRIVER}" STREQUAL "LittleWire")
    add_subdirectory(LittleWire)
    target_link_libraries(rf24DriverUtility INTERFACE LittleWireDriver)
    set(rf24_config_includes ${CMAKE_SOURCE_DIR}/utility/LittleWire/includes.h)
else()
    # No valid driver selected... this is bad
    message(FATAL_ERROR  "No valid driver selected! Please specify one of the following supported drivers (ie -DRF24_DRIVER=SPIDEV):\n\twiringPi\n\tRPi\n\tSPIDEV\n\tMRAA\n\tLittleWire")
endif()

# copy the includes file to the binary directory and add this path to the target
copy_includes(RF24 ${rf24_config_includes})
message("Using driver: ${RF24_DRIVER}")
