#############################################################################
#
# Makefile for librf24-bcm on Raspberry Pi
#
# License: GPL (General Public License)
# Author:  Charles-Henri Hallard 
# Date:    2013/03/13 
#
# Description:
# ------------
# use make all and mak install to install the library 
# You can change the install directory by editing the LIBDIR line
#
PREFIX=/usr/local

# Library parameters
# where to put the lib
LIBDIR=$(PREFIX)/lib
# lib name 
LIB=librf24-bcm
# shared library name
LIBNAME=$(LIB).so.1.0

# Where to put the header files
HEADER_DIR=${PREFIX}/include/RF24

# The base location of support files for different devices
ARCH_DIR=utility

# The default objects to compile
OBJECTS=RF24.o spi.o

SHARED_LINKER_FLAGS=-shared -Wl,-soname,$@.so.1



# Detect the Raspberry Pi from cpuinfo
# Allow users to override the use of BCM2835 driver and force use of SPIDEV by specifying " sudo make install -B RF24_SPIDEV=1 "
ifeq "$(RF24_SPIDEV)" "1"
RPI=0
else
#Count the matches for BCM2708 or BCM2709 in cpuinfo
RPI=$(shell cat /proc/cpuinfo | grep Hardware | grep -c BCM2708)
  ifneq "${RPI}" "1"
  RPI=$(shell cat /proc/cpuinfo | grep Hardware | grep -c BCM2709)
  endif
endif

ifeq "$(RF24_MRAA)" "1"
SHARED_LINKER_FLAGS+=-lmraa 
DRIVER_DIR=$(ARCH_DIR)/MRAA
OBJECTS+=gpio.o compatibility.o

else ifeq "$(RPI)" "1"
DRIVER_DIR=$(ARCH_DIR)/RPi
OBJECTS+=bcm2835.o	
# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

else
DRIVER_DIR=$(ARCH_DIR)/BBB
OBJECTS+=gpio.o compatibility.o
endif


# make all
# reinstall the library after each recompilation
all: test librf24-bcm

test:
	cp ${DRIVER_DIR}/includes.h $(ARCH_DIR)/includes.h
# Make the library
librf24-bcm: $(OBJECTS)
	g++ ${SHARED_LINKER_FLAGS} ${CCFLAGS} -o ${LIBNAME} $^
	
# Library parts
RF24.o: RF24.cpp	
	g++ -Wall -fPIC ${CCFLAGS} -c $^

bcm2835.o: $(DRIVER_DIR)/bcm2835.c
	gcc -Wall -fPIC ${CCFLAGS} -c $^

spi.o: $(DRIVER_DIR)/spi.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c $^

compatibility.o: $(DRIVER_DIR)/compatibility.c
	gcc -Wall -fPIC  ${CCFLAGS} -c $(DRIVER_DIR)/compatibility.c

gpio.o: $(DRIVER_DIR)/gpio.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c $(DRIVER_DIR)/gpio.cpp
	
# clear build files
clean:
	rm -rf *.o ${LIB}.*

install: all install-libs install-headers

# Install the library to LIBPATH
install-libs: 
	@echo "[Installing Libs]"
	@if ( test ! -d $(PREFIX)/lib ) ; then mkdir -p $(PREFIX)/lib ; fi
	@install -m 0755 ${LIBNAME} ${LIBDIR}
	@ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/${LIB}.so.1
	@ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/${LIB}.so
	@ldconfig

install-headers:
	@echo "[Installing Headers]"
	@if ( test ! -d ${HEADER_DIR} ) ; then mkdir -p ${HEADER_DIR} ; fi
	@install -m 0644 *.h ${HEADER_DIR}
	@if ( test ! -d ${HEADER_DIR}/${DRIVER_DIR} ) ; then mkdir -p ${HEADER_DIR}/${DRIVER_DIR} ; fi
	@install -m 0644 ${DRIVER_DIR}/*.h ${HEADER_DIR}/${DRIVER_DIR}
	@install -m 0644 ${ARCH_DIR}/*.h ${HEADER_DIR}/${ARCH_DIR}
