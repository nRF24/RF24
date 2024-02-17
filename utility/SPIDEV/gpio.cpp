/*
 * https://github.com/mrshu/GPIOlib
 * Copyright (c) 2011, Copyright (c) 2011 mr.Shu
 * All rights reserved.
 *
 * Modified on 24 June 2012, 11:06 AM
 * File:   gpio.cpp
 * Author: purinda (purinda@gmail.com)
 *
 *  Patched for filedescriptor catching and error control by L Diaz 2018
 */
#include <linux/gpio.h>
#include "gpio.h"
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <sys/ioctl.h> // ioctl()

char* dev_name = "/dev/gpiochip4";

GPIO::GPIO()
{
}

GPIO::~GPIO()
{
}

int fd;

void GPIO::Gopen(int port, int DDR)
{
    fd = open(dev_name, O_RDONLY);
    if (fd >= 0) {
        close(fd);
    }
    else {
        dev_name = "/dev/gpiochip0";
        fd = open(dev_name, O_RDONLY);
        if (fd >= 0) {
            close(fd);
        }
        else {
            throw GPIOException("can't open /dev/gpiochip");
        }
    }
}

void GPIO::Gclose(int port)
{
}

int GPIO::Gread(int port)
{

    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    if (fd >= 0) {
        rq.lineoffsets[0] = port;
        rq.flags = GPIOHANDLE_REQUEST_INPUT;
        rq.lines = 1;
        ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
        if (ret == -1) {
            throw GPIOException("Can't get line handle from IOCTL");
            return ret;
        }
        close(fd);
        ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
        if (ret == -1) {
            throw GPIOException("Can't get line value from IOCTL");
            return ret;
        }
        close(rq.fd);
        return ret;
    }
    return -1;
}

void GPIO::Gwrite(int port, int value)
{

    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    if (fd < 0) {
        throw GPIOException("Can't open dev");
        return;
    }
    rq.lineoffsets[0] = port;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    if (ret == -1) {
        throw GPIOException("Can't get line handle from IOCTL");
        return;
    }
    close(fd);
    data.values[0] = value;
    ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (ret == -1) {
        throw GPIOException("Can't set line value from IOCTL");
        return;
    }
    close(rq.fd);
}
