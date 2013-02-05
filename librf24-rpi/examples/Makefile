CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

all: scanner pingtest pongtest

pongtest: main_pongtest.cpp
	g++ ${CCFLAGS} -Wall -L.  -lrf24 main_pongtest.cpp -o pongtest

pingtest: main_pingtest.cpp
	g++ ${CCFLAGS} -Wall -L.  -lrf24 main_pingtest.cpp -o pingtest

scanner: main_scanner.cpp
	g++ ${CCFLAGS} -Wall -L.  -lrf24 main_scanner.cpp -o scanner

clean:
	rm -rf scanner pingtest

