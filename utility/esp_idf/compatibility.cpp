#include <esp_timer.h>
#include <unistd.h> // usleep()
#include "compatibility.h"

#ifdef __cplusplus
extern "C" {
#endif

void __msleep(int64_t milisec)
{
    usleep(milisec * 1000);
}

uint32_t __millis()
{
    // esp_timer_get_time() returns microseconds since boot
    return (uint32_t)(esp_timer_get_time() / 1000L);
}

#ifdef __cplusplus
}
#endif
