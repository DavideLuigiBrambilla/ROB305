/**
 * @file Timer.h
 * @author Davide Luigi Brambilla
 * @brief Timer class that permits to implement and initialize a timer. It will need a derivate class to implement it because of the presence of virtual funtion
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>

/**
 * @brief Timer class that permits to implement and initialize a timer.
 * 
 */
class Timer
{
protected:
	/**
	 * @brief the timer variable timer_t
	 * 
	 */
	timer_t tid;

public:
	/**
	 * @brief Construct a new Timer object
	 * 
	 */
	Timer();
	
	/**
	 * @brief Destroy the Timer object
	 * it is virtual because we have declared two functions virtual
	 */
	virtual ~Timer();	
	
	/**
	 * @brief starting the timer
	 * it is virtual in order to define it in the derivate classes
	 * @param duration_ms how much the timer will last
	 */
	virtual void start(double duration_ms);

	/**
	 * @brief stopping the timer
	 * 
	 */
	void stop();

protected:
	/**
	 * @brief handler function of the timer
	 * it is pure virtual since it will be different in each different time: virtual means that every class has to implement it on its own
	 * 
	 */
	virtual void callback() = 0;

private:
	/**
	 * @brief function that will call the handler function
	 * it is connected to the class and not to the objet
	 * @param si contains signal information
	 */
	static void call_callback(int, siginfo_t* si, void*); 
};


#endif
