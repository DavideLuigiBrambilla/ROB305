/**
 * @file Consumer.h
 * @author Davide Luigi Brambilla
 * @brief Thread Consumer that will be in charge of taking off items from the box
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef Consumer_h_INCLUDED
#define Consumer_h_INCLUDED

#include <limits.h>
#include <pthread.h>
#include "Semaphore.h"
#include "Thread.h"

/**
 * @brief Thread Consumer that will be in charge of removing items from the box
 * 
 */
class Consumer : public Thread
{
private:
	/**
	 * @brief pointer to a Semaphore(the box where we'll remove the items)
	 * 
	 */
	Semaphore *semaphore;

	/**
	 * @brief counter on the number of items that we will remove
	 * 
	 */
	unsigned counter;

public:
	/**
	 * @brief Construct a new Consumer object
	 * 
	 * @param semaph pointer to the right semaphore
	 */
	Consumer(Semaphore *semaph);

	/**
	 * @brief Destroy the Consumer object
	 * 
	 */
	~Consumer();

	/**
	 * @brief running the handling function : removing items
	 * 
	 */
	void run();

	/**
	 * @brief Get the counter
	 * 
	 * @return unsigned : counter
	 */
	unsigned getCounter();
};

#endif
