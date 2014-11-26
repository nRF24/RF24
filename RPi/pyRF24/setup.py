#!/usr/bin/env python

from distutils.core import setup, Extension

module_RF24 = Extension('RF24',
            libraries = ['rf24-bcm', 'boost_python'],
            sources = ['pyRF24.cpp'])

setup(name='RF24',
    version='1.0',
    ext_modules=[module_RF24]
      )
