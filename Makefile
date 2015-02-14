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
ARCH_DIR=arch

# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

# The default objects to compile
OBJECTS=RF24.o spi.o

# Detect the Raspberry Pi by the existence of the bcm_host.h file
# Allow users to override the use of BCM2835 driver and force use of SPIDEV by specifying " sudo make install -B RF24_SPIDEV=1 "
ifeq "$(RF24_SPIDEV)" "1"
BCMLOC=/opt/vc/include/bcm_host.none
else
BCMLOC=/opt/vc/include/bcm_host.h
endif

ifneq ("$(wildcard $(BCMLOC))","")
DRIVER_DIR=$(ARCH_DIR)/RPi
OBJECTS+=bcm2835.o	
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
	g++ -shared -Wl,-soname,$@.so.1 ${CCFLAGS} -o ${LIBNAME} $^
	
# Library parts
RF24.o: RF24.cpp	
	g++ -Wall -fPIC ${CCFLAGS} -c $^

bcm2835.o: $(DRIVER_DIR)/bcm2835.c
	gcc -Wall -fPIC ${CCFLAGS} -c $^

spi.o: $(DRIVER_DIR)/spi.cpp
	gcc -Wall -fPIC ${CCFLAGS} -c $^

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
