# This file defines what we will call a utility library
# It is chosen based upon the driver the user specifies

# The idea here is to create a proxy library that is always linked to RF24
# The proxy library itself is linked the the specific, underlying driver library being used
add_library(rf24DriverUtility INTERFACE)

# Use wiringPi
if ("${RF24_DRIVER}" STREQUAL  "wiringPi")
    add_subdirectory(wiringPi)
    target_link_libraries(rf24DriverUtility INTERFACE wiringPiDriver )
# use RPi
elseif("${RF24_DRIVER}" STREQUAL "RPi")
    add_subdirectory(RPi)
    target_link_libraries(rf24DriverUtility INTERFACE RPiDriver )
# use SPIDEV
elseif("${RF24_DRIVER}" STREQUAL "SPIDEV")
    add_subdirectory(SPIDEV)
    target_link_libraries(rf24DriverUtility INTERFACE SPIDEVDriver )
# use MRAA
elseif("${RF24_DRIVER}" STREQUAL "MRAA")
    add_subdirectory(MRAA)
    target_link_libraries(rf24DriverUtility INTERFACE MRAADriver )
# use LittleWire
elseif("${RF24_DRIVER}" STREQUAL "LittleWire")
    add_subdirectory(LittleWire)
    target_link_libraries(rf24DriverUtility INTERFACE LittleWireDriver )
else()
    # No driver selected... this is bad
    message(FATAL_ERROR  "No driver selected! Please rerun with driver selected.")
endif()

message("Using driver: ${RF24_DRIVER}")
