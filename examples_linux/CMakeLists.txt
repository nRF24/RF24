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


set(linked_libs 
    ${RF24}
    pthread # Notice we specify pthread as a linked lib here
)

# append additional libs for linking to the executable
if("${RF24_DRIVER}" STREQUAL "MRAA")
    if(NOT "${LibMRAA}" STREQUAL "LibMRAA-NOTFOUND")
        message(STATUS "linking to ${LibMRAA}")
        list(APPEND linked_libs ${LibMRAA})
    else()
        message(FATAL "Lib ${RF24_DRIVER} not found.")
    endif()
elseif("${RF24_DRIVER}" STREQUAL "wiringPi")
    if(NOT "${LibWiringPi}" STREQUAL "LibWiringPi-NOTFOUND")
        message(STATUS "linking to ${LibWiringPi}")
        # wiringPi additionally needs to link to crypt and shm_open libraries
        list(APPEND linked_libs ${LibWiringPi} crypt rt)
    else()
        message(FATAL "Lib ${RF24_DRIVER} not found.")
    endif()
elseif(NOT "${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND" AND NOT DEFINED RF24_NO_INTERUPT)
    if(NOT "${RF24_DRIVER}" STREQUAL "pigpio")
        message(STATUS "linking to ${LibPIGPIO} for interrupt support")
    else()
        message(STATUS "linking to ${LibPIGPIO}")
    endif()
    # linking to pigpio requires pthread to be listed as last linked lib
    list(APPEND linked_libs ${LibPIGPIO} pthread)
else()
    message(STATUS "Disabling IRQ pin support")
endif()

foreach(example ${EXAMPLES_LIST})
    #make a target
    add_executable(${example} ${example}.cpp)
    
    # avoid including interrupt.h when pigpio is not available
    if("${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND" OR DEFINED RF24_NO_INTERRUPT)
        target_compile_definitions(${example} PUBLIC RF24_NO_INTERRUPT)
    endif()

    target_link_libraries(${example} PUBLIC ${linked_libs})
endforeach()

include(../cmake/enableNcursesExample.cmake)
if(BUILD_NCURSES_EXAMPLE)
    add_subdirectory(ncurses)
endif()
