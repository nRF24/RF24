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
LIBDIR=/usr/local/lib
LIBNAME=librf24-bcm.so.1.0


# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

# make all
all: librf24-bcm

# Make the library
librf24-bcm: RF24.o bcm2835.o compatibility.o
	g++ -shared -Wl,-soname,librf24-bcm.so.1 ${CCFLAGS}  -o ${LIBNAME} compatibility.o bcm2835.o RF24.o

# Library parts
RF24.o: RF24.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c RF24.cpp

bcm2835.o: bcm2835.c
	gcc -Wall -fPIC ${CCFLAGS} -c bcm2835.c

compatibility.o: compatibility.c
	gcc -Wall -fPIC  ${CCFLAGS} -c compatibility.c

# clear build files
clean:
	rm -rf *o ${LIBNAME}

# Install the library to LIBPATH
install: 
	cp librf24-bcm.so.1.0 ${LIBDIR}/${LIBNAME}
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/librf24-bcm.so.1
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/librf24-bcm.so
	ldconfig

