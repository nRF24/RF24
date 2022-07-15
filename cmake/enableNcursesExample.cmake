find_package(Curses)
if(Curses_FOUND)
    include_directories(${CURSES_INCLUDE_DIR})
    option(BUILD_NCURSES_EXAMPLE
        "Enable/Disable building the ncurses example (requires libncurses5-dev installed)"
        ON
    )
else()
    message(STATUS "libncurses5-dev not found. Skipping ncurses example")
    option(BUILD_NCURSES_EXAMPLE
        "Enable/Disable building the ncurses example (requires libncurses5-dev installed)"
        OFF
    )
endif()
message(STATUS "BUILD_NCURSES_EXAMPLE set to ${BUILD_NCURSES_EXAMPLE}")
