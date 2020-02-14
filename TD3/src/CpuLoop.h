/**
 * @file CpuLoop.h
 * @author Davide Luigi Brambilla
 * @brief Implementation of the class CpuLoop that will derive from Looper and will make a calibration given a time
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef CpuLoop_h_INCLUDED
#define CpuLoop_h_INCLUDED

#include "Calibrator.h"
#include "Looper.h"

/**
 * @brief Implementation of the class CpuLoop that will derive from Looper and will make a calibration given a time
 * 
 */
class CpuLoop : public Looper
{
private:
	/**
	 * @brief reference on a calibrator object
	 * 
	 */
	Calibrator &calibrator;
public:
	/**
	 * @brief Construct a new CpuLoop object
	 * 
	 * @param calibrator object that initialise the calibrator object
	 */
	CpuLoop(Calibrator& calibrator);

	/**
	 * @brief runs the Looper objet given a time
	 * 
	 * @param duration_ms time that the Looper will have to run
	 */
	void runTime(double duration_ms);
};


#endif
