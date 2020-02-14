/**
 * @file main_td2c.cpp
 * @author Davide Luigi Brambilla
 * @brief Functions that create parallel processus in order to increment a counter
 * with a order defined and a mutex to handle the data access
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "TimeSpec.h"

#include <iostream>
#include <string>
#include <iomanip> 
#include <pthread.h>

using namespace std;

/**
 * @brief Data structure that we will give to the created thread composed by number of
 * loops to do, the value to increment, the protectionflag and the mutex
 * 
 */
struct Data
{
    unsigned int nLoop;
    double *counter;
    unsigned protection;
    pthread_mutex_t mutex;
};

/**
 * @brief Function handler thread: increment of counter
 * 
 * @param nLoops number of loops that has to be done
 * @param pCounter counter that has to be increased by the function
 */
void incr(unsigned int nLoops, double* pCounter)
{
    for(unsigned int iLoop=0; iLoop < nLoops; ++iLoop)
    {
        *pCounter += 1.0;
    }
}

/**
 * @brief  function of type void* that will be passed at the moment of creation of the thread
 * 
 * @param data data that will be treated by the thread
 * @return void* 
 */
void* call_incr(void* data)
{
    Data* pData = (Data*) data;
    if(pData->protection){
        pthread_mutex_lock(&pData->mutex);
    }
    incr(pData->nLoop, pData->counter);
    if(pData->protection){
        pthread_mutex_unlock(&pData->mutex);
    }
    return data;
}

/**
 * @brief main function
 * 
 * @param argv parameters to give at the moment of execution <nLoop> <nTasks> <policy> <protected>
 * @return int 
 */
int main(int, char* argv[])
{
    //getting the informations from the user
    unsigned int nLoop = stoi(argv[1]);
    unsigned nTasks = stoi(argv[2]);
    
    int schedPolicy;
    if(string(argv[3]) == "SCHED_RR") schedPolicy = SCHED_RR;               
    else if(string(argv[3]) == "SCHED_FIFO") schedPolicy = SCHED_FIFO;      
    else schedPolicy = SCHED_OTHER;

    unsigned protection;
    if(string(argv[4]) == "protected")
    {
        protection = 1;
    }
    else
    {
        protection = 0;
    }
    pthread_mutex_t mutex;
    double counter = 0.0;
    pthread_t incrementThread[nTasks];
    Data data = {nLoop, &counter, protection, mutex};
    pthread_mutex_init(&data.mutex, NULL);
    struct timespec timeBegin;
    struct timespec timeEnd;
    
    // Definition of the main priority
    struct sched_param schedParam;
    schedParam.sched_priority = sched_get_priority_max(schedPolicy);
    pthread_setschedparam(pthread_self(), schedPolicy, &schedParam);

    // Definition of the thread priority
    pthread_attr_t attr;
    struct sched_param	schedParams;
    int priority = rand()%100 + 1;                      // I get a number between 1 and 100
    if(priority == 100) priority = priority - 2;        // priority has to be in a range between 1 and 98 since 99 is the priority of the main
    schedParams.sched_priority = (schedPolicy == SCHED_OTHER) ? 0 : priority;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, schedPolicy);
    pthread_attr_setschedparam(&attr, &schedParams);

    timeBegin = timespec_now();

    // Creation of the threads
    for(unsigned iThread = 0; iThread < nTasks; ++iThread){
        pthread_create(&incrementThread[iThread], &attr, call_incr, (void*)&data);
    }
    
    // Termination of the threads
    for(unsigned iThread = 0; iThread < nTasks; ++iThread){
        pthread_join(incrementThread[iThread], NULL);
    }

    pthread_mutex_destroy(&data.mutex);
    timeEnd = timespec_now();
    
    cout << "The value of counter is " << counter << "\n";
    
    cout << fixed << setprecision(9) << "The time taken by the operation is " << (timespec_to_ms(timeEnd-timeBegin)/1000) << " seconds\n";
    return 0;
}
