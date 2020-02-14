/**
 * @file CpuLoopMutex.h
 * @author Davide Luigi Brambilla
 * @brief Class CpuLoopMutex that allows us to launch a thread CpuLoop to do cycles
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef CpLoopMutex_h_INCLUDED
#define CpLoopMutex_h_INCLUDED

#include "Calibrator.h"
#include "CpuLoop.h"
#include "Thread.h"
#include "Mutex.h"
#include "TimeSpec.h"

/**
 * @brief Class CpuLoopMutex that allows us to launch a thread CpuLoop to do cycles
 * 
 */
class CpuLoopMutex: public Thread
{
private:

	/**
	 * @brief Pointer towards an object CpuLoop
	 * 
	 */
	CpuLoop *loop;

	/**
	 * @brief Pointer towards the mutex object
	 * 
	 */
	Mutex *mutex;
	
	/**
	 * @brief priority of the thread in order to recognize it
	 * 
	 */
	int priority;
	
	/**
	 * @brief Execution Time of the Thread
	 * 
	 */
	double timeExecution;

	/**
	 * @brief Time between the start of the execution and the moment at which we ask the thread
	 * 
	 */
	double timeReqMutex;

	/**
	 * @brief Duration Time of the lock of the mutex
	 * 
	 */
	double timeLastMutex;
	
public:
	
	/**
	 * @brief Construct a new Cpu Loop Mutex object
	 * 
	 * @param l reference towards CpuLoop object
	 * @param policy policy of the thread
	 * @param prior priority of the thread
	 * @param m pointer towardsmutex 
	 * @param timeEx Execution time of the thread
	 * @param timeReqM Time between the start of the execution and the moment at which we ask the thread
	 * @param timeLastM Duration of the Lock
	 */
	CpuLoopMutex(CpuLoop *l, int policy, int prior, Mutex *m, double timeEx, double timeReqM, double timeLastM);
	
	/**
	 * @brief Destroy the Cpu Loop Mutex object
	 * 
	 */
	~CpuLoopMutex();
	
	/**
	 * @brief routine function -> it will be different if the thread has acces to mutex or not
	 * 
	 */
	void run();

};

#endif
