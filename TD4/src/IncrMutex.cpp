/**
 * @file IncrMutex.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementing IncrMutex.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "IncrMutex.h"
#include "Mutex/Lock.h"
#include "Mutex/TryLock.h"

#include <iostream>

IncrMutex::IncrMutex(unsigned int nLoops, volatile double* pCounter, int schedPolicy, Mutex *m) : Thread()
{
    nLoop = nLoops;
    counter = pCounter;
    mutex = m;

    int priority = rand()%100 + 1;      //I get a number between 1 and 100
    if(priority == 100) priority--;      //priority has to be in a range between 1 and 99
    int schedPriority = schedPolicy == SCHED_OTHER ? 0 : priority;
    
    setScheduling(schedPolicy, schedPriority);
}

IncrMutex::~IncrMutex()
{
}

void IncrMutex::run()
{
    Mutex::Lock lock(*mutex);
    // Mutex::Lock lock(*mutex, 50);
    // Mutex::TryLock trylock(*mutex);
    for(unsigned int iLoop=0; iLoop < nLoop; ++iLoop)
    {
        *counter += 1.0;
    }
}