cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
# include parent folder (repo root) as a component library
list(APPEND EXTRA_COMPONENT_DIRS ../../)
# in user projects (external to RF24 repo), they should use `idf_component_register()` instead
project(getting_started)
