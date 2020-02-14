/**
 * @file Chrono.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Chrono.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "Chrono.h"
#include "TimeSpec.h"


Chrono::Chrono()
{
    startTime_=timespec_now();
}


void Chrono::stop()
{
    stopTime_ = timespec_now();
}


void Chrono::restart()
{
    startTime_=timespec_now();
    stopTime_=timespec_now();
}


bool Chrono::isActive()
{
    return startTime_ == stopTime_;
}


double Chrono::startTime()
{
    return timespec_to_ms(startTime_);
}


double Chrono::stopTime()
{
    return timespec_to_ms(stopTime_);
}


double Chrono::lap()
{
    double lap = isActive() ? (timespec_to_ms(timespec_now())-startTime()) : (stopTime() - startTime()); // differences between the thread active or unactive
    return lap;
}