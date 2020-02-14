/**
 * @file PeriodicTimer.h
 * @author Davide Luigi Brambilla
 * @brief Class implementing a periodic timer derivate from the Timer class
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef PeriodicTimer_h_INCLUDED
#define PeriodicTimer_h_INCLUDED

#include "Timer.h"

/**
 * @brief Period Timer from Timer: setting the length of all the periods: first and following periods
 *
 */
class PeriodicTimer : public Timer
{
public:
	/**
 	* @brief start function adapted to the periodic timer in a way that it starts many times
 	* 
 	* @param duration_ms duration of a period of our timer
 	*/
	void start(double duration_ms);
};


#endif
