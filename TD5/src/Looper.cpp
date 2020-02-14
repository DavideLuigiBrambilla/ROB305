/**
 * @file Looper.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementing of Looper.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "Looper.h"
#include <iostream>

using namespace std;

double Looper::runLoop(double nLoops)
{
    doStop = false;
    iLoop  = 0;
    for (unsigned i = 0; i < nLoops; i++)
    {
        iLoop++;
        if(doStop)
        {
            break;
        }
    }
    return iLoop;
}

double Looper::getSample()
{
    return iLoop;
}

double Looper::stopLoop()
{
    doStop = true;
    return iLoop;
}
