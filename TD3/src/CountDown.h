/**
 * @file CountDown.h
 * @author Davide Luigi Brambilla
 * @brief Countdown class that permits, by deriving from PeriodicTimer, to implement a coutdown  
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef CountDown_h_INCLUDED
#define CountDown_h_INCLUDED

#include "PeriodicTimer.h"

/**
 * @brief CountDown class that permits to implement a countdown
 * 
 */
class CountDown : public PeriodicTimer
{
private:
	
	/**
	 * @brief Counter to be decreased by the callback function 
	 * 
	 */
	int count;

public:
	
	/**
	 * @brief Construct a new CountDown object
	 * 
	 * @param n number of times the counter will be decreased
	 */
	CountDown(int n);
	
	/**
	 * @brief Get the counter 
	 * 
	 * @return int : the value of counter
	 */
	int getCount();

protected:
	/**
	 * @brief implementation of the pure virtual function of Timer in a way that is a countdown: decreasing the counter and stopping it when count = 0
	 * 
	 */
	void callback();
};


#endif
