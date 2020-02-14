/**
 * @file main_td5.cpp
 * @author Davide Luigi Brambilla
 * @brief main function for TD5
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "CpuLoopMutex.h"

#include <iostream>

using namespace std;

int main() 
{
	//set that we will work only on a single CPU
	cpu_set_t  cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);

	//defining mutex with control on the inversion
	Mutex mutex(1);	

	Chrono chrono;

	//setting policy and priority
	int policy = SCHED_RR;
	int priorityA = 30;
	int priorityB = 20;
	int priorityC = 10;
	
	Calibrator calibrator(1000,5);
	CpuLoop loopA(calibrator);
	CpuLoop loopB(calibrator);
	CpuLoop loopC(calibrator);
		
	//Tread with mutex object Creation 
	CpuLoopMutex threadA(&loopA, policy, priorityA, &mutex, 4000, 1000, 2000);
	CpuLoopMutex threadB(&loopB, policy, priorityB, &mutex, 1000, -1, -1);
	CpuLoopMutex threadC(&loopC, policy, priorityC, &mutex, 5000, 2000, 2000);

	//Starting thread C and waiting for activating A and B
	cout << "Starting Thread C (priority 10)" << endl;
	threadC.start();
	timespec_wait(timespec_from_ms(3000));
	cout << "Starting Thread A (priority 30) and B (priority 20)" << endl;
	threadA.start();
	threadB.start();
		
	//Joining Threads
	threadA.join();
	threadC.join();
	threadB.join();
		
	chrono.stop();
	cout << "The thread A took " << threadA.execTime_ms()/1000 << " seconds" << endl;
	cout << "The thread B took " << threadB.execTime_ms()/1000 << " seconds" << endl;
	cout << "The thread C took " << threadC.execTime_ms()/1000 << " seconds" << endl;
	cout << "The time taken by the execution of the main is " << (chrono.lap()/1000) << " seconds\n";
	return 0;
}
