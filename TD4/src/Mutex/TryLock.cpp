/**
 * @file TryLock.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of TryLock.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "TryLock.h"

Mutex::TryLock::TryLock(Mutex &m) : Monitor(m)
{
    if(mutex.trylock() == false)
    {
        throw TimeoutException();   
    }
}

Mutex::TryLock::~TryLock()
{
    mutex.unlock();
}
