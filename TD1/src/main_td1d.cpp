/**
 * @file main_td1d.cpp
 * @author Davide Luigi Brambilla
 * @brief functions to calculate the calibration and verification in the main
 * The aim is to estimate the number of loops r given a time t by : r = a*t + b
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "TimeSpec.h"
#include "SignalHandler.h"

#include <iostream>
#include <string>
#include <iomanip> 
#include <climits>

using namespace std;

/**
 * @brief Increment function with the stop condition too
 * 
 * @param nLoops number of Loops to be executed
 * @param pCounter pointer towards the value that has to be incrementer
 * @param pStop boolean stop condition
 * @return unsigned - number of loops done 
 */
unsigned incr(unsigned int nLoops, double* pCounter, volatile bool* pStop)
{
    unsigned int realLoops = 0;
    for(unsigned int iLoop=0; iLoop < nLoops && *pStop == false; ++iLoop)
    {
        *pCounter += 1.0;
        realLoops += 1; 
    }
    return realLoops;
}

/**
 * @brief estimating a et b from two samples (two times t and two loops r)
 * 
 * @param a a parameter
 * @param b b parameter
 * @param r1 first sample on the number of loops
 * @param r2 second sample on the number of loops
 * @param t1 first sample on the time
 * @param t2 second sample on the time
 */
void calib (double* a, double* b, double r1, double r2, double t1, double t2)
{
    *b = (t1*r2-r1*t2)/(t1-t2);
    *a = (r1 - *b)/t1;
}


/**
 * @brief main training function with two timers of 4 and 6 seconds and verification on 5 seconds 
 * 
 * @return int 
 */
int main()
{
    unsigned int nLoops = UINT_MAX;
    double counter = 0.0;
    bool stop = false;
    struct timespec timeBegin;
    struct timespec timeStart;
    struct timespec timeEnd;
    struct timespec timeElapsed[3];  //that will store the time elapsed for 4sec, 6sec and 5sec
    unsigned int realLoops[3];  //that will store the number of loops for 4sec, 6sec and 5sec
    double a, b; 
    itimerspec its;
    timer_t tid;
    double r1, r2, t1, t2;
    
    timeBegin = timespec_now();

    // 4 seconds timing
    cout << "--- Samples for 4sec case ---" << endl;
    its.it_value.tv_sec = 4;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    tid = init_signal(SIGRTMIN, myHandler, (void*) &stop); //we have to specify a cast towards void*
    timer_settime(tid, 0, &its, NULL);
    timeStart = timespec_now();
    realLoops[0] = incr(nLoops, &counter, &stop);
    timeEnd = timespec_now();
    timeElapsed[0] = timeEnd - timeStart;
    timer_delete(tid);
    r1 = realLoops[0];
    t1 = timespec_to_ms(timeElapsed[0])/1000;
    
    //6 seconds timing
    cout << "--- Samples for 6sec case ---" << endl;
    stop = false;
    its.it_value.tv_sec = 6;
    tid = init_signal(SIGRTMIN, myHandler, (void*) &stop);
    timer_settime(tid, 0, &its, NULL);
    timeStart = timespec_now();
    realLoops[1] = incr(nLoops, &counter, &stop);
    timeEnd = timespec_now();
    timeElapsed[1] = timeEnd - timeStart;
    timer_delete(tid);
    r2 = realLoops[1];
    t2 = timespec_to_ms(timeElapsed[1])/1000;

    //Calling of Calibration in order to estimate a and b
    calib(&a, &b, r1, r2, t1, t2);


    // verification of the estimation given by calib for 5 seconds
    cout << "--- Test with 5sec case ---" << endl;
    stop = false;
    its.it_value.tv_sec = 5;
    tid = init_signal(SIGRTMIN, myHandler, (void*) &stop); 
    timer_settime(tid, 0, &its, NULL);
    timeStart = timespec_now();
    realLoops[2] = incr(nLoops, &counter, &stop);
    timer_delete(tid);
    timeEnd = timespec_now();
    timeElapsed[2] = timeEnd - timeStart;


    timeEnd = timespec_now();

    // displaying information
    cout << "The three times elapsed are " << timespec_to_ms(timeElapsed[0])/1000 << " sec    " << timespec_to_ms(timeElapsed[1])/1000 << " sec    " << timespec_to_ms(timeElapsed[2])/1000  << " sec\n\n\n";

    cout << "The real number of Loop is " << realLoops[2]  << "\n";

    cout << fixed << setprecision(9) << "The number of Loop estimated by calib is " << a * timespec_to_ms(timeElapsed[2])/1000 + b << "\n";
    
    cout << "The error is " << abs(realLoops[2] - (a * timespec_to_ms(timeElapsed[2])/1000 + b)) << "\n";
    
    cout << "The error in percentage is " << (abs(realLoops[2] - (a * timespec_to_ms(timeElapsed[2])/1000 + b))/realLoops[2]) * 100 << "%\n";

    cout << fixed << setprecision(9) << "\n\n\nThe time taken by all the operations is " << (timespec_to_ms(timeEnd-timeBegin)/1000) << " seconds\n";
    return 0;
}
