/**
 * @file Consumer.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of Consumer.h
 * @version 0.1
 * @date 2019-12-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Semaphore.h"
#include "TimeSpec.h"
#include "Consumer.h"

using namespace std;

Consumer::Consumer(Semaphore *semaph): semaphore(semaph)
{
    counter = 0;
}

Consumer::~Consumer()
{

}

void Consumer::run()
{
    while(semaphore->take(1000))
    {
        counter++;
    }
}

unsigned Consumer::getCounter()
{
    return counter;
}
