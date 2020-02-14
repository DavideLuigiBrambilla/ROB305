/**
 * @file Chrono.h
 * @author Davide Luigi Brambilla
 * @brief Chrono classe in order to create a chronometer object
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#ifndef Chrono_h_INCLUDED
#define Chrono_h_INCLUDED

#include <time.h>

/**
 * @brief Chrono classes in order to create a chronometer object
 * 
 */
class Chrono
{
private:
	/**
	 * @brief starting time of the chronometer
	 * 
	 */
	timespec startTime_;

	/**
	 * @brief ending time of the chronometer
	 * 
	 */
	timespec stopTime_;

public:
	/**
	 * @brief Construct a new Chrono object
	 * 
	 */
	Chrono();

	/**
	 * @brief stopping the chrono
	 * 
	 */
	void stop();			
	
	/**
	 * @brief restarting chrono
	 * 
	 */
	void restart();
	
	/**
	 * @brief visualisation of the state of chrono
	 * 
	 */
	bool isActive();
	
	/**
	 * @brief get startTime_
	 * 
	 * @return double : startTime_
	 */
	double startTime();		

	/**
	 * @brief get stopTime_
	 * 
	 * @return double : stopTime_
	 */
	double stopTime();

	/**
	 * @brief get how much the Chrono has last
	 * 
	 * @return double : stopTime_ - startTime_
	 */
	double lap();
};

#endif
