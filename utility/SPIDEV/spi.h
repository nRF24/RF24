/**
 * @file spi.h
 * @author Purinda Gunasekara <purinda@gmail.com>
 *
 * Created on 24 June 2012, 11:00 AM
 *
 * Class declaration for SPI helper files
 */

#ifndef RF24_UTILITY_SPIDEV_SPI_H_
#define RF24_UTILITY_SPIDEV_SPI_H_

#include <inttypes.h>
#include <stdexcept>

#include "../../RF24_config.h" // This is cyclical and should be fixed

/** Specific excpetion for SPI errors */
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

    void begin(int busNo, uint32_t spi_speed = RF24_SPI_SPEED);

    uint8_t transfer(uint8_t tx);

    void transfernb(char* tbuf, char* rbuf, uint32_t len);

    void transfern(char* buf, uint32_t len);

    ~SPI();

private:
    int fd;
    uint32_t _spi_speed;
    bool spiIsInitialized = false;
    void init(uint32_t spi_speed = RF24_SPI_SPEED);
};

#endif // RF24_UTILITY_SPIDEV_SPI_H_
