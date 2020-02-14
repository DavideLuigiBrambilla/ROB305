/**
 * @file main_td3b.cpp
 * @author Davide Luigi Brambilla
 * @brief main function in order to create an object countdown and veridy that works properly
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "TimeSpec.h"
#include "CountDown.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip> 

/**
 * @brief main function in order to create an object countdown and veridy that works properly
 * 
 * @return int 
 */
int main()
{
    //verifying countdown
    CountDown countDown(6);
    countDown.start(1000);

    while (countDown.getCount() > 0)
    {
		}

    return 0;
}
