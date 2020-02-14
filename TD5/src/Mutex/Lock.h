/**
 * @file Lock.h
 * @author Davide Luigi Brambilla
 * @brief class Lock that will allow to take a lock on a mutex and is derived from Monitor
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Mutex_Lock_h_INCLUDED
#define Mutex_Lock_h_INCLUDED

#include "Monitor.h"
#include <pthread.h>


/**
 * @brief class Lock that will allow to take a lock on a mutex and is derived from Monitor
 * 
 */
class Mutex::Lock : public Monitor
{
public:
	/**
	 * @brief Construct a new Lock object
	 * 
	 * @param m reference to the mutex that we are going to lock
	 */
	Lock(Mutex &m);

	/**
	 * @brief Construct a new Lock object
	 * 
	 * @param m reference to the mutex that we are going to lock
	 * @param timeout_ms time that we will pass to the lock with timeout
	 */
	Lock(Mutex &m, double timeout_ms);

	/**
	 * @brief Destroy the Lock object
	 * 
	 */
	~Lock();
};

#endif