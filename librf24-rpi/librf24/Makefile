all: librf24

librf24: RF24.o gpio.o spi.o compatibility.o
	g++ -shared -Wl,-soname,librf24.so.1  -o librf24.so.1.0 compatibility.o gpio.o spi.o RF24.o

RF24.o: RF24.cpp
	g++ -Wall -fPIC -c RF24.cpp

gpio.o: gpio.cpp
	g++ -Wall -fPIC -c gpio.cpp

spi.o: spi.cpp
	g++ -Wall -fPIC -c spi.cpp

compatibility.o: compatibility.c
	gcc -Wall -fPIC -c compatibility.c

clean:
	rm -rf *o librf24.so.1.0

