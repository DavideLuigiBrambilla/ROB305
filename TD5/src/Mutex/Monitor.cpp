/**
 * @file Monitor.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Monitor.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "Monitor.h"

Mutex::Monitor::Monitor(Mutex &m) : mutex(m)
{
    
}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&mutex.posixCondId, &mutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    timespec timeout(timespec_now() + timespec_from_ms(timeout_ms));
    return !(bool) pthread_cond_timedwait(&mutex.posixCondId, &mutex.posixId, &timeout);
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&mutex.posixCondId);
}


const char* Mutex::Monitor::TimeoutException::launchingException() const noexcept
{
    return "Lock not possible!";
}
