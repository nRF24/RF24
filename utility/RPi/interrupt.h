/*
Interrupts functions extruded from wiringPi library by Oitzu.
*/

#include "RF24_arch_config.h"

#define INT_EDGE_SETUP          0
#define INT_EDGE_FALLING        1
#define INT_EDGE_RISING         2
#define INT_EDGE_BOTH           3

static void *interruptHandler (void *arg);

#ifdef __cplusplus
extern "C" {
#endif
extern int waitForInterrupt (int pin, int mS);
extern int piHiPri (const int pri);
extern int attachInterrupt (int pin, int mode, void (*function)(void));
#ifdef __cplusplus
}
#endif