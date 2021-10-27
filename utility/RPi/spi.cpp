#include "spi.h"
#include <pthread.h>
#include <unistd.h>
#include <stdexcept>

static pthread_mutex_t spiMutex = PTHREAD_MUTEX_INITIALIZER;
bool bcmIsInitialized = false;

SPI::SPI()
{
}

void SPI::begin(int busNo, uint32_t spi_speed)
{
    if (!bcmIsInitialized) {
        if (!bcm2835_init()) {
            return;
        }
    }
    bcmIsInitialized = true;
    bcm2835_spi_begin();
}

void SPI::beginTransaction(SPISettings settings)
{
    if (geteuid() != 0) {
        throw std::runtime_error("Process should run as root");
    }
    pthread_mutex_lock(&spiMutex);
    setBitOrder(settings.border);
    setDataMode(settings.dmode);
    setClockDivider(settings.clck);
}

void SPI::endTransaction()
{
    pthread_mutex_unlock(&spiMutex);
}

void SPI::setBitOrder(uint8_t bit_order)
{
    bcm2835_spi_setBitOrder(bit_order);
}

void SPI::setDataMode(uint8_t data_mode)
{
    bcm2835_spi_setDataMode(data_mode);
}

void SPI::setClockDivider(uint32_t spi_speed)
{
    //bcm2835_spi_setClockDivider(spi_speed);
    bcm2835_spi_set_speed_hz(spi_speed);
}

void SPI::chipSelect(int csn_pin)
{
    bcm2835_spi_chipSelect(csn_pin);
    delayMicroseconds(5);
}

SPI::~SPI()
{
}
