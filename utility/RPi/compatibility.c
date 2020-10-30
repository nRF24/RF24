#include "compatibility.h"

uint32_t millis(void)
{
    struct timeval now;
    uint32_t ms;

    gettimeofday(&now, NULL);

    ms = ((now.tv_sec * 1000000) + now.tv_usec) / 1000;
    return (ms);

}

uint32_t micros(void)
{
    struct timeval now;
    uint32_t us;

    gettimeofday(&now, NULL);

    us = (now.tv_sec * 1000000) + now.tv_usec;
    return (us);

}