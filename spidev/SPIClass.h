// SPIClass.h
// 
// Generic linux SPI using ioctl
// 
// https://www.kernel.org/doc/Documentation/spi/spidev
// http://armbedded.eu/node/318
//
// Author: Chris Campbell (iforce2d)
//

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

static unsigned long long epoch;

class SPIClass {
private:
    static int fd;
public:
    static int begin(const char* device);
    static uint8_t transfer(uint8_t _data);
    static void transfernb(char* tbuf, char* rbuf, uint32_t len);
    static void end();
};

extern SPIClass SPI;

// Simulate the delay() and millis() functions of arduino
void simulate_delay(unsigned int millis);
unsigned int simulate_millis(void);

#define millis() simulate_millis()
#define delay(x) simulate_delay(x)
#define delayMicroseconds(x) simulate_delay(x)
#define HIGH 0x1
#define LOW  0x0

#endif

