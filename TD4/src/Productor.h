/**
 * @file Productor.h
 * @author Davide Luigi Brambilla
 * @brief Thread Productor that will be in charge of adding items to the box
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#ifndef Productor_h_INCLUDED
#define Productor_h_INCLUDED

#include <pthread.h>
#include "Semaphore.h"
#include "Thread.h"

/**
 * @brief Thread Productor that will be in charge of adding items to the box
 * 
 */
class Productor : public Thread
{
private:
	/**
	 * @brief pointer to the object semaphore
	 * 
	 */
	Semaphore *semaphore;

	/**
	 * @brief number of items that have been created
	 * 
	 */
	unsigned counter;

	/**
	 * @brief number of items that have to be created
	 * 
	 */
	unsigned maxCount;
		
public:
	/**
	 * @brief Construct a new Productor object
	 * 
	 * @param semaph pointer towards the sempahore object ot use
	 * @param numItem number of items that have to be created
	 */
	Productor(Semaphore *semaph, unsigned numItem);

	/**
	 * @brief Destroy the Productor object
	 * 
	 */
	~Productor();

	/**
	 * @brief implementing the handling function - adding items
	 * 
	 */
	void run();

	/**
	 * @brief Get counter
	 * 
	 * @return unsigned : counter
	 */
	unsigned getCounter();
};

#endif