cmake_minimum_required(VERSION 3.12)

# iterate over a list of examples by filename
set(EXAMPLES_LIST
    gettingstarted
    acknowledgementPayloads
    manualAcknowledgements
    streamingData
    multiceiverDemo
    scanner
)

project(RF24Examples CXX)
add_compile_options(-Ofast -Wall) # passing the compiler a `-pthread` flag doesn't work here

# detect the CPU make and type
include(../cmake/detectCPU.cmake) # sets the variable SOC accordingly

# auto-detect what driver to use
# auto-detect can be overriden using `cmake .. -D RF24_DRIVER=<supported driver>`
include(../cmake/AutoConfig_RF24_DRIVER.cmake)

find_library(RF24 rf24 REQUIRED)
message(STATUS "using RF24 library: ${RF24}")

# conditionally append "interruptConfigure" to the EXAMPLES_LIST
if("${RF24_DRIVER}" STREQUAL "MRAA" OR "${RF24_DRIVER}" STREQUAL "wiringPi" OR "${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND")
    message(STATUS "Skipping interruptConfigure.cpp example as it is incompatible with selected driver library")
else() # not using MRAA or wiringPi drivers (or pigpio lib was found)
    list(APPEND EXAMPLES_LIST interruptConfigure)
endif()

foreach(example ${EXAMPLES_LIST})
    #make a target
    add_executable(${example} ${example}.cpp)
    
    # avoid including interrupt.h when pigpio is not available
    if("${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND")
        target_compile_definitions(${example} PUBLIC RF24_NO_INTERRUPT)
    endif()

    # link the RF24 lib to the target. Notice we specify pthread as a linked lib here
    if("${RF24_DRIVER}" STREQUAL "MRAA")
        target_link_libraries(${example} PUBLIC ${RF24} pthread ${LibMRAA})
    elseif("${RF24_DRIVER}" STREQUAL "wiringPi")
        # wiringPi additionally needs to link to crypt and shm_open libraries
        target_link_libraries(${example} PUBLIC ${RF24} pthread ${LibWiringPi} crypt rt)
    elseif("${RF24_DRIVER}" STREQUAL "pigpio" OR NOT "${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND")
        # linking to pigpio requires pthread to be listed as last linked lib
        target_link_libraries(${example} PUBLIC ${RF24} ${LibPIGPIO} pthread)
    else() # not using MRAA or wiringPi drivers
        target_link_libraries(${example} PUBLIC ${RF24} pthread)
    endif()
endforeach()
