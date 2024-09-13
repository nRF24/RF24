cmake_minimum_required(VERSION 3.12)

# iterate over a list of examples by filename
set(EXAMPLES_LIST
    gettingstarted
    acknowledgementPayloads
    manualAcknowledgements
    streamingData
    multiceiverDemo
    scanner
    interruptConfigure
)

# generate a compilation database for static analysis by clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(RF24Examples CXX)
add_compile_options(-Ofast -Wall) # passing the compiler a `-pthread` flag doesn't work here

# detect the CPU make and type
include(../cmake/detectCPU.cmake) # sets the variable SOC accordingly

# auto-detect what driver to use
# auto-detect can be overridden using `cmake .. -D RF24_DRIVER=<supported driver>`
include(../cmake/AutoConfig_RF24_DRIVER.cmake)

find_library(RF24 rf24 REQUIRED)
message(STATUS "using RF24 library: ${RF24}")


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
elseif("${RF24_DRIVER}" STREQUAL "pigpio")
    if(NOT "${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND")
        message(STATUS "linking to ${LibPIGPIO}")
        # linking to pigpio requires pthread to be listed as last linked lib
        list(APPEND linked_libs ${LibPIGPIO} pthread)
    else()
        message(FATAL "Lib ${RF24_DRIVER} not found")
    endif()
endif()

foreach(example ${EXAMPLES_LIST})
    #make a target
    add_executable(${example} ${example}.cpp)

    target_link_libraries(${example} PUBLIC ${linked_libs})
endforeach()

add_subdirectory(ncurses)
