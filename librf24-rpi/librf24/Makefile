
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

all: librf24

librf24: RF24.o gpio.o spi.o compatibility.o
	g++ -shared -Wl,-soname,librf24.so.1 ${CCFLAGS}  -o librf24.so.1.0 compatibility.o gpio.o spi.o RF24.o

RF24.o: RF24.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c RF24.cpp

gpio.o: gpio.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c gpio.cpp

spi.o: spi.cpp
	g++ -Wall -fPIC ${CCFLAGS} -c spi.cpp

compatibility.o: compatibility.c
	gcc -Wall -fPIC  ${CCFLAGS} -c compatibility.c

clean:
	rm -rf *o librf24.so.1.0

