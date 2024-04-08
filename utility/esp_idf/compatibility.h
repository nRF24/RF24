/**
 * @file compatibility.h
 * Class declaration for SPI helper files
 */
#ifndef RF24_UTILITY_ESP_IDF_COMPATIBLITY_H_
#define RF24_UTILITY_ESP_IDF_COMPATIBLITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void __msleep(int milisec);

void __usleep(int microsec);

uint32_t __millis();

#ifdef __cplusplus
}
#endif

#endif // RF24_UTILITY_ESP_IDF_COMPATIBLITY_H_
