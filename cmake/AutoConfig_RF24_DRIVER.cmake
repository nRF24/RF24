set(RF24_LINKED_DRIVER "")
set(RF24_DRIVER "UNKNOWN" CACHE STRING "override automatic configuration of RF24's utility driver.
    Specify 1 of the following supported drivers (ie -DRF24_DRIVER=SPIDEV):
    wiringPi
    RPi
    SPIDEV
    MRAA
    LittleWire
    pigpio"
)

###########################
# detect pre-existing (locally installed) 3rd party libraries
###########################

# detect installed libraries despite what RF24_DRIVER is set to
# this is always done for cross-compiling purposes
find_library(LibMRAA mraa)
find_library(LibWiringPi wiringPi)
find_library(LibLittleWire littlewire-spi)
find_library(LibPIGPIO pigpio)
if(EXISTS /dev/spidev0.0)
    set(SPIDEV_EXISTS TRUE)
else()
    set(SPIDEV_EXISTS FALSE)
endif()


if(${RF24_DRIVER} STREQUAL "UNKNOWN") # invokes automatic configuration
    if("${SOC}" STREQUAL "BCM2708" OR "${SOC}" STREQUAL "BCM2709" OR "${SOC}" STREQUAL "BCM2835")
        set(RF24_DRIVER RPi CACHE STRING "using folder /utility/RPi" FORCE)
    elseif(NOT "${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND")
        message(STATUS "Found pigpio library: ${LibPIGPIO}")
        set(RF24_DRIVER pigpio CACHE STRING "using folder /utility/pigpio" FORCE)
    elseif(NOT "${LibWiringPi}" STREQUAL "LibWiringPi-NOTFOUND")
        message(STATUS "Found wiringPi library: ${LibWiringPi}")
        set(RF24_DRIVER wiringPi CACHE STRING "using folder /utility/wiringPi" FORCE)
    elseif(NOT "${LibLittleWire}" STREQUAL "LibLittleWire-NOTFOUND")
        message(STATUS "Found LittleWire library: ${LibLittleWire}")
        set(RF24_DRIVER LittleWire CACHE STRING "using folder /utility/LittleWire" FORCE)
    elseif(NOT "${LibMRAA}" STREQUAL "LibMRAA-NOTFOUND")
        message(STATUS "Found MRAA library: ${LibMRAA}")
        set(RF24_DRIVER MRAA CACHE STRING "using folder /utility/MRAA" FORCE)
    elseif(SPIDEV_EXISTS) # should be a non-empty string if SPI is enabled
        message(STATUS "detected that SPIDEV is enabled: ${SPIDEV_EXISTS}")
        set(RF24_DRIVER SPIDEV CACHE STRING "using folder /utility/SPIDEV" FORCE)
    endif()
endif()

# override the auto-detect if RF24_DRIVER is defined in an env var
if(DEFINED ENV{RF24_DRIVER})
    message(STATUS "RF24_DRIVER (set from env var) = $ENV{RF24_DRIVER}")
    set(RF24_DRIVER $ENV{RF24_DRIVER} CACHE STRING "" FORCE)
endif()

message(STATUS "Using driver: ${RF24_DRIVER}")
