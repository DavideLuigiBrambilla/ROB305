/**
 * @file Looper.h
 * @author Davide Luigi Brambilla
 * @brief Looper class that has to cycle until the wanted number of loops is reached or until the stop condition becomes true  
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef Looper_h_INCLUDED
#define Looper_h_INCLUDED

#include <limits.h>

#include "PeriodicTimer.h"

/**
 * @brief Looper class that has to cycle until the wanted number of loops is reached or until the stop condition becomes true
 * 
 */
class Looper
{
private:
	/**
	 * @brief variable that will stop the loops if becomes true
	 * 
	 */
	volatile bool doStop;
	/**
	 * @brief number of loops done, it is incremented at each iteration
	 * 
	 */
	double iLoop;

public:
	/**
	 * @brief start executing loops
	 * 
	 * @param nLoops =__DBL_MAX__ - the idea is to make it works until it is stopped
	 * @return double : the number of loops at the end of the execution
	 */
	double runLoop(double nLoops = __DBL_MAX__);

	/**
	 * @brief it will get the variable iLoop
	 * 
	 * @return double : the number of loops at the moment of the call of this function
	 */
	double getSample();
	
	/**
	 * @brief will set the doStop as false and will 
	 * 
	 * @return double : the number of loops at the moment of the stop
	 */
	double stopLoop();
};


#endif
