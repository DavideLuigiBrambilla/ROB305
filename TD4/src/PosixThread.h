/**
 * @file PosixThread.h
 * @author Davide Luigi Brambilla
 * @brief PosixThread class that implements the basic functions of a Thread Posix
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#ifndef PosixThread_h_INCLUDED
#define PosixThread_h_INCLUDED

#include <pthread.h>
#include <exception>

using namespace std;

/**
 * @brief PosixThread class that implements the basic functions of a Thread Posix
 * 
 */
class PosixThread
{

public:
	/**
	 * @brief Exception of the thread - Not existing thread
	 * 
	 */
	class Exception : exception
	{
		public:		
			const char* launchingException() const noexcept;
	};
private:
	/**
	 * @brief Identificator of the thread
	 * 
	 */
	pthread_t posixId;
	
	/**
	 * @brief Attribute of the thread
	 * 
	 */
	pthread_attr_t posixAttr;
protected:

	/**
	 * @brief State of the Thread
	 * 
	 */
	bool isActive = false;
public:
	/**
	 * @brief Construct a new PosixThread object
	 * 
	 */
	PosixThread();
	
	/**
	 * @brief Construct a new PosixThread object based on an already present object
	 * 
	 * @param posixId Id of the already existing thread
	 */
	PosixThread(pthread_t posixId);

	/**
	 * @brief Destroy the PosixThread object
	 * 
	 */
	~PosixThread();

	/**
	 * @brief starting the trhead
	 * 
	 * @param threadFunc handler function of the thread
	 * @param threadArg arguments of the thread
	 */
	void start(void*(*threadFunc)(void*), void* threadArg);
	
	/**
	 * @brief terminate the Thread
	 * 
	 */
	void join();
	
	/**
	 * @brief terminate the thread with timedjoin
	 * 
	 * @param timeout_ms time that the join has to wait
	 * @return true : if it went well
	 * @return false : if there was an error
	 */
	bool join(double timeout_ms);
	
	/**
	 * @brief Set the policy and the priority of the current thread
	 * 
	 * @param schedPolicy policy to set to the current thread
	 * @param priority priority to set to the current thread
	 * @return true : if it went well
	 * @return false : if there was an error 
	 */
	bool setScheduling(int schedPolicy, int priority);
	
	/**
	 * @brief Get the policy and the priority of the current thread
	 * 
	 * @param pSchedPolicy pointer in order to store the policy value
	 * @param pPriority pointer in order to store the priority value
	 * @return true : if it went well
	 * @return false : if there was an error
	 */
	bool getScheduling(int* pSchedPolicy, int* pPriority);
};

#endif
