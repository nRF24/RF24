# this example needs the ncurses package installed
find_package(Curses)
if(Curses_FOUND)
    message(STATUS "Including ncurses example")
    include_directories(${CURSES_INCLUDE_DIR})
else()
    message(STATUS "libncurses5-dev not found. Skipping ncurses example")
    return()
endif()

set(example scanner_curses)

# make a target
add_executable(${example} ${example}.cpp)

# link the RF24 lib to the target. Notice we specify pthread as a linked lib here
target_link_libraries(${example} PUBLIC
    ${linked_libs}
    ${CURSES_LIBRARIES}
)
