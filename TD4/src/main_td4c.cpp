/**
 * @file main_td4c.cpp
 * @author Davide Luigi Brambilla
 * @brief main function to verify that all the items produced are consumed
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "Semaphore.h"
#include "Productor.h"
#include "Consumer.h"
#include "TimeSpec.h"

#include <iostream>
#include <string>
#include <vector> 

using namespace std;

/**
 * @brief main function to verify that all the items produced are consumed
 * 
 * @param argv arguments given at the moment of execution
 * @return int 
 */
int main(int, char* argv[])
{
    //getting the informations from the user
    unsigned nProd = stoi(argv[1]);
    unsigned nCons = stoi(argv[2]);
    unsigned nItems = stoi(argv[3]);
    Semaphore semaphore;
    double opTimeProd = 0;
    double opTimeCons = 0;
    unsigned prod = 0;
    unsigned cons = 0;
    
    Chrono chrono;
    
    vector<Productor> productors(nProd, Productor(&semaphore, nItems));

    vector<Consumer> consumers(nCons, Consumer(&semaphore));

    //setting the priority and the policy of the first consumer
    consumers[0].setScheduling(0,0);
    
    //creating productors
    for (Productor &productor : productors)
    {
        productor.start();
    }
    
    //creating consumers
    for (Consumer &consumer : consumers)
    {
        consumer.start();
    }

    //joining the productors
    for (Productor &productor : productors)
    {
        productor.join();
        opTimeProd += productor.execTime_ms();  //total time if they were in series
        prod += productor.getCounter();
    }

    //joining the conumers
    for (Consumer &consumer : consumers)
    {
        consumer.join();
        opTimeCons += consumer.execTime_ms();   //total time if they were in series
        cons += consumer.getCounter();
    }
  
    chrono.stop();
    
    //verification
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

    cout << "The time taken by the execution of the main is " << (chrono.lap())/1000 << " seconds\n";
    return 0;
}
