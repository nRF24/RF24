/*
 * Time keeping functions
 */
#ifndef RF24_UTILITY_PIGPIO_COMPATIBLITY_H_
#define RF24_UTILITY_PIGPIO_COMPATIBLITY_H_

#include <stdint.h> // for uintXX_t types

#ifdef __cplusplus
extern "C" {
#endif

void __msleep(int milisec);

void __usleep(int milisec);

void __start_timer();

uint32_t __millis();

#ifdef __cplusplus
}
#endif

#endif /* RF24_UTILITY_PIGPIO_COMPATIBLITY_H_ */
