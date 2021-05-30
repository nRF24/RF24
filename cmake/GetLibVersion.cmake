# Make version vars based on the current version from git
execute_process(COMMAND awk -F "=" "/version/ {print $2}" ${CMAKE_SOURCE_DIR}/library.properties
    OUTPUT_VARIABLE VERSION
    )

#parse the version information into pieces.
string(REGEX REPLACE "^([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")

# this is the library version
set(${LibTargetName}_VERSION_MAJOR ${VERSION_MAJOR})
set(${LibTargetName}_VERSION_MINOR ${VERSION_MINOR})
set(${LibTargetName}_VERSION_PATCH ${VERSION_PATCH})
set(${LibTargetName}_VERSION_STRING ${${LibTargetName}_VERSION_MAJOR}.${${LibTargetName}_VERSION_MINOR}.${${LibTargetName}_VERSION_PATCH})

message(STATUS "RF24 library version: ${${LibTargetName}_VERSION_STRING}")
