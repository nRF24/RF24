/**
 * @file includes.h
 * Configuration defines for RF24/Linux
 */

#ifndef RF24_UTILITY_INCLUDES_H_
#define RF24_UTILITY_INCLUDES_H_

/**
 * Define a specific platform for this configuration
 */
#define LITTLEWIRE

/**
 * Load the correct configuration for this platform
 */
#include "LittleWire/RF24_arch_config.h"

#endif // RF24_UTILITY_INCLUDES_H_
