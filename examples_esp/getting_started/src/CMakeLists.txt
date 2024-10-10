# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources}
    REQUIRES RF24
    # # for user projects (that don't belong in the RF24 repo), use the component registry
    # REQUIRES nRF24/RF24
)
