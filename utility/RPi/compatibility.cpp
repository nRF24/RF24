#include <chrono>
#include "compatibility.h"

#ifdef __cplusplus
extern "C" {
#endif

auto start = std::chrono::steady_clock::now();

uint32_t millis(void)
{
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

#ifdef __cplusplus
}
#endif
