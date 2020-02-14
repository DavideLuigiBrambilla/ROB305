/**
 * @file Semaphore.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Semaphore.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "Semaphore.h"
#include "TimeSpec.h"

#include <iostream>

using namespace std;

Semaphore::Semaphore(unsigned initCount, unsigned maximumCount)
{
    counter = initCount;
	maxCount = maximumCount;
}

void Semaphore::give()
{
    Mutex::Lock lock(mutex);
    if(counter < maxCount)
    {
        counter++;
    }
    lock.notify();
}

void Semaphore::take()
{
    Mutex::Lock lock(mutex);
    while(counter == 0)
    {
        lock.wait();
    }
    counter--;
}

bool Semaphore::take(double timeout_ms)
{
    Mutex::Lock lock(mutex);
    if(counter == 0)
    {
        lock.wait(timeout_ms);
    }
    if(counter == 0)
    {
        return false;
    }
    counter--;
    return true;
}