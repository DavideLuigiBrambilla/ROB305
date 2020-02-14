/**
 * @file main_td1b.cpp
 * @author Davide Luigi Brambilla
 * @brief main fuction to test SignalHandler
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include"SignalHandler.h"

#include <iostream>

using namespace std;

int main()
{
    struct timespec timeFirst;
    struct timespec timePeriod;

    // int counter = 0;
    volatile int counter = 0;
    /* we have to add volatile in order to explicit that the variable counter
    can be modified by other parallel processus. If we add -O3 to the
    compilation program we optimise the execution of the program and the
    fact that the counter can be modified by other processus won't be considered */
    
    timeFirst.tv_sec = 1;               // it is the first period 
    timeFirst.tv_nsec = 0;
    timePeriod.tv_sec = 0;              // it represents the length of the other periods*/
    timePeriod.tv_nsec = 500000000;

    //creation of the timer
    timer_t tid = init_signal(SIGRTMIN, myHandler, (void*)&counter); // we have to specify a cast towards void* in the case of init_signal
    
    itimerspec its;
    its.it_value = timeFirst;
    its.it_interval = timePeriod;
    timer_settime(tid, 0, &its, NULL);

    while(counter < 15)                 // in the optimized version this is rewritten as while(true) if we don't sepcify volatile because the counter i never modified inside the main
        continue;
    
    timer_delete(tid);

    return 0;
}
