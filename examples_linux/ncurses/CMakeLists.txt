# this example needs the ncurses package installed
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(example scanner_curses)

# make a target
add_executable(${example} ${example}.cpp)

# link the RF24 lib to the target. Notice we specify pthread as a linked lib here
target_link_libraries(${example} PUBLIC
    ${linked_libs}
    ${CURSES_LIBRARIES}
)
if("${LibPIGPIO}" STREQUAL "LibPIGPIO-NOTFOUND" OR DEFINED RF24_NO_INTERRUPT)
    target_compile_definitions(${example} PUBLIC RF24_NO_INTERRUPT)
endif()
