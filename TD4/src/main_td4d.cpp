/**
 * @file main_td4d.cpp
 * @author Davide Luigi Brambilla
 * @brief main function in order to test the production and the remotion of object T by different threads
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "Fifo.hpp"
#include "FifoProductor.h"
#include "FifoConsumer.h"
#include "TimeSpec.h"

#include <iostream>
#include <string>
#include <vector> 

using namespace std;


/**
 * @brief main function in order to test the production and the remotion of object T by different threads
 * 
 * @param argv arguments that have to be given at the moment of the execution
 * @return int 
 */
int main(int, char* argv[])
{
    //getting the informations from the user
    unsigned nProd = stoi(argv[1]);
    unsigned nCons = stoi(argv[2]);
    unsigned nItems = stoi(argv[3]);
    Fifo<int> fifo;
    double opTimeProd = 0;
    double opTimeCons = 0;
    unsigned prod = 0;
    unsigned cons = 0;
    
    Chrono chrono;
    
    vector<FifoProductor> productors(nProd, FifoProductor(&fifo, nItems));

    vector<FifoConsumer> consumers(nCons, FifoConsumer(&fifo));

    //starting productors threads
    for (FifoProductor &productor : productors)
    {
        productor.start();
    }
    
    //starting consumer threads
    for (FifoConsumer &consumer : consumers)
    {
        consumer.start();
    }

    //joining cproductor threads
    for (FifoProductor &productor : productors)
    {
        productor.join();
        opTimeProd += productor.execTime_ms();
        prod += productor.getCounter();
    }

    //joining cproductor threads
    for (FifoConsumer &consumer : consumers)
    {
        consumer.join();
        opTimeCons += consumer.execTime_ms();
        cons += consumer.getCounter();
    }
  
    chrono.stop();
    
    cout << "The time taken by all the productors is " << (opTimeProd/1000) << " seconds\n";

    cout << "The time taken by all the consumers is " << (opTimeCons/1000) << " seconds\n";

    cout << "The number of item produced is " << prod << "\n";

    cout << "The number of item consumed is " << cons << "\n";

    if(prod == cons)
    {
        cout << "The same number of item has been produced and consumed \n";
    }
    else
    {
    cout << "----ERROR----\nThe number of item that has been produced and consumed is different\n";
    }

    cout << "The time taken by the execution of the main is " << (chrono.lap()/1000) << " seconds\n";
    return 0;
}
