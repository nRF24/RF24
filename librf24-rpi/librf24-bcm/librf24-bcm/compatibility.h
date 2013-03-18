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
#include <sys/time.h>

long __millis();


// Function, constant map as a result of migrating from Arduino
//#define delay(milisec) bcm2835_delay(milisec)
//#define delayMicroseconds(usec) bcm2835_delayMicroseconds(usec)

#ifdef	__cplusplus
}
#endif

#endif	/* COMPATIBLITY_H */

