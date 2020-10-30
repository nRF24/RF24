#ifndef COMPATIBLITY_H
#define COMPATIBLITY_H

#include <sys/time.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
extern uint32_t millis(void);

extern uint32_t mircos(void);

#ifdef __cplusplus
}
#endif

#endif //Compatibility.h