/**
 * @file Mutex.h
 * @author Davide Luigi Brambilla
 * @brief Mutex class that will permit to implement the mutual exclusion between different threads 
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <pthread.h>
#include <exception>

/**
 * @brief Mutex class that will permit to implement the mutual exclusion between different threads
 * 
 */
class Mutex
{
public:
	/**
	 * @brief class that takes the mutex
	 * 
	 */
	class Lock;

	/**
	 * @brief class that tries to take the mutex
	 * 
	 */
	class TryLock;

	/**
	 * @brief class that will handle the Lock and Unlock
	 * 
	 */
	class Monitor;

private:
	/**
	 * @brief Id of the mutex
	 * 
	 */
	pthread_mutex_t posixId;

	/**
	 * @brief condition attribute of the mutex
	 * 
	 */
	pthread_cond_t posixCondId;

public:

	/**
	 * @brief Construct a new Mutex object with the possibility to invert the priority
	 * 
	 */
	Mutex(bool isInversionSafe);

	/**
	 * @brief Destroy the Mutex object
	 * 
	 */
	~Mutex();

private:
	/**
	 * @brief locks the mutex
	 * 
	 */
	void lock();

	/**
	 * @brief locks the mutex with a timedlock (lock with timeout)
	 * 
	 * @param timeout_ms time to be used in timedlock
	 * @return true : if it worked
	 * @return false : if there had been an error
	 */
	bool lock(double timeout_ms);

	/**
	 * @brief tries to lock the mutex
	 * 
	 * @return true : if it worked 
	 * @return false : if there had been an error
	 */
	bool trylock();

	/**
	 * @brief unlock the mutex
	 * 
	 */
	void unlock();
};

#endif
