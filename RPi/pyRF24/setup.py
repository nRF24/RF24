#!/usr/bin/env python

from distutils.core import setup, Extension
import sys

BOOST_LIB = 'boost_python'
if sys.version_info >= (3,):
    BOOST_LIB = 'boost_python3'

module_RF24 = Extension('RF24',
            libraries = ['rf24-bcm', BOOST_LIB],
            sources = ['pyRF24.cpp'])

setup(name='RF24',
    version='1.0',
    ext_modules=[module_RF24]
      )
