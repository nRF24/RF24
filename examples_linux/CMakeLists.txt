cmake_minimum_required(VERSION 3.12)

# iterate over a list of examples by name
set(EXAMPLES_LIST
    gettingstarted
    acknowledgementPayloads
    manualAcknowledgements
    streamingData
    multiceiverDemo
    interruptConfigure
    )

project(RF24LogExamples)
add_compile_options(-Ofast -Wall)

foreach(example ${EXAMPLES_LIST})
    #make a target
    add_executable(${example} ${example}.cpp)

    # link the RF24 lib to the target
    target_link_libraries(${example} PUBLIC rf24 pthread) # this command looks for the installed librf24.so
    # Notice that we specify pthread as a linked lib here instead passing the compiler a `-pthread` flag
endforeach()
