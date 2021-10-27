#include "compatibility.h"
#include <chrono>

auto start = std::chrono::steady_clock::now();

uint32_t millis(void)
{
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}
