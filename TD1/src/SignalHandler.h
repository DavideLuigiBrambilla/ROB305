/**
 * @file SignalHandler.h
 * @author Davide Luigi Brambilla
 * @brief Functions to handle the creation of a timer Posix
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef SignalHandler_h_INCLUDED
#define SignalHandler_h_INCLUDED
#include <time.h>
#include <signal.h>

/**
 * @brief define the header of the handler function
 * 
 */
typedef void (*handler_t)(int, siginfo_t* si, void*);

/**
 * @brief Implementation of the handler function of the timer
 * 
 * @param sig number associated to the signal
 * @param si contains signal information
 */
void myHandler(int sig, siginfo_t* si, void*);

/**
 * @brief function to initialiser a signal : in our case timer
 * 
 * @param sig number associated to the signal
 * @param myHandler handler function
 * @param myData data to give to the signal
 * @return timer_t : the timer initialised
 */
timer_t init_signal(int sig, handler_t myHandler, void* myData);

#endif
