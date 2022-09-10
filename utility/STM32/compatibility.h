/**
 * @file compatibility.h
 * declaration for timing helper functions
 */

#ifndef RF24_UTILITY_STM32_COMPATIBLITY_H_
#define RF24_UTILITY_STM32_COMPATIBLITY_H_

#include <stdint.h>
#include "includes.h"

uint32_t rf24_get_time_us();

void __usleep(int32_t usecs);

#endif // RF24_UTILITY_STM32_COMPATIBLITY_H_
