/**
 * @file IncrMutex.h
 * @author Davide Luigi Brambilla
 * @brief Update of the class Incr from the TD4a with a mutex in order to have the right value of counter
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef IncrMutex_h_INCLUDED
#define IncrMutex_h_INCLUDED

#include "Thread.h"
#include "Mutex.h"

/**
 * @brief Update of the class Incr from the TD4a with a mutex in order to have the right value of counter
 * 
 */
class IncrMutex : public Thread
{
private:
	
	/**
	 * @brief number of times that the counter has to be incremented
	 * 
	 */
	unsigned int nLoop;
	
	/**
	 * @brief pointer to the variable counter that will be incremented
	 * 
	 */
	volatile double *counter;

	/**
	 * @brief pointer to the mutex that will be locked
	 * 
	 */
	Mutex* mutex;
	
public:
	/**
	 * @brief Construct a new Incr Mutex object
	 * 
	 * @param nLoops number of times that the counter has to be incremented
	 * @param pCounter  pointer to the variable counter that will be incremented
	 * @param schedPolicy policy that will be assigned to the thread
	 * @param m pointer to the mutex that will be locked
	 */
	IncrMutex(unsigned int nLoops, volatile double* pCounter, int schedPolicy, Mutex *m);
	
	/**
	 * @brief Destroy the Incr Mutex object
	 * 
	 */
	~IncrMutex();
	
	/**
	 * @brief Implementing the handle function related to the thread that, this time, will use the mutex
	 * 
	 */
	void run();
};

#endif
