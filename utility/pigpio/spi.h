/*
 *
 */

#ifndef SPI_H
#define SPI_H

/**
 * @file spi.h
 * \cond HIDDEN_SYMBOLS
 * Class declaration for SPI helper files
 */

/**
* Example GPIO.h file
*
* @defgroup SPI SPI Example
*
* See RF24_arch_config.h for additional information
* @{
*/

#include <inttypes.h>
#include <stdexcept>

#include "../../RF24_config.h"

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
    /**
    * SPI constructor
    */
    SPI();

    /**
    * Start SPI
    */
    void begin(int busNo, uint32_t spi_speed);

    /**
    * Transfer a single byte
    * @param tx Byte to send
    * @return Data returned via spi
    */
    uint8_t transfer(char tx);

    /**
    * Transfer a buffer of data
    * @param tbuf Transmit buffer
    * @param rbuf Receive buffer
    * @param len Length of the data
    */
    void transfernb(char* tbuf, char* rbuf, uint32_t len);

    /**
    * Transfer a buffer of data without an rx buffer
    * @param buf Pointer to a buffer of data
    * @param len Length of the data
    */
    void transfern(char* buf, uint32_t len)
    {
        transfernb(buf, buf, len);
    }

    ~SPI();

private:
    unsigned spiHandle;
    bool spiIsInitialized = false;
    void init(uint32_t spi_speed);
};

/**
 * \endcond
 */
/*@}*/
#endif /* SPI_H */
