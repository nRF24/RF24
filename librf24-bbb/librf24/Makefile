#############################################################################
#
# Makefile for librf24 on Raspberry Pi
#
# License: GPL (General Public License)
# Author:  gnulnulf <arco@appeltaart.mine.nu>
# Date:    2013/02/07 (version 1.0)
#
# Description:
# ------------
# use make all and mak install to install the library
# You can change the install directory by editing the LIBDIR line
#
LIBDIR=/usr/local/lib
INCLUDEDIR=/usr/local/include
LIBNAME=librf24.so.1.0

# make all
all: librf24

# Make the library
librf24: RF24.o gpio.o spi.o compatibility.o
	g++ -shared -Wl,-soname,librf24.so.1 ${CCFLAGS}  -o ${LIBNAME} compatibility.o gpio.o spi.o RF24.o

# Library parts
RF24.o: RF24.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c RF24.cpp

gpio.o: gpio.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c gpio.cpp

spi.o: spi.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c spi.cpp

compatibility.o: compatibility.c
	gcc -Wall -fPIC  ${CCFLAGS} -c compatibility.c

# clear build files
clean:
	rm -rf *o ${LIBNAME}

# Install the library to LIBPATH
install:
	cp librf24.so.1.0 ${LIBDIR}/${LIBNAME}
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/librf24.so.1
	ln -sf ${LIBDIR}/${LIBNAME} ${LIBDIR}/librf24.so
	cp compatibility.h ${INCLUDEDIR}
	cp gpio.h ${INCLUDEDIR}
	cp nRF24L01.h ${INCLUDEDIR}
	cp RF24_config.h ${INCLUDEDIR}
	cp RF24.h ${INCLUDEDIR}
	cp spi.h ${INCLUDEDIR}
	ldconfig

