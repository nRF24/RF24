#ifndef RF24_UTILITY_INCLUDES_H_
#define RF24_UTILITY_INCLUDES_H_

#define RF24_RPi

#include "RPi/bcm2835.h"
#include "RPi/RF24_arch_config.h"
#ifndef RF24_NO_INTERRUPT
    #include "RPi/interrupt.h"
#endif

#endif // RF24_UTILITY_INCLUDES_H_
