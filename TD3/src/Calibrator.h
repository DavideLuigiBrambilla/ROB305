/**
 * @file Calibrator.h
 * @author Davide Luigi Brambilla
 * @brief Calibrator class that permits to get an estimation about the number of loops done given a certain time
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef Calibrator_h_INCLUDED
#define Calibrator_h_INCLUDED
#include "Looper.h"
#include "PeriodicTimer.h"

#include <vector>

/**
 * @brief Calibrator class that derives from PeriodicTimer permits to get an estimation about the number of loops done given a certain time
 * 
 */
class Calibrator : public PeriodicTimer
{
private:
	/**
	 * @brief the slope of our estimation
	 * 
	 */
	double a;

	/**
	 * @brief the constant coefficient of our estimation
	 * 
	 */
	double b;

	/**
	 * @brief the vector of samples obtained from different training timer
	 * 
	 */
	std::vector<double> samples;
	
	/**
	 * @brief looper object that permits to have more cycles in order ot have different calibrations
	 * 
	 */
	Looper looper;

public:
	
	/**
	 * @brief Construct a new Calibrator object
	 * 
	 * @param samplingPeriod_ms duration time of our calibrations
	 * @param nSamples number of times that the single calibration will be made
	 */
	Calibrator(double samplingPeriod_ms, unsigned nSamples);
	
	/**
	 * @brief Calculate the estimated number of loops given a time
	 * 
	 * @param duration_ms time on which we want ot estimate the number of loops
	 * @return double : the numbers of loops estimated
	 */
	double nLoops(double duration_ms);

protected:
	/**
	 * @brief handler function of the calibator
	 * 
	 * 
	 */
	void callback();

private:
	/**
	 * @brief counter used to stop the calibration when the requested number of calibrations is made
	 * 
	 */
	int counter;
	
	/**
	 * @brief linear regression function used to caulculate the a value and the b value
	 * 
	 * @param numCalibs number of calibrations that are made
	 * @param a the slope of our estimation that has to be calculated
	 * @param b the constant coefficient of our estimation that has to be calculated
	 * @param samples vector containing the samples on which we will base our estimation
	 * @param samplingPeriod_ms duration of a calibration
	 */
	void regression(int numCalibs, double* a, double* b, std::vector<double> samples, double samplingPeriod_ms);
};


#endif
