/**
 * @file spi.h
 * Class declaration for SPI wrapping the Pico SDK
 */
#ifndef RF24_UTILITY_RP2_SPI_H_
#define RF24_UTILITY_RP2_SPI_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define RF24_SPI_BYTE_SIZE 8
#define RF24_SPI_ENDIAN    SPI_MSB_FIRST
#define RF24_SPI_CPHA      SPI_CPHA_0
#define RF24_SPI_CPOL      SPI_CPOL_0

// this SPI class uses beginTransaction() & endTransaction() to
// implement spi_init() & spi_deinit()
#define SPI_HAS_TRANSACTION 1

class SPI
{

public:
    SPI();

    /**
     * Start SPI
     * @param hw_id This is either `spi0` or `spi1` (provided by the Pico SDK)
     *
     * @note this function assumes using the default SPI pins defined for your
     * board in "pico-sdk/src/boards/include/boards/*.h" files of the Pico SDK.
     * @see begin(spi_inst_t, uint8_t, uint8_t, uint8_t) for using other pins as
     * your SPI bus.
     */
    void begin(spi_inst_t* hw_id);

    /**
     * Start SPI
     * @param hw_id This is either `spi0` or `spi1` (provided by the Pico SDK)
     * @param _sck The pin to be used as the SPI bus' sck
     * @param _tx The pin to be used as the SPI bus' tx (MOSI)
     * @param _rx The pin to be used as the SPI bus' rx (MISO)
     *
     * @note this function assumes using the default SPI pins defined for your
     * board in "pico-sdk/src/boards/include/boards/*.h" files of the Pico SDK.
     * @see The [Pico SDK has a chart of applicable pins](https://datasheets.raspberrypi.org/pico/raspberry-pi-pico-c-sdk.pdf#%5B%7B%22num%22%3A106%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C115%2C377.118%2Cnull%5D)
     * that can be used for hardware driven SPI transactions.
     */
    void begin(spi_inst_t* hw_id, uint8_t _sck, uint8_t _tx, uint8_t _rx);

    uint8_t transfer(uint8_t tx_);

    void transfernb(const uint8_t* txBuf, uint8_t* rxBuf, uint32_t len);

    void transfern(const uint8_t* buf, uint32_t len);

    void beginTransaction(uint32_t _spi_speed);

    /** deinit the SPI bus (using hw_id passed to begin()) */
    void endTransaction();

    virtual ~SPI();

private:
    /** the ID of the hardware driven SPI bus */
    spi_inst_t* _hw_id;
};

#endif // RF24_UTILITY_RP2_SPI_H_
