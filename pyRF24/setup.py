#!/usr/bin/env python

import os
import sys
# import distutils.core
import setuptools
import crossunixccompiler


def process_configparams():
    with open('../Makefile.inc') as f:
        config_lines = f.readlines()

    for line in config_lines:
        identifier, value = line.split('=', 1)
        os.environ[identifier] = value


if sys.version_info >= (3,):
    BOOST_LIB = 'boost_python3'
else:
    BOOST_LIB = 'boost_python'

#process_configparams()
crossunixccompiler.register()

# module_RF24 = distutils.core.Extension('RF24',
module_RF24 = setuptools.Extension('RF24',
                                       libraries=['rf24', BOOST_LIB],
                                       sources=['pyRF24.cpp']
                                       )

# distutils.core.setup(name='RF24',
setuptools.setup(name='RF24',
                     version='1.1',
                     ext_modules=[module_RF24]
                     )
