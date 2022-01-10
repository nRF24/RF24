#ifndef __RF24_INCLUDES_H__
#define __RF24_INCLUDES_H__

#define RF24_RPi

#include "RPi/bcm2835.h"
#include "RPi/RF24_arch_config.h"
#ifndef RF24_NO_INTERRUPT
    #include "RPi/interrupt.h"
#endif

#endif
