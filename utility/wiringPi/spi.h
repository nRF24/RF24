/**
 * @file spi.h
 * Class declaration for SPI helper files
 */

#ifndef RF24_UTILITY_WIRINGPI_SPI_H_
#define RF24_UTILITY_WIRINGPI_SPI_H_

#include <stdint.h>
#include <stdexcept>
#include <string>

#ifndef RF24_SPI_SPEED
    #define RF24_SPI_SPEED 10000000
#endif

/** Specific exception for SPI errors */
class SPIException : public std::runtime_error
{
public:
    explicit SPIException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

class SPI
{

public:
    SPI();

    void begin(int csn_pin, uint32_t spi_speed = RF24_SPI_SPEED);

    uint8_t transfer(uint8_t);

    void transfernb(char*, char*, uint32_t);

    void transfern(char*, const uint32_t);

    virtual ~SPI();

private:
    int fd;
    int channel;
    uint8_t xferBuf[32 + 1];
    uint8_t xferByte;
};

#endif // RF24_UTILITY_WIRINGPI_SPI_H_
