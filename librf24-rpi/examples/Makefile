all: scanner pingtest

pingtest: main_pingtest.cpp
	g++ -Wall -L.  -lrf24 main_pingtest.cpp -o pingtest

scanner: main_scanner.cpp
	g++ -Wall -L.  -lrf24 main_scanner.cpp -o scanner

clean:
	rm -rf scanner pingtest

