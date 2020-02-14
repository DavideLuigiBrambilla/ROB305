/**
 * @file main_td2a.cpp
 * @author Davide Luigi Brambilla
 * @brief Functions that create parallel processus in order to increment a counter
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
 * @brief Data structure that we will give the created thread composed by number of
 * loops to do and the value to increment
 * 
 */
struct Data
{
    unsigned int nLoop;
    double *counter;
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
    incr(pData->nLoop, pData->counter);
    return data;
}

/**
 * @brief main function
 * 
 * @param argv parameters to give at the moment of execution <nLoop> <nTasks>
 * @return int 
 */
int main(int, char* argv[])
{
    //getting the informations from the user
    unsigned int nLoop = stoi(argv[1]);
    unsigned nTasks = stoi(argv[2]);
    double counter = 0.0;
    pthread_t incrementThread[nTasks];
    volatile Data data = {nLoop, &counter};
    struct timespec timeBegin;
    struct timespec timeEnd;

    timeBegin = timespec_now();

    // Creation of the threads
    for(unsigned iThread = 0; iThread < nTasks; ++iThread)
    {
        pthread_create(&incrementThread[iThread], NULL, call_incr, (void*) &data);
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

/**
 * The counter value is often varying because the acces to the datas it is not the same.
 * We have that different threads have acces to the same zone of memory so we have to add
 * the mutex. Globalement we are going to have un sousestimation.because every thread is trying
 * to write the value at the same time: if we have 3 threads that writes 1000000 we are not going to
 * have 3000000 at the end but we are going to have less. So we have to add the parameter mutex.
 * MUTUAL EXCLUSION: the threads are excluded mutually in the acces to a resource. 
*/