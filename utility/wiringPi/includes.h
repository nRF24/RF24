/**
* @file includes.h
* Configuration defines for RF24/Linux
*/

#ifndef RF24_UTILITY_INCLUDES_H_
#define RF24_UTILITY_INCLUDES_H_

/**
 * Define RF24_WIRINGPI configuration for RaspberryPi platform
 */
#define RF24_WIRINGPI

/**
 * Load the correct configuration for this platform
 */
#include "wiringPi/RF24_arch_config.h"

#endif // RF24_UTILITY_INCLUDES_H_
