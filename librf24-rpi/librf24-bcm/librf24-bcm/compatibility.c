
#include "compatibility.h"

/**********************************************************************/
/**
 * This function is added in order to simulate arduino delay() function
 * @param milisec
 */
 
static struct timeval start, end;
static long mtime, seconds, useconds;    


/**
 * This function is added in order to simulate arduino millis() function
 */
long __millis()
{
	gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;	
	return mtime;
}
