/**
 * @file Monitor.h
 * @author Davide Luigi Brambilla
 * @brief Monitor class that will have the reference towards a mutex in order to access to it
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#ifndef Mutex_Monitor_h_INCLUDED
#define Mutex_Monitor_h_INCLUDED

#include "../TimeSpec.h"
#include "../Mutex.h"
#include <pthread.h>
#include <exception>

using namespace std;

/**
 * @brief Class Monitor that will have the reference towards a mutex in order to access to it
 * 
 */
class Mutex::Monitor
{
public:
	/**
	 * @brief Reference to the mutex
	 * 
	 */
	Mutex &mutex;

public:
	/**
	 * @brief Exception of the threads
	 * 
	 */
	class TimeoutException : exception
	{
	public:
		const char* launchingException() const noexcept;
	};

protected:
	/**
	 * @brief Construct a new Monitor object
	 * 
	 * @param m mutex that will be taken
	 */
	Monitor(Mutex &m);

public:
	/**
	 * @brief called for a locked mutex that will waits until a
	 * pthread_cond_broadcast() or a pthread_cond_signal() is received
	 * 
	 */
	void wait();

	/**
	 * @brief called for a locked mutex that will waits until a
	 * pthread_cond_broadcast() or a pthread_cond_signal()
	 * is received and waits for a given time
	 * 
	 * @param timeout_ms time that the thread will wait before taking
	 * an other time the mutex
	 * @return true 
	 * @return false 
	 */
	bool wait(double timeout_ms);

	/**
	 * @brief unlock a thread that is in blocked in a waiting condition
	 * 
	 */
	void notify();

	/**
	 * @brief unlock all the threads that are blocked in a waiting condition
	 * 
	 */
	void notifyAll();
};

#endif
