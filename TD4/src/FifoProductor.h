/**
 * @file FifoProductor.h
 * @author Davide Luigi Brambilla
 * @brief FifoProductor class that implements a productor for an object of type T
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef FifoProductor_h_INCLUDED
#define FifoProductor_h_INCLUDED

#include "Fifo.hpp"
#include "Thread.h"
#include "Mutex.h"

/**
 * @brief FifoProductor class that implements a productor for an object of type T
 * 
 */
class FifoProductor : public Thread
{
private:
	/**
	 * @brief pointer towards the fifo object that will be shared by different threads
	 * 
	 */
	Fifo<int> *fifo;

	/**
	 * @brief number of objects T that have been produced
	 * 
	 */
	unsigned counter;

	/**
	 * @brief number of objects T to be produced
	 * 
	 */
	unsigned maxCount;
		
public:
	/**
	 * @brief Construct a new Fifo Productor object
	 * 
	 * @param fif pointer towards the fifo object that will be shared by different threads
	 * @param numItem number of Items T to be produced
	 */
	FifoProductor(Fifo<int> *fif, unsigned numItem);

	/**
	 * @brief Destroy the Fifo Productor object
	 * 
	 */
	~FifoProductor();

	/**
	 * @brief running the handling function - addding objects
	 * 
	 */
	void run();

	/**
	 * @brief Get tcounter
	 * 
	 * @return unsigned : counter
	 */
	unsigned getCounter();
};

#endif