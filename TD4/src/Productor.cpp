/**
 * @file Productor.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Productor.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include "Semaphore.h"
#include "TimeSpec.h"
#include "Productor.h"

using namespace std;

Productor::Productor(Semaphore *semaph, unsigned numItem) : semaphore(semaph)
{
    counter = 0;
    maxCount = numItem;
}

Productor::~Productor()
{
}

void Productor::run()
{
    for(unsigned i = 0; i < maxCount; i++)
    {
        semaphore->give();
        counter++;
    }
}

unsigned Productor::getCounter()
{
    return counter;
}