/**
 * @file mains_td1e.cpp
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
#include <cmath>

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
 * @brief function that gives the possibility to calculate a and b from different measures usign the linear regression formula
 * 
 * @param numCalibs number of calibration to be done
 * @param a regression coefficient of the line that will approximate the number of loops
 * @param b constant coefficient to be added in order to estimate the number of loops
 * @param r array of number of loops
 * @param t array of time
 */
void regression (int numCalibs, double* a, double* b, double r[], double t[])
{
    double rMean = 0;
    double tMean = 0;

    double tDeviation  = 0;
    double rtDeviation = 0;

    for(int i = 0; i < numCalibs; i++)
    {
        rMean += r[i];
        tMean += t[i];
    } 
    
    rMean = rMean/numCalibs;
    tMean = tMean/numCalibs;
    
    for(int i = 0; i < numCalibs; i++)
    {
        tDeviation  += pow((t[i] - tMean),2);
        rtDeviation += (r[i] - rMean)*(t[i] - tMean);
    }
    
    *a = rtDeviation/tDeviation;
    *b = rMean - *a*tMean;
}

/**
 * @brief Function that initialize different timers in order to calculate the samples for
 * regression: number of loops and times
 * 
 * @param time duration of the timer
 * @param r number of loops that are executed by the timer
 * @param t time taken by the timer
 */
void runtimer (int time, double* r, double* t)
{
    unsigned int nLoops = UINT_MAX;
    bool stop = false;
    double counter = 0.0;
    struct timespec timeStart;
    struct timespec timeEnd;
    struct timespec timeElapsed;
    itimerspec its;
    timer_t tid;
    unsigned int realLoops; 
    its.it_value.tv_sec = time;
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    tid = init_signal(SIGRTMIN, myHandler, (void*) &stop); 
    timer_settime(tid, 0, &its, NULL);
    timeStart = timespec_now();
    realLoops = incr(nLoops, &counter, &stop);
    timeEnd = timespec_now();
    timeElapsed = timeEnd - timeStart;
    timer_delete(tid);
    *r = realLoops;
    *t = timespec_to_ms(timeElapsed)/1000;
}
    
/**
 * @brief Calibration function that will run more timers 
 * in order to have more samples and call regression to calculate a and b
 * 
 * @param numCalibs number of calibration done
 * @param a a parameter
 * @param b b parameter
 */
void calib (int numCalibs, double* a, double* b)
{
    double r[numCalibs];                        
    double t[numCalibs];
    for(int i = 0; i < numCalibs; i++)
    {
        cout << "Calib num " << i+1 << endl;
        runtimer(i+1, &r[i], &t[i]);        // we will save all the values given by the timers initialised
    }

    regression(numCalibs, a, b, r, t);
}


/**
 * @brief main function to verify that the estimation has a good accuracy 
 * 
 * @return int 
 */
int main()
{
    struct timespec timeBegin;
    struct timespec timeEnd;
    double a = 0, b = 0; 
    double r = 0, t = 0;
    int numCalibs = 5;
    
    timeBegin = timespec_now();
    
    calib(numCalibs, &a, &b);

    cout << "Calibration done!\n\n";
    //verification of the estimation given by calib
    runtimer(5, &r, &t);

    timeEnd = timespec_now();

    cout << "\nThe time elapsed is " << t << "sec\n";

    cout << fixed << setprecision(9) << "The real number of Loop is " << r  << "\n";

    cout << fixed << setprecision(9) << "The number of Loop estimated by calib is " << a * t + b << "\n";
    
    cout << "The error is " << abs(r - (a * t + b)) << "\n";

    cout << "The error in percentage is " << (abs(r - (a * t + b))/r)*100 << "%\n";

    cout << "The accuracy is " << (1 - (abs(r - (a * t + b))/r))*100 << "%\n";

    cout << fixed << setprecision(9) << "\nThe time taken by all the operations is " << (timespec_to_ms(timeEnd-timeBegin)/1000) << " seconds\n";
    return 0;
}
