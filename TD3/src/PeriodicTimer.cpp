/**
 * @file PeriodicTimer.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of PeriodicTimer.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "PeriodicTimer.h"
#include "TimeSpec.h"

void PeriodicTimer::start(double duration_ms)
{
    itimerspec its;

    its.it_value = timespec_from_ms(duration_ms);
    its.it_interval = timespec_from_ms(duration_ms);
    
    timer_settime(tid, 0, &its, NULL);
}