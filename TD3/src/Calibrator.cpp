/**
 * @file Calibrator.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementing of Calibrator.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "Calibrator.h"
#include <iostream>
#include <math.h>

using namespace std;

Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples)
{
    cout << "Starting Calibration " << "\n";
    counter = nSamples;
    start(samplingPeriod_ms);       //start periodic timer
    looper.runLoop();
    regression(nSamples, &a,&b, samples, samplingPeriod_ms);
    cout << "End of Calibration " << "\n";    
}

double Calibrator::nLoops(double duration_ms)
{
    return a * duration_ms + b;    
}

void Calibrator::callback()
{
    counter--;

    if(counter == 0)
    {
        samples.push_back(looper.stopLoop());
        cout << "\n---STOPPING---\n";
        looper.stopLoop(); 
    }
    else{
        // cout << "The value of the counter is " << counter << "\n";
        samples.push_back(looper.getSample());
    } 
}

void Calibrator::regression(int numCalibs, double* a, double* b, vector<double> samples, double samplingPeriod_ms)
{
    double rMean = 0;
    double tMean =  samplingPeriod_ms*(numCalibs+1)/2;
    double t = 0;
    double tDeviation  = 0;
    double rtDeviation = 0;

    for(int i = 0; i < numCalibs; i++)
    {
        rMean += samples[i];
    } 
    
    rMean = rMean/numCalibs;

    for(int i = 0; i < numCalibs; i++)
    {
        t+=samplingPeriod_ms;
        tDeviation  += pow((t - tMean),2);
        rtDeviation += (samples[i]- rMean)*(t - tMean);
    }
    
    *a = rtDeviation/tDeviation;
    *b = rMean - *a*tMean;
}