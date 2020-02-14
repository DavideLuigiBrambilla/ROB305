/**
 * @file CpuLoop.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of CpuLoop.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "CpuLoop.h"
#include <iostream>

using namespace std;

CpuLoop::CpuLoop(Calibrator& calibrator) : calibrator(calibrator)
{
    
}

void CpuLoop::runTime(double duration_ms)
{
    runLoop(calibrator.nLoops(duration_ms));
}
