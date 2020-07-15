#include "compatibility.h"


// Time for millis()
static uint32_t epoch;

uint32_t millis(void)
{
    struct timeval now;
    uint32_t ms;

    gettimeofday(&now, NULL);

    ms = (now.tv_sec * 1000000 + now.tv_usec) / 1000;

    return ((uint32_t)(ms - epoch));
}