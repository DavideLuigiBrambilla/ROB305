/**
 * @file Incr.h
 * @author Davide Luigi Brambilla
 * @brief class Incr that will have the objective to increment the counter for a number of cycles 
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Incr_h_INCLUDED
#define Incr_h_INCLUDED

#include "Thread.h"

/**
 * @brief class Incr that will have the objective to increment the counter for a number of cycles 
 * 
 */
class Incr : public Thread
{
private:
	/**
	 * @brief pointer to the variable counter that will be incremented
	 * 
	 */
	volatile double *counter;

	/**
	 * @brief number of times that the counter has to be incremented
	 * 
	 */
	unsigned int nLoop;

public:
	/**
	 * @brief Construct a new Incr object
	 * 
	 * @param nLoops number of times that the counter has to be incremented
	 * @param pCounter pointer to the variable counter that will be incremented
	 * @param schedPolicy policy that will be chosen for the thread
	 */
	Incr(unsigned int nLoops, volatile double* pCounter, int schedPolicy);
	
	/**
	 * @brief Destroy the Incr object
	 * 
	 */
	~Incr();

	/**
	 * @brief implementing the handle function related to the thread
	 * 
	 */
	void run();
};

#endif
