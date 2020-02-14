/**
 * @file CountDown.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementation of CountDon.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "CountDown.h"
#include <iostream>

using namespace std;

CountDown::CountDown(int n)
{
    count = n;
}

int CountDown::getCount()
{
    return count;
}

void CountDown::callback()
{
    --count;
    cout << "The value of the counter is " << count << "\n";

    if(count == 0)
    {
        cout << "\n---STOPPING---\n";
        CountDown::stop();
    }
}