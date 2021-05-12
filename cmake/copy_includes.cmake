# Copies an includes file from one of the utility drivers and then adds it to target
#
# target - cmake target that has this file added in its target_include_directories
# source - path to source file for the original includes
function (copy_includes source)
    execute_process(COMMAND cp ${source} ${CMAKE_SOURCE_DIR}/utility/includes.h)
endfunction()