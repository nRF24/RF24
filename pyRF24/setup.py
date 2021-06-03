#!/usr/bin/env python

import os
import sys
import setuptools
import crossunixccompiler

version = ""


def process_configparams():
    version = ""  # using python keyword `global` is bad practice
    cflags = os.getenv("CFLAGS", "")
    symlink_directory = ""
    # check for possible linker flags  set via CFLAGS environment varible
    for flag in cflags.split("-"):
        if flag.startswith("L"):
            symlink_directory = flag[1:].strip() + (" " if len(symlink_directory) else "")

    # NOTE current repo directory structure requires the use of
    # `python3 setup.py build` and `python3 setup.py install`
    # where `pip3 install ./pyRF24` copies pyRF24 directory to
    # `tmp` folder that doesn't have the needed `../Makefile.inc`
    # NOTE can't access "../Makefile.inc" from working dir because
    # it's relative. Brute force absolute path dynamically.
    rf24_git_dir = os.path.split(os.path.abspath(os.getcwd()))[0]
    try:  # get compiler options from the generated Makefile.inc
        with open(os.path.join(rf24_git_dir, "Makefile.inc"), "r") as f:
            for line in f.read().splitlines():
                identifier, value = line.split('=', 1)
                if identifier == "CPUFLAGS":
                    # this is never reached as CPUFLAGS var is concatenated into CFLAGS var.
                    # however the CFLAGS var may conditionally contain "-lwiringPi"
                    cflags += " " + value
                elif identifier == "HEADER_DIR":
                    cflags += " -I" + os.path.dirname(value)
                elif identifier == "LIB_DIR":
                    symlink_directory += value
                    cflags += " -L" + value
                elif identifier == "LIB_VERSION":
                    version = value
                elif identifier in ("CC", "CXX"):
                    os.environ[identifier] = value

    except FileNotFoundError:  # assuming lib was built & installed with CMake

        # get LIB_VERSION from library.properties file for Arduino IDE
        with open(os.path.join(rf24_git_dir, "library.properties"), "r") as f:
            for line in f.read().splitlines():
                if line.startswith("version"):
                    version = line.split("=")[1]

        # add default values for compilation
        # NOTE for cross-compilation purposes, these values are best left to be
        #   set by the user with the CFLAGS environment variable
        # cflags += "-Ofast -Wall -pthread"  # default flags agnostic to GNU compiler
        # cflags += " -I/usr/local/include/RF24"  # default HEADER_DIR
        # cflags += " -L/usr/local/lib"  # default LIB_DIR

        compilers = (os.getenv("CC", ""), os.getenv("CXX", ""))
        # use default compilers if not specified with environment variables
        os.environ["CC"] = "/usr/bin/cc" if not len(compilers[0]) else compilers[0]
        os.environ["CXX"] = "/usr/bin/c++" if not len(compilers[1]) else compilers[1]

    finally:
        # check C++ RF24 lib is installed
        if not symlink_directory:
            print("install location of librf24.so isn't explicit; trying default location.")
            symlink_directory = "/usr/local/lib"
        for symlink_loc in symlink_directory.split():
            try:
                with open(symlink_directory + "/librf24.so", "r+b") as f:
                    print("librf24.so found at", symlink_loc)
                break
            except FileNotFoundError:
                raise FileNotFoundError("RF24 library is not installed. "
                                        "{}}/librf24.so does not exist.".format(
                                            symlink_loc
                                        ))

    os.environ["CFLAGS"] = cflags
    return version


if sys.version_info >= (3,):
    BOOST_LIB = "boost_python3"
else:
    BOOST_LIB = "boost_python"

version = process_configparams()
crossunixccompiler.register()

module_RF24 = setuptools.Extension("RF24",
                                   libraries=["rf24", BOOST_LIB],
                                   sources=["pyRF24.cpp"])

setuptools.setup(name="RF24",
                 version=version,
                 ext_modules=[module_RF24])
