/**
 * @file SignalHandler.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of SignalHandler.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "SignalHandler.h"

#include <iostream>

void myHandler (int, siginfo_t* si, void*)
{
    bool* boolean = (bool*) si->si_value.sival_ptr;
    // std::cout << "The boolean value of stop is " << *boolean << std::endl; 
    *boolean = true;            
    // std::cout << "The boolean value of stop is " << *boolean << std::endl;
    
}

timer_t init_signal(int sigId, handler_t myHandler, void* myData)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;                // function that we will execute
    sigemptyset(&sa.sa_mask);
    sigaction(sigId, &sa, NULL);
    
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = sigId;
    sev.sigev_value.sival_ptr = myData;         // we are passing to the function to execute the parameter

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);   // creation of the timer
    
    return tid;
}
