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
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>

const char* dev_name = "/dev/gpiochip0";

#define NEWGPIO


//std::map<int, GPIOfdCache_t> GPIO::cache;



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
  if (fd >= 0){
    
  }
  close(fd);
    #if !defined NEWGPIO


    FILE* f;
    f = fopen("/sys/class/gpio/export", "w");
    if (f == NULL) {
        throw GPIOException("can't export GPIO pin .check access rights");
    }
    fprintf(f, "%d\n", port);
    fclose(f);

    int counter = 0;
    char file[128];
    sprintf(file, "/sys/class/gpio/gpio%d/direction", port);

    while ((f = fopen(file, "w")) == NULL) { //Wait 10 seconds for the file to be accessible if not open on first attempt
        sleep(1);
        counter++;
        if (counter > 10) {
            throw GPIOException("can't access /sys/class/gpio/gpio%d/direction GPIO pin. check access rights");
            /*perror("Could not open /sys/class/gpio/gpio%d/direction");
            exit(0); */
        }
    }
    int l = (DDR == 0) ? fprintf(f, "in\n") : fprintf(f, "out\n");
    if (!(l == 3 || l == 4)) {
        fclose(f);
        throw GPIOException("can't set direction on GPIO pin. check access rights");
    }
    /*
    if (DDR == 0)
        fprintf(f, "in\n");
    else
        printf(f, "out\n");
    */
    fclose(f);

    // Caches the GPIO descriptor;
    sprintf(file, "/sys/class/gpio/gpio%d/value", port);
    int flags = (DDR == 0) ? O_RDONLY : O_WRONLY;
    int fd = ::open(file, flags);
    if (fd < 0) {
        throw GPIOException("Can't open the GPIO");
    }
    else {
        cache[port] = fd; // cache the fd;
        lseek(fd, SEEK_SET, 0);
    }
  #endif
  
}

void GPIO::Gclose(int port)
{
    close(fd);
    #if !defined NEWGPIO
    std::map<int, GPIOfdCache_t>::iterator i;
    i = cache.find(port);
    if (i != cache.end()) {
        close(i->second); // close the cached fd
        cache.erase(i);   // Delete cache entry
    }
    // Do unexport
    FILE* f;
    f = fopen("/sys/class/gpio/unexport", "w");
    if (f != NULL) {
        fprintf(f, "%d\n", port);
        fclose(f);
    }
    #endif
}

int GPIO::Gread(int port)
{
    
    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    if (fd >= 0){
      rq.lineoffsets[0] = port;
      rq.flags = GPIOHANDLE_REQUEST_INPUT;
      rq.lines = 1;
      ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
      close(fd);
      ret = ioctl(rq.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
      close(rq.fd);
      return ret;      
    }
    return -1;
    
    #if !defined NEWGPIO
    std::map<int, GPIOfdCache_t>::iterator i;
    int fd;
    i = cache.find(port);
    if (i == cache.end()) { // Fallback to open the gpio
        GPIO::open(port, GPIO::DIRECTION_IN);
        i = cache.find(port);
        if (i == cache.end()) {
            throw GPIOException("can't access to GPIO");
        }
        else {
            fd = i->second;
        }
    }
    else {
        fd = i->second;
    }

    char c;
    if (lseek(fd, 0, SEEK_SET) == 0 && ::read(fd, &c, 1) == 1) {
        return (c == '0') ? 0 : 1;
    }
    else {
        throw GPIOException("can't access to GPIO");
    }

    /*
    FILE *f;

    char file[128];
    sprintf(file, "/sys/class/gpio/gpio%d/value", port);
    f = fopen(file, "r");

    int i;
    fscanf(f, "%d", &i);
    fclose(f);
    return i;
    */
    #endif
}

void GPIO::Gwrite(int port, int value)
{
    
    struct gpiohandle_request rq;
    struct gpiohandle_data data;
    int fd, ret;
    fd = open(dev_name, O_RDONLY);
    rq.lineoffsets[0] = port;
    rq.flags = GPIOHANDLE_REQUEST_OUTPUT;
    rq.lines = 1;
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
    close(fd);
    data.values[0] = value;
    ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    close(rq.fd);
    
    #if !defined NEWGPIO
    std::map<int, GPIOfdCache_t>::iterator i;
    int fd;
    i = cache.find(port);
    if (i == cache.end()) { // Fallback to open the gpio
        GPIO::open(port, GPIO::DIRECTION_OUT);
        i = cache.find(port);
        if (i == cache.end()) {
            throw GPIOException("can't access to GPIO");
        }
        else {
            fd = i->second;
        }
    }
    else {
        fd = i->second;
    }

    if (lseek(fd, 0, SEEK_SET) != 0) {
        throw GPIOException("can't access to GPIO");
    }
    int l = (value == 0) ? ::write(fd, "0\n", 2) : ::write(fd, "1\n", 2);
    if (l != 2) {
        throw GPIOException("can't access to GPIO");
    }

    /*
    FILE *f;

    char file[128];
    sprintf(file, "/sys/class/gpio/gpio%d/value", port);
    f = fopen(file, "w");

    if (value == 0)
        fprintf(f, "0\n");
    else
        fprintf(f, "1\n");

    fclose(f);
    */
    #endif
}
