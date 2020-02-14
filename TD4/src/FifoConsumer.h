/**
 * @file FifoConsumer.h
 * @author Davide Luigi Brambilla
 * @brief FifoConsumer class that implements a consumer for an object of type T
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef FifoConsumer_h_INCLUDED
#define FifoConsumer_h_INCLUDED

#include "Fifo.hpp"
#include "Thread.h"
#include "Mutex.h"

/**
 * @brief FifoConsumer class that implements a consumer for an object of type T
 * 
 */
class FifoConsumer : public Thread
{
private:
	/**
	 * @brief pointer towards the fifo object that will be shared by different threads
	 * 
	 */
	Fifo<int> *fifo;

	/**
	 * @brief number of object that has been removed
	 * 
	 */
	unsigned counter;

public:
	/**
	 * @brief Construct a new Fifo Consumer object
	 * 
	 * @param fif pointer towards the fifo object that will be shared by different threads
	 * @param mut pointer towards the mutex object that will be shared by different threads
	 */
	FifoConsumer(Fifo<int> *fif);

	/**
	 * @brief Destroy the Fifo Consumer object
	 * 
	 */
	~FifoConsumer();

	/**
	 * @brief running the handling function - removing objects
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
