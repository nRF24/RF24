/*
 * File:   compatiblity.h
 * Author: kripton
 *
 * Created on 01 April 2021
 */

/**
 * @file compatibility.h
 * Class declaration for SPI helper files
 */

/**
 * Example of compatibility.h class declaration for timing functions portability
 *
 * @defgroup Porting_Timing Porting: Timing
 *
 * @{
 */

#ifndef COMPATIBLITY_H
#define COMPATIBLITY_H

#ifdef __cplusplus
extern "C" {
#endif

void __msleep(int milisec);

void __usleep(int milisec);

void __start_timer();

long __millis();

#ifdef    __cplusplus
}
#endif

#endif    /* COMPATIBLITY_H */

/**@}*/
