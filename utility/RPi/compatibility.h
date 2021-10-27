#ifndef RF24_UTILITY_RPI_COMPATIBLITY_H_
#define RF24_UTILITY_RPI_COMPATIBLITY_H_

#include <sys/time.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
extern uint32_t millis(void);

#ifdef __cplusplus
}
#endif

#endif // RF24_UTILITY_RPI_COMPATIBLITY_H_
