
#include "compatibility.h"


static long mtime, seconds, useconds;
static struct timeval start, end;

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
	nanosleep(&req, (struct timespec *)NULL);	
}

void __usleep(int milisec)
{
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000L;
	nanosleep(&req, (struct timespec *)NULL);	
}

/**
 * This function is added in order to simulate arduino millis() function
 */

 
void __start_timer()
{
	gettimeofday(&start, NULL);
}

long __millis()
{
	gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;	
	return mtime;
}
