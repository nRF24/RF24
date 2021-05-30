cmake_minimum_required(VERSION 3.12)
set(RF24_DRIVER "SPIDEV" CACHE STRING "Specify 'MRAA' or 'wiringPi' to compensate for the specialized supported driver")

# iterate over a list of examples by name
set(EXAMPLES_LIST
    gettingstarted
    acknowledgementPayloads
    manualAcknowledgements
    streamingData
    multiceiverDemo
    )

if("${RF24_DRIVER}" STREQUAL "MRAA" OR "${RF24_DRIVER}" STREQUAL "wiringPi")
    message("skipping interruptConfigure example - as it is incompatible with wiringPi and MRAA drivers")
else() # not using MRAA or wiringPi drivers
    list(APPEND EXAMPLES_LIST interruptConfigure)
endif()

project(RF24LogExamples)
add_compile_options(-Ofast -Wall)

foreach(example ${EXAMPLES_LIST})
    #make a target
    add_executable(${example} ${example}.cpp)

    # link the RF24 lib to the target
    # Notice that we specify pthread as a linked lib here instead passing the compiler a `-pthread` flag
    # target_link_libraries() command looks for the installed librf24.so
    if("${RF24_DRIVER}" STREQUAL "MRAA")
        target_link_libraries(${example} PUBLIC rf24 pthread mraa)
    elseif("${RF24_DRIVER}" STREQUAL "wiringPi")
        # wiringPi additionally needs to link to crypt and shm_open libraries
        target_link_libraries(${example} PUBLIC rf24 pthread wiringPi crypt rt)
    else() # not using MRAA or wiringPi drivers
        target_link_libraries(${example} PUBLIC rf24 pthread)
    endif()

endforeach()
