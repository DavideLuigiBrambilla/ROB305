/**
 * @file SignalHandler.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementing SignalHandler.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "SignalHandler.h"

#include <iostream>


void myHandler (int, siginfo_t* si, void*)
{
    int* pCounter = (int*) si->si_value.sival_ptr;
    std::cout << "Iteration number " << *pCounter << std::endl;
    *pCounter += 1;
}

timer_t init_signal(int sigId, handler_t myHandler, void* myData)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = myHandler;
    sigemptyset(&sa.sa_mask);
    sigaction(sigId, &sa, NULL);
    
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = sigId;
    sev.sigev_value.sival_ptr = myData;

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid);
    
    return tid;
}