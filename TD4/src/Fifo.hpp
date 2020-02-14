/**
 * @file Fifo.hpp
 * @author Davide Luigi Brambilla
 * @brief Fifo class that will contains both the declaration and the implementation of the fuctions
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include "Mutex.h"
#include "Mutex/Lock.h"
#include "Mutex/TryLock.h"

#include <queue>
#include <exception>
#include <string>

using namespace std;

/**
 * @brief 
 * 
 * @tparam T object type that will be adapted
 */
template <typename T> class Fifo
{
private:
	/**
	 * @brief elements in the queue that will have to be popped and pushed
	 * 
	 */
	std::queue<T> elements;

	/**
	 * @brief mutex element that guarantee the acces
	 * 
	 */
	Mutex mutex;
public:
	/**
	 * @brief Exception in the case of Empty Queue
	 * 
	 */
	class EmptyException : exception
	{
		public:
			const char* launchingException() const noexcept;
	};	
public:
	/**
	 * @brief Construct a new Fifo object
	 * 
	 */
	Fifo();

	/**
	 * @brief Destroy the Fifo object
	 * 
	 */
	~Fifo();

	/**
	 * @brief adding an element at th end of the queue
	 * 
	 * @param element element to be added
	 */
	void push(T element);

	/**
	 * @brief removing the element at the top of the queue
	 * 
	 * @return T : gives back the element popped
	 */
	T pop();

	/**
	 * @brief removing the element at the top of the queue (with timeout)
	 * 
	 * @param timeout_ms using the wait in the wait function
	 * @return T : gives back the element popped
	 */
	T pop(double timeout_ms);
};

template <typename T> Fifo<T>::Fifo()
{

}

template <typename T> Fifo<T>::~Fifo()
{

}

template <typename T> void Fifo<T>::push(T element)
{
	Mutex::Lock lock(mutex);
	elements.push(element);
}

template <typename T> T Fifo<T>::pop()
{
	Mutex::Lock lock(mutex);
	while(elements.size() == 0)
	{
		lock.wait();
	}
	T popped = elements.front();
	elements.pop();

	return popped;
}

template <typename T> T Fifo<T>::pop(double timeout_ms)
{
	Mutex::Lock lock(mutex);
	if(elements.size() == 0)
	{
		lock.wait(timeout_ms);
	}
	if(elements.size() != 0)
	{
		T popped = elements.front();
		elements.pop();
		return popped;
	}
	else
	{
		throw Fifo<T>::EmptyException();
	}
}

template <typename T> const char *Fifo<T>::EmptyException::launchingException() const noexcept
{
		return "No elements to pop! The queue is empty!\n";
}

#endif
