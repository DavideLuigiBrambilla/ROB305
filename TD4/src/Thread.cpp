/**
 * @file Thread.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Thread.h
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "Thread.h"
#include "TimeSpec.h"

Thread::Thread() : chrono() //initializing the chrono object
{
}

Thread::~Thread()
{
}

bool Thread::start()
{
    if(!started)
    {
        started = true;
        PosixThread::start(call_run, this);
        return true;
    }
    else
    {
        return false;
    }
}


void* Thread::call_run(void* v_thread)
{
    Thread* thread = (Thread*) v_thread;
    thread->chrono.restart();
	thread->run();
	thread->chrono.stop();
    thread->isActive = false;
    return (void*) thread;
}

void Thread::sleep_ms(double delay_ms)
{
    timespec_wait(timespec_from_ms(delay_ms));
}

double Thread::startTime_ms()
{
    return chrono.startTime();
}

double Thread::stopTime_ms()
{
    return chrono.stopTime();
}

double Thread::execTime_ms()
{
    return (chrono.stopTime() - chrono.startTime());
}