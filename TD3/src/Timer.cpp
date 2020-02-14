/**
 * @file Timer.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Timer.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "Timer.h"
#include "TimeSpec.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;    // Calling the function that calls the routine function

    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);
    
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = this;

    timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
    timer_delete(tid);
}


void Timer::start(double duration_ms)
{
    itimerspec its;

    its.it_value = timespec_from_ms(duration_ms);
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    
    timer_settime(tid, 0, &its, NULL);
}


void Timer::stop()
{
    itimerspec its;
    
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    
    timer_settime(tid, 0, &its, NULL);
}

void Timer::call_callback(int, siginfo_t* si, void*)
{
    Timer* timer = (Timer*) si->si_value.sival_ptr;
    timer->callback();
}