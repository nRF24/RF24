#############################################################################
#
# Makefile for librf24
#
# License: GPL (General Public License)
# Author:  Charles-Henri Hallard 
# Date:    2013/03/13 
#
# Description:
# ------------
# use make all and make install to install the library 
#

ifeq ($(wildcard Makefile.inc), )
$(error Configuration not found. Run ./configure first)
endif	

include Makefile.inc

# Objects to compile
OBJECTS=RF24.o
ifeq ($(DRIVER), MRAA)
OBJECTS+=spi.o gpio.o compatibility.o
else ifeq ($(DRIVER), RPi)
OBJECTS+=spi.o bcm2835.o interrupt.o
else ifeq ($(DRIVER), SPIDEV)
OBJECTS+=spi.o gpio.o compatibility.o
endif

# make all
# reinstall the library after each recompilation
all: $(LIBNAME)

# Make the library
$(LIBNAME): $(OBJECTS)
	@echo "[Linking]"
	${CC} ${SHARED_LINKER_FLAGS} ${CFLAGS} -o ${LIBNAME} $^

# Library parts
RF24.o: RF24.cpp	
	${CXX} -Wall -fPIC ${CFLAGS} -c $^

bcm2835.o: $(DRIVER_DIR)/bcm2835.c
	${CC} -Wall -fPIC ${CFLAGS} -c $^

spi.o: $(DRIVER_DIR)/spi.cpp
	${CXX} -Wall -fPIC ${CFLAGS} -c $^

compatibility.o: $(DRIVER_DIR)/compatibility.c
	${CC} -Wall -fPIC  ${CFLAGS} -c $(DRIVER_DIR)/compatibility.c

gpio.o: $(DRIVER_DIR)/gpio.cpp
	${CXX} -Wall -fPIC ${CFLAGS} -c $(DRIVER_DIR)/gpio.cpp

interrupt.o: $(DRIVER_DIR)/interrupt.c
	${CXX} -Wall -fPIC ${CFLAGS} -c $(DRIVER_DIR)/interrupt.c
	
# clear build files
clean:
	@echo "[Cleaning]"
	rm -rf *.o ${LIBNAME}.*

install: all install-libs install-headers
upload: all upload-libs upload-headers

# Install the library to LIBPATH
install-libs:
	@echo "[Installing Libs]"
	@if ( test ! -d $(PREFIX)/lib ) ; then mkdir -p $(PREFIX)/lib ; fi
	@install -m 0755 ${LIBNAME} ${LIB_DIR}
	@ln -sf ${LIB_DIR}/${LIBNAME} ${LIB_DIR}/${LIBNAME}.1
	@${LDCONFIG}

upload-libs:
	@echo "[Uploading Libs to ${REMOTE}]"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "mkdir -p ${REMOTE_LIB_DIR}"
	@scp -q -P ${REMOTE_PORT} ${LIBNAME} ${REMOTE}:/tmp
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "sudo install -m 0755 /tmp/${LIBNAME} ${REMOTE_LIB_DIR} && rm /tmp/${LIBNAME} && sudo ln -sf ${REMOTE_LIB_DIR}/${LIBNAME} ${REMOTE_LIB_DIR}/${LIBNAME}.1 && sudo ldconfig"

install-headers:
	@echo "[Installing Headers]"
	@mkdir -p ${HEADER_DIR}/${DRIVER_DIR}
	@install -m 0644 *.h ${HEADER_DIR}
	@install -m 0644 ${DRIVER_DIR}/*.h ${HEADER_DIR}/${DRIVER_DIR}
	@install -m 0644 ${ARCH_DIR}/*.h ${HEADER_DIR}/${ARCH_DIR}

upload-headers:
	@echo "[Uploading Headers to ${REMOTE}]"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "sudo mkdir -p ${REMOTE_HEADER_DIR}/${DRIVER_DIR}"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "mkdir -p /tmp/RF24 && rm -rf /tmp/RF24/*"
	@rsync -a --include="*.h" --include="*/" --exclude="*" -e "ssh -p ${REMOTE_PORT}" . ${REMOTE}:/tmp/RF24
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "sudo install -m 0644 /tmp/RF24/*.h ${REMOTE_HEADER_DIR}"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "sudo install -m 0644 /tmp/RF24/${DRIVER_DIR}/*.h ${REMOTE_HEADER_DIR}/${DRIVER_DIR}"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "sudo install -m 0644 /tmp/RF24/${ARCH_DIR}/*.h ${REMOTE_HEADER_DIR}/${ARCH_DIR}"
	@ssh -q -t -p ${REMOTE_PORT} ${REMOTE} "rm -rf /tmp/RF24"
