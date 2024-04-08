/**
 * @file spi.h
 * Class declaration for SPI helper files
 *
 * See https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html
 */
#ifndef RF24_UTILITY_ESP_IDF_SPI_H_
#define RF24_UTILITY_ESP_IDF_SPI_H_

#include <stdint.h> // uintXX_t
#include <driver/spi_master.h>

#ifndef RF24_SPI_SPEED
    #define RF24_SPI_SPEED 10000000
#endif

#define SPI_HAS_TRANSACTION

enum spi_mode_t : uint8_t
{
    SPI_MODE0 = 0,
    SPI_MODE1 = 1,
    SPI_MODE2 = 2,
    SPI_MODE3 = 3,
};

class SPIClass
{

public:
    SPIClass();

    void begin(spi_host_device_t busNo = SPI1_HOST, uint32_t speed = RF24_SPI_SPEED);
    void begin(spi_host_device_t busNo, uint32_t speed, uint8_t mode, spi_bus_config_t* busConfig);

    void beginTransaction();

    void endTransaction();

    uint8_t transfer(uint8_t tx_);

    void transfernb(const uint8_t* txBuf, uint8_t* rxBuf, uint32_t len);

    void transfern(const uint8_t* buf, uint32_t len);

    virtual ~SPIClass();

private:
    /** SPI bus handle: A pointer to the allocated SPI device as initialized in begin() */
    spi_device_handle_t bus;
};

#endif // RF24_UTILITY_ESP_IDF_SPI_H_
