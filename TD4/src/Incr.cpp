/**
 * @file Incr.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Incr.h
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Incr.h"
#include <iostream>

using namespace std;

Incr::Incr(unsigned int nLoops, volatile double* pCounter, int schedPolicy) : Thread()
{
    counter = pCounter;
    nLoop = nLoops;

    int priority = rand()%100 + 1;       //I get a number between 1 and 100
    if(priority == 100) priority--;      //priority has to be in a range between 1 and 99
    int schedPriority = schedPolicy == SCHED_OTHER ? 0 : priority;
    setScheduling(schedPolicy, schedPriority);
}

Incr::~Incr()
{
}

void Incr::run()
{
    for(unsigned int iLoop=0; iLoop < nLoop; ++iLoop)
    {
        *counter += 1.0;
    }
}