/*
 *
 * Copyright (c) 2024, Copyright (c) 2024 TMRh20 & 2bndy5
 * All rights reserved.
 *
 *
 */
#include <linux/gpio.h>
#include "gpio.h"
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <sys/ioctl.h> // ioctl()
#include <errno.h>     // errno
#include <string.h>    // memset()

const char* dev_name = "/dev/gpiochip4";

GPIO::GPIO()
{
}

GPIO::~GPIO()
{
}

void GPIO::open(int port, int DDR)
{
    int fd;
    fd = ::open(dev_name, O_RDONLY);
    if (fd >= 0) {
        ::close(fd);
    }
    else {
        dev_name = "/dev/gpiochip0";
        fd = ::open(dev_name, O_RDONLY);
        if (fd >= 0) {
            ::close(fd);
        }
        else {
            throw GPIOException("can't open /dev/gpiochip");
        }
    }
}

void GPIO::close(int port)
{
}

int GPIO::read(int port)
{
    int fd = ::open(dev_name, O_RDWR);
    if (fd < 0) {
        throw GPIOException("Can't open character device");
        return -1;
    }

    struct gpio_v2_line_request rq;
    memset(&rq, 0, sizeof(rq));
    rq.offsets[0] = port;
    rq.num_lines = 1;
    rq.config.flags = GPIO_V2_LINE_FLAG_INPUT;

    int ret = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &rq);
    if (ret == -1) {
        std::string msg = "[GPIO::read] Can't get line handle from IOCTL; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return ret;
    }

    struct gpio_v2_line_values data;
    data.bits = 0;
    data.mask = 1;
    ret = ioctl(rq.fd, GPIO_V2_LINE_GET_VALUES_IOCTL, &data);
    if (ret == -1 || rq.fd <= 0) {
        std::string msg = "[GPIO::read] Can't get line value from IOCTL; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return ret;
    }
    ::close(rq.fd);
    ::close(fd);
    return data.bits & data.mask;
}

void GPIO::write(int port, int value)
{
    int fd = ::open(dev_name, O_RDWR);
    if (fd < 0) {
        throw GPIOException("Can't open character device");
        return;
    }

    gpio_v2_line_request rq;
    memset(&rq, 0, sizeof(rq));
    rq.offsets[0] = port;
    rq.num_lines = 1;
    rq.config.flags = GPIO_V2_LINE_FLAG_OUTPUT;

    int ret = ioctl(fd, GPIO_V2_GET_LINE_IOCTL, &rq);
    if (ret == -1) {
        std::string msg = "[GPIO::write] Can't get line handle from IOCTL; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return;
    }

    struct gpio_v2_line_values data;
    data.bits |= value;
    data.mask = 1;
    ret = ioctl(rq.fd, GPIO_V2_LINE_SET_VALUES_IOCTL, &data);
    if (ret == -1 || rq.fd <= 0) {
        std::string msg = "[GPIO::write] Can't set line value from IOCTL; ";
        msg += strerror(errno);
        throw GPIOException(msg);
        return;
    }
    ::close(rq.fd);
    ::close(fd);
}
