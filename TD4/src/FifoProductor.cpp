/**
 * @file FifoProductor.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of FifoProductor.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "TimeSpec.h"
#include "FifoProductor.h"

using namespace std;

FifoProductor::FifoProductor(Fifo<int> *fif, unsigned numItem) : fifo(fif)
{
    counter = 0;
    maxCount = numItem;
}

FifoProductor::~FifoProductor()
{
}

void FifoProductor::run()
{
    for(unsigned i = 0; i < maxCount; i++)
    {
        fifo->push(i);
        counter++;
    }
}

unsigned FifoProductor::getCounter()
{
    return counter;
}