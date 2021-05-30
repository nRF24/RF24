#!/usr/bin/env python

import os
import sys
import setuptools
from . import crossunixccompiler

version = ""


def process_configparams():
    version = ""  # using python keyword `global` is bad practice
    cflags = os.getenv("CFLAGS", "")

    # NOTE current repo directory structure requires the use of
    # `python3 setup.py build` and `python3 setup.py install`
    # where `pip3 install ./pyRF24` copies pyRF24 directory to
    # `tmp` folder that doesn't have the needed `../Makefile.inc`
    # NOTE can't access "../Makefile.inc" from working dir because
    # it's relative. Brute force absolute path dynamically.
    rf24_git_dir = os.path.split(os.path.abspath(os.getcwd()))[0]
    try:  # get compiler options from the generated Makefile.inc
        symlink_directory = ""
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
                    symlink_directory = value
                    cflags += " -L" + value
                elif identifier == "LIB_VERSION":
                    version = value
                elif identifier in ("CC", "CXX"):
                    os.environ[identifier] = value

        # check C++ RF24 lib is installed
        try:
            with open(symlink_directory + "/librf24.so", "r+b") as f:
                pass
        except FileNotFoundError:
            raise FileNotFoundError("RF24 library is not installed. "
                                    "{}}/librf24.so does not exist.".format(
                                        symlink_directory
                                    ))

    except FileNotFoundError:  # assuming lib was built & installed with CMake
        # the following algorithm does not work for cross-compilation.

        # verify the C++ RF24 lib is installed
        try:
            with open("/usr/local/lib/librf24.so", "r+b"):
                pass
        except FileNotFoundError:
            raise FileNotFoundError("RF24 library is not installed. "
                                    "/usr/local/lib/librf24.so does not exist.")

        # get LIB_VERSION from library.properties file for Arduino IDE
        with open(os.path.join(rf24_git_dir, "library.properties"), "r") as f:
            for line in f.read().splitlines():
                if line.startswith("version"):
                    version = line.split("=")[1]
        # add default values for compilation
        # cflags += "-Ofast -Wall -pthread"  # default flags agnostic to GNU compiler
        cflags += " -I/usr/local/include/RF24"  # default HEADER_DIR
        cflags += " -L/usr/local/lib"  # default LIB_DIR
        os.environ["CC"] = "/usr/bin/cc"  # default C compiler
        os.environ["CXX"] = "/usr/bin/c++"  # default C++ compiler

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
