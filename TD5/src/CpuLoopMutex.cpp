/**
 * @file CpuLoopMutex.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of CpuLoopMutex.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "CpuLoopMutex.h"
#include "Mutex/Lock.h"
#include "Thread.h"

#include <iostream>

using namespace std;

CpuLoopMutex::CpuLoopMutex(CpuLoop *l, int policy, int prior, Mutex *m, double timeEx, double timeReqM, double timeLastM) : Thread(), loop(l), mutex(m), timeExecution(timeEx), timeReqMutex(timeReqM), timeLastMutex(timeLastM)
{
	priority = prior;
	setScheduling(policy, priority);
}

CpuLoopMutex::~CpuLoopMutex()
{

}

void CpuLoopMutex::run()
{
	cout << "I am the thread with priority " << priority << endl;
	if(timeReqMutex != -1)
	{
		loop->runTime(timeReqMutex);							//before the mutex
		Mutex::Lock lock(*mutex, 10000); 						//time hat the mutex will wait before getting the lock
		cout << "I am the thread with priority " << priority << " and I have the Mutex" << endl;
		loop->runTime(timeLastMutex);							//duration of the mutex
		lock.~Lock();
		loop->runTime(timeExecution - (timeLastMutex + timeReqMutex));	//finishing the execution after the lock
	}
	else
	{
		loop->runTime(timeExecution);							//case without the mutex
		cout << "I am the thread with priority " << priority << endl;
	}
}

