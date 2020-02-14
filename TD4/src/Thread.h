/**
 * @file Thread.h
 * @author Davide Luigi Brambilla
 * @brief Thread class that implements a thread and will be based on the basic class PosixThread
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

#include "PosixThread.h"
#include "Chrono.h"

/**
 * @brief Thread class that implements a thread and will be based on the basic class PosixThread
 * 
 */
class Thread : public PosixThread
{
private:
	/**
	 * @brief Chrono object used only inside the class in order to measure the execution time
	 * 
	 */
	Chrono chrono;

	/**
	 * @brief tells if the thread was started or not
	 * 
	 */
	bool started = false;

public:
	/**
	 * @brief Construct a new Thread object
	 * 
	 */
	Thread();
	
	/**
	 * @brief Destroy the Thread object
	 * 
	 */
	~Thread();
	
	/**
	 * @brief starting the thread
	 * 
	 * @return true : if the thread wasn't started already
	 * @return false : if the thread was already started
	 */
	bool start();

protected:
	
	/**
	 * @brief virtual void function that will be implemented by the derivate class
	 * 
	 */
	virtual void run() = 0;

private:
	
	/**
	 * @brief private function that will be use only in the Thread class to start the function
	 * 
	 * @param v_thread pointer to the thread where the execution will be run 
	 * @return void* 
	 */
	static void * call_run(void* v_thread);

public:
	/**
	 * @brief function used to make the thread sleep for a while
	 * 
	 * @param delay_ms time that the thread has to sleep 
	 */
	static void sleep_ms(double delay_ms);

	/**
	 * @brief gives the time where the Thread has started
	 * 
	 * @return double : startingTime of the chrono
	 */
	double startTime_ms();
	
	/**
	 * @brief gives the time where the Thread has finished
	 * 
	 * @return double : stopTime of the chrono
	 */
	double stopTime_ms();
	
	/**
	 * @brief gives the duration of the thread
	 * 
	 * @return double : duration of the chrono
	 */
	double execTime_ms();	
};

#endif
