/**
 * @file main_td3a.cpp
 * @author Davide Luigi Brambilla
 * @brief main function : verifying that Chrono is working well
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "Chrono.h"
#include "TimeSpec.h"

#include <iostream>
#include <iomanip>
#include <unistd.h>

using namespace std;

/**
 * @brief main function: verifying that Chrono is working well: try on 6 seconds and comparaison with TimeSpec
 * 
 * @return int 
 */
int main()
{
    //timespec to verify
    struct timespec timeBegin;
    struct timespec timeEnd;
    
    // initializing of the object Chrono
    Chrono chrono;
    timeBegin = timespec_now();
    cout << "Sleeping for 6 seconds" << endl;
    sleep(6);

    chrono.stop();
    timeEnd = timespec_now();

    // verifying that the object is working well 
    cout << fixed << setprecision(9) << "The time measured by TimeSpec is " << (timespec_to_ms(timeEnd-timeBegin)/1000) << " seconds\n";
    cout << fixed << setprecision(9) << "The time measured by Chrono is " << (chrono.lap())/1000 << " seconds\n";
    return 0;
}
