/**
 * @file Semaphore.h
 * @author Davide Luigi Brambilla
 * @brief Class Semaphore that implements une box to which we will give or we will take some items with simultaneous acces
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Semaphore_h_INCLUDED
#define Semaphore_h_INCLUDED

#include <limits.h>
#include <pthread.h>
#include "Mutex.h"
#include "Mutex/Lock.h"
#include "Mutex/TryLock.h"

/**
 * @brief Class Semaphore that implements une box to which we will give or we will take some items with simultaneous acces
 * 
 */
class Semaphore
{
public:
	/**
	 * @brief 	will count the number of items that we are inserting .
	 * 		It will increment with a give()
	 * 		It will decrease with a take()
	 */
	unsigned counter;

	/**
	 * @brief the maximal number of item that can be stored in the box
	 * 
	 */
	unsigned maxCount;

private:	
	/**
	 * @brief mutex object that will be taken by a thread
	 * 
	 */
	Mutex mutex;

public:
	/**
	 * @brief Construct a new Semaphore object
	 * 
	 * @param initCount number of items that are in the box at the beginning
	 * @param maximumCount maximal number of item that can be stored in the box 
	 */
	Semaphore(unsigned initCount = 0, unsigned maximumCount = UINT_MAX);
	
	/**
	 * @brief adding an item
	 * 
	 */
	void give();
	
	/**
	 * @brief taking of an item
	 * 
	 */
	void take();

	/**
	 * @brief taking of an item - possibility to wait for a certain time if the box is empty
	 * 
	 */
	bool take(double timeout_ms);
};

#endif
