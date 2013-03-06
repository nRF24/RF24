/* 
 * File:   compatiblity.h
 * Author: purinda
 *
 * Created on 24 June 2012, 3:08 PM
 */

#ifndef COMPATIBLITY_H
#define	COMPATIBLITY_H

#ifdef	__cplusplus
extern "C" {
#endif
	
#include <stddef.h>
#include <time.h>
#include <sys/time.h>

// added attribute unused to avoid compiler warnings
static struct timeval start __attribute__ ((unused)) ,end __attribute__ ((unused));

static long __attribute__ ((unused)) mtime;
static long __attribute__ ((unused)) seconds;
static long __attribute__ ((unused)) useconds;

void __msleep(int milisec);
void __usleep(int milisec);
void __start_timer();
long __millis();

#ifdef	__cplusplus
}
#endif

#endif	/* COMPATIBLITY_H */

