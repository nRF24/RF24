#include <time.h>
#include <sys/time.h> // gettimeofday()
#include "compatibility.h"

#ifdef __cplusplus
extern "C" {
#endif

void __msleep(int milisec)
{
    struct timespec req; // = {0};
    req.tv_sec = (time_t)milisec / 1000;
    req.tv_nsec = (milisec % 1000) * 1000000L;
    //nanosleep(&req, (struct timespec *)NULL);
    clock_nanosleep(CLOCK_REALTIME, 0, &req, NULL);
}

void __usleep(int microsec)
{
    struct timespec req; // = {0};
    req.tv_sec = (time_t)microsec / 1000000;
    req.tv_nsec = (microsec % 1000000) * 1000;
    //nanosleep(&req, (struct timespec *)NULL);
    clock_nanosleep(CLOCK_REALTIME, 0, &req, NULL);
}

uint32_t __millis()
{
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    return (uint32_t)(((int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec) / 1000L);
}

#ifdef __cplusplus
}
#endif
