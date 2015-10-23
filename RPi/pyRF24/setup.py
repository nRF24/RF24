#!/usr/bin/env python

from distutils.core import setup, Extension
import sys

if sys.version_info >= (3,):
    BOOST_LIB = 'boost_python3'
else:
    BOOST_LIB = 'boost_python'

module_RF24 = Extension('RF24',
            libraries = ['rf24-bcm', BOOST_LIB],
            sources = ['pyRF24.cpp'])

setup(name='RF24',
    version='1.1',
    ext_modules=[module_RF24]
      )
