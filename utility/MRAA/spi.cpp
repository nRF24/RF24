
#include <mraa.h> // mraa_strresult(), mraa_result_t
#include "spi.h"

SPI::SPI()
{
    mspi = NULL;
}

void SPI::begin(int busNo, uint32_t spi_speed)
{
    // init mraa spi bus, it will handle chip select internally. For CS pin wiring user must check SPI details in hardware manual
    mspi = new mraa::Spi(busNo);

    mraa::Result result;

    result = mspi->mode(mraa::SPI_MODE0);
    if (result != mraa::Result::SUCCESS) {
        std::string msg = "[SPI::begin] Could not set bus mode;";
        msg += mraa_strresult((mraa_result_t)result);
        throw SPIException(msg);
        return;
    }

    result = mspi->bitPerWord(8);
    if (result != mraa::Result::SUCCESS) {
        std::string msg = "[SPI::begin] Could not set bus bits per word;";
        msg += mraa_strresult((mraa_result_t)result);
        throw SPIException(msg);
        return;
    }

    // Prophet: this will try to set 8MHz, however MRAA will reset to max platform speed and syslog a message of it
    result = mspi->frequency(spi_speed);
    if (result != mraa::Result::SUCCESS) {
        std::string msg = "[SPI::begin] Could not set bus frequency;";
        msg += mraa_strresult((mraa_result_t)result);
        throw SPIException(msg);
        return;
    }
}

void SPI::end()
{
    // Prophet: we should check for existence of mspi before deleting it
    if (mspi != NULL) {
        delete mspi;
    }
}

void SPI::setBitOrder(uint8_t bit_order)
{
    if (mspi != NULL) {
        mspi->lsbmode((mraa_boolean_t)bit_order);
    } // Prophet: bit_order
}

void SPI::setDataMode(uint8_t data_mode)
{
    if (mspi != NULL) {
        mspi->mode((mraa::Spi_Mode)data_mode);
    }
}

void SPI::setClockDivider(uint32_t spi_speed)
{
    if (mspi != NULL) {
        mspi->frequency(spi_speed);
    }
}

void SPI::chipSelect(int csn_pin)
{
}

SPI::~SPI()
{
    // Prophet: we should call end here to free used memory and unexport SPI interface
    this->end();
}
