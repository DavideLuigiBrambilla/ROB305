/**
 * @file main_td3c.cpp
 * @author Davide Luigi Brambilla
 * @brief main function to test calibration
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "Calibrator.h"
#include "CpuLoop.h"
#include "Chrono.h"

#include <iostream>
#include <string>
#include <iomanip> 

using namespace std;

/**
 * @brief main function to test the calibration
 * 
 * @return int 
 */
int main()
{
    //initialising the Calibrator and the CpuLoop object
    Calibrator calibrator(1000, 10);        // init calibrator

    CpuLoop	loop(calibrator);               // initialize loop

    int time = 2000;
    Chrono chrono;
    loop.runTime(time);                     // runtime
    chrono.stop();

    // Verification
    cout << fixed << "The real number of Loop is " << loop.getSample()  << "\n";

    cout << fixed << setprecision(9) << "The number of Loop estimated by calib is " <<  calibrator.nLoops(time) << "\n";
    
    cout << "The error is " << abs(loop.getSample() - calibrator.nLoops(time)) << "\n";

    cout << "The accuracy is " << (1 - (abs(loop.getSample() - calibrator.nLoops(time))/loop.getSample()))*100 << "%\n";

    cout << fixed << setprecision(9) << "\nThe time taken by all the operations is " << chrono.lap()/1000 << " seconds\n";
    return 0;
}
