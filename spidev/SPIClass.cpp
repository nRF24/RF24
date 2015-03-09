
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/time.h>
#include <time.h>

#include "SPIClass.h"

SPIClass SPI;
int SPIClass::fd = -1;

int SPIClass::begin(const char *device) {

    struct timeval tv;
    gettimeofday (&tv, NULL) ;
    epoch = (tv.tv_sec * 1000000 + tv.tv_usec) / 1000 ;

    uint8_t mode = 0;
    uint8_t bits = 8;
    uint32_t speed = 1000000;

    fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("can't open device");
        return fd;
    }

    int ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1) {
        perror("can't set spi mode");
        return ret;
    }

    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1) {
        perror("can't set bits per word");
        return ret;
    }

    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
        perror("can't set max speed hz");
        return ret;
    }

    return 0;
}


void SPIClass::end()
{
    if ( fd < 0 )
        return;
    close( fd );
    fd = -1;
}


uint8_t SPIClass::transfer(uint8_t _data) {
    uint16_t delay = 0;
    uint8_t rx = 0;
    struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)&_data,
            .rx_buf = (unsigned long)&rx,
            .len = 1,
            .speed_hz = 0,
            .delay_usecs = delay,
            .bits_per_word = 0
    };

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret == -1)
        perror("can't send spi message");
    return rx;
}


void SPIClass::transfernb(char *tbuf, char *rbuf, uint32_t len)
{
    uint16_t delay = 0;
    struct spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)tbuf,
            .rx_buf = (unsigned long)rbuf,
            .len = len,
            .speed_hz = 0,
            .delay_usecs = delay,
            .bits_per_word = 0
    };

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret == -1)
        perror("can't send spi message");
}


void simulate_delay(unsigned int millis)
{
    struct timespec sleeper;
    sleeper.tv_sec  = (time_t)(millis / 1000);
    sleeper.tv_nsec = (long)(millis % 1000) * 1000000;
    nanosleep(&sleeper, NULL);
}


unsigned int simulate_millis(void)
{
    struct timeval now;
    unsigned long long ms;
    gettimeofday(&now, NULL);
    ms = (now.tv_sec * 1000000 + now.tv_usec) / 1000 ;
    return ((uint32_t) (ms - epoch ));
}


