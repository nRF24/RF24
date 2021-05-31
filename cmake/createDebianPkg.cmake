# This module will build a debian compatible package to install - handy for cross-compiling
if(NOT CMAKE_HOST_UNIX)
    message(FATAL "building a debian package requires a Debian compatible OS and dpkg-deb installed.")
endif()

# get target arch if not cross-compiling
if(NOT DEFINED TARGET_ARCH) # TARGET_ARCH is defined only in the toolchain_<ARCH_TYPE>.cmake files
    execute_process(COMMAND dpkg --print-architecture
        OUTPUT_VARIABLE TARGET_ARCH
        )
    string(STRIP "${TARGET_ARCH}" TARGET_ARCH)
endif()

# assemble a debian package filename from known info
set(DEB_PKG_NAME "lib${LibTargetName}-${RF24_DRIVER}_${${LibName}_VERSION_MAJOR}.${${LibName}_VERSION_MINOR}-${${LibName}_VERSION_PATCH}_${TARGET_ARCH}")
message(STATUS "ready to package: ${DEB_PKG_NAME}.deb")

# declare the package folder location
set(PKG_DIR ${CMAKE_BINARY_DIR}/${DEB_PKG_NAME})

# copy over templated control file while replacing variables within
configure_file(cmake/deb_pkg_control.in ${DEB_PKG_NAME}/DEBIAN/control)

# create a post-install & post-removal scripts to update linker
set(POST_SCRIPTS
    ${PKG_DIR}/DEBIAN/postrm
    ${PKG_DIR}/DEBIAN/postinst
    )
foreach(script ${POST_SCRIPTS})
    file(WRITE ${script} ldconfig)
    execute_process(COMMAND chmod +x ${script})
    execute_process(COMMAND chmod 775 ${script})
endforeach()

# alter install prefix to have library install to the directory that will become the package
set(CMAKE_INSTALL_PREFIX ${PKG_DIR}/usr/local)

# add install rule to run dpkg-deb (needs to run on a ext4 file system)
install(CODE "execute_process(COMMAND dpkg-deb --build --root-owner-group ${PKG_DIR} ${CMAKE_BINARY_DIR}/${DEB_PKG_NAME}.deb)")
