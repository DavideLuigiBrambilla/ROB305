/**
 * @file FifoConsumer.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of FifoConsumer.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "TimeSpec.h"
#include "FifoConsumer.h"

#include <iostream>
using namespace std;

FifoConsumer::FifoConsumer(Fifo<int> *fif) : fifo(fif)
{
    counter = 0;
}

FifoConsumer::~FifoConsumer()
{

}

void FifoConsumer::run()
{
    while(isActive)
    {
        try
        {
            fifo->pop(1000);
            counter++;
        }
        catch(const Fifo<int>::EmptyException& e)
        {
            std::cerr << e.launchingException() << '\n';
            isActive = false;
        }
    }
}

unsigned FifoConsumer::getCounter()
{
    return counter;
}
