#include <time.h>
#include <chrono>
#include "compatibility.h"

void __msleep(int millisec)
{
    struct timespec req; // = {0};
    req.tv_sec = (time_t)millisec / 1000;
    req.tv_nsec = (millisec % 1000) * 1000000L;
    clock_nanosleep(CLOCK_REALTIME, 0, &req, NULL);
}

void __usleep(int microsec)
{
    struct timespec req; // = {0};
    req.tv_sec = (time_t)microsec / 1000000;
    req.tv_nsec = (microsec % 1000000) * 1000;
    clock_nanosleep(CLOCK_REALTIME, 0, &req, NULL);
}

void __start_timer()
{
}

auto start = std::chrono::steady_clock::now();

uint32_t __millis()
{
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
