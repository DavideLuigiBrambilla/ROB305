/**
 * @file main_td2b.cpp
 * @author Davide Luigi Brambilla
 * @brief Functions that create parallel processus in order to increment a counter with a order defined
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
 * loops to do and the value to increment
 * 
 */
struct Data
{
    unsigned int nLoop;
    double *counter;
};

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
    incr(pData->nLoop, pData->counter);
    return data;
}

/**
 * @brief main function
 * 
 * @param argv parameters to give at the moment of execution <nLoop> <nTasks> <policy>
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
    
    double counter = 0.0;
    pthread_t incrementThread[nTasks];
    volatile Data data = {nLoop, &counter};
    struct timespec timeBegin;
    struct timespec timeEnd;

    // Definition of the main priority
    struct sched_param schedParam;
    schedParam.sched_priority = sched_get_priority_max(schedPolicy);
    pthread_setschedparam(pthread_self(), schedPolicy, &schedParam);

    // Definition of the thread priority
    pthread_attr_t attr;
    struct sched_param	schedParams;
    int priority = rand()%100 + 1;                      //I get a number between 1 and 100
    if(priority == 100) priority = priority - 2;        //priority has to be in a range between 1 and 98
    schedParams.sched_priority = (schedPolicy == SCHED_OTHER) ? 0 : priority;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, schedPolicy);
    pthread_attr_setschedparam(&attr, &schedParams);
    
    timeBegin = timespec_now();

    // Creation of the threads
    for(unsigned iThread = 0; iThread < nTasks; ++iThread)
    {
        pthread_create(&incrementThread[iThread], &attr, call_incr, (void*)&data);
    }

    // Termination of the threads
    for(unsigned iThread = 0; iThread < nTasks; ++iThread)
    {
        pthread_join(incrementThread[iThread], NULL);
    }
    timeEnd = timespec_now();
    
    cout << "The value of counter is " << counter << "\n";
    
    cout << fixed << setprecision(9) << "The time taken by the operation is " << (timespec_to_ms(timeEnd-timeBegin)/1000) << " seconds\n";
    return 0;
}

/*The counter valeur de counter is often varying because the acces to the data it is not the same*/