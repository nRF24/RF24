CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

all: scanner pingtest pingtest2

pingtest2: main_pingtest2.cpp
	g++ ${CCFLAGS} -Wall -L.  -lrf24 main_pingtest2.cpp -o pingtest2

pingtest: main_pingtest.cpp
	g++ ${CCFLAGS} -Wall -L.  -lrf24 main_pingtest.cpp -o pingtest

scanner: main_scanner.cpp
	g++ ${CCFLAGS} -Wall -L.  -lrf24 main_scanner.cpp -o scanner

clean:
	rm -rf scanner pingtest

