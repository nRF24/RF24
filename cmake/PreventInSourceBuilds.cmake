#
# This function will prevent in-source builds
function(AssureOutOfSourceBuilds)
    # make sure the user doesn't play dirty with symlinks
    get_filename_component(src_dir "${CMAKE_SOURCE_DIR}" REALPATH)
    get_filename_component(bin_dir "${CMAKE_BINARY_DIR}" REALPATH)

    # disallow in-source builds
    if("${src_dir}" STREQUAL "${bin_dir}")
        message("######################################################")
        message("Warning: in-source builds are disabled")
        message("Please create a separate build directory and run cmake from there")
        message("######################################################")
        message(FATAL_ERROR "Quitting configuration")
    endif()
endfunction()

AssureOutOfSourceBuilds()
