#include "compatibility.h"
#include <chrono>
//static struct timeval start, end;
//static long mtime, seconds, useconds;

/**********************************************************************/
/**
 * This function is added in order to simulate arduino delay() function
 * @param milisec
 */
void __msleep(int milisec)
{
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    nanosleep(&req, (struct timespec*) NULL);
    //usleep(milisec*1000);
}

void __usleep(int milisec)
{
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000L;
    nanosleep(&req, (struct timespec*) NULL);
    //usleep(milisec);
}

auto start = std::chrono::steady_clock::now();

/**
 * This function is added in order to simulate arduino millis() function
 */
void __start_timer()
{
    //gettimeofday(&start, NULL);
}

long __millis()
{
    auto end = std::chrono::steady_clock::now();
	
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
