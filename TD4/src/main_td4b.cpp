/**
 * @file main_td4b.cpp
 * @author Davide Luigi Brambilla
 * @brief implementation of the main function
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "IncrMutex.h"
#include "TimeSpec.h"

#include <iostream>
#include <string>
#include <vector> 

using namespace std;

/**
 * @brief 
 * 
 * @param argv parameters that has to inserted at the moment of execution
 * @return int 
 */
int main(int, char* argv[])
{
    //getting the informations from the user
    unsigned int nLoop = stoi(argv[1]);
    unsigned int nThreads = stoi(argv[2]);
    volatile double counter = 0.0;
    double opTime = 0;
    Mutex mutex;
    
    int schedPolicy;
    if(string(argv[3]) == "SCHED_RR") schedPolicy = SCHED_RR;               //it needs sudo in the execution
    else if(string(argv[3]) == "SCHED_FIFO") schedPolicy = SCHED_FIFO;      //it needs sudo in the execution
    else schedPolicy = SCHED_OTHER;

    Chrono chrono;
    
    vector<IncrMutex> threads(nThreads, IncrMutex(nLoop, &counter, schedPolicy, &mutex));
    
    //starting threads
    for (IncrMutex &thread : threads)
    {
        if(thread.start())
        {
            cout << "Thread started properly \n";
        }
        else
        {
            cout << "Thread already started!";
        }
    }

    //joining threads
    for (IncrMutex &thread : threads)
    {
        thread.join();
        opTime += thread.execTime_ms();
    }
    
    chrono.stop();
    //verification   
    cout << "The value of counter is " << counter << "\n";
    
    cout << "The time taken by all the threads is " << (opTime/1000) << " seconds\n";

    cout << "The time taken by the execution of the main is " << (chrono.lap())/1000 << " seconds\n";
    return 0;
}
