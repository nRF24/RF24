/**
 * @file compatibility.h
 * @author purinda
 *
 * Created on 24 June 2012, 3:08 PM
 *
 * Class declaration for SPI helper files
 */

#ifndef RF24_UTILITY_ATXMEGAD3_COMPATIBLITY_H_
#define RF24_UTILITY_ATXMEGAD3_COMPATIBLITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
//#include <time.h>
//#include <sys/time.h>

void __msleep(int milisec);

void __usleep(int usec);

void __start_timer();

long __millis();

void update_milisec();

#ifdef __cplusplus
}
#endif

#endif // RF24_UTILITY_ATXMEGAD3_COMPATIBLITY_H_
