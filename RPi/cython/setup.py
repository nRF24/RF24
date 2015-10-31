from distutils.core import setup, Extension
from Cython.Build import cythonize



setup(ext_modules = cythonize(Extension(
           "pyRF24",                                # the extension name
           sources=["pyRF24.pyx", "../../RF24.cpp", '../../utility/RPi/spi.cpp', '../../utility/RPi/bcm2835.c'], # the Cython source and
           language="c++",                        # generate and compile C++ code
           include_dirs = ["../../","utility/RPi/"],
      )))


