/**
 * @file main_td1c.cpp
 * @author Davide Luigi Brambilla
 * @brief 
 * @version 0.1
 * @date 2019-12-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "TimeSpec.h"

#include <iostream>
#include <string>
#include <iomanip> 

using namespace std;

/**
 * @brief Function used to increment the counter
 * 
 * @param nLoops number of loops that must be done
 * @param pCounter counter to be incremented
 */
void incr(unsigned int nLoops, double* pCounter)
{
    for(unsigned int iLoop=0; iLoop < nLoops; ++iLoop)
    {
        *pCounter += 1.0;
    }
}

/**
 * @brief main function
 * 
 * @param argv parameter given at the moment of execution
 * @return int 
 */
int main(int, char* argv[])
{
    //getting the number of loops from the user
    unsigned int nLoops = stoi(argv[1]); 
    double counter = 0.0;
    struct timespec timeBegin;
    struct timespec timeEnd;

    //starting the execution
    timeBegin = timespec_now();
    incr(nLoops, &counter);              // calling incr function in order to increment counter nLoops times
    timeEnd = timespec_now();

    //verification
    cout << "The value of counter is " << counter << "\n";
    
    cout << fixed << setprecision(9) << "The time taken by the operation is " << (timespec_to_ms(timeEnd-timeBegin)/1000) << " seconds\n";
    return 0;
}
