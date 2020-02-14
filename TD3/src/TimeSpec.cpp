/**
 * @file TimeSpec.cpp
 * @author Davide Luigi Brambilla
 * @brief Implementing TimeSpec.h
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#include "TimeSpec.h"
#include <math.h>
#include <cerrno>

double timespec_to_ms(const timespec& time_ts)
{ 
    return time_ts.tv_sec*1e3 + time_ts.tv_nsec/1e6;               
}


timespec timespec_from_ms(double time_ms)
{
    struct timespec time_ts;
    time_ts.tv_sec = (time_ms >= 0) ? time_ms/1e3 : time_ms/1e3-1;  // handle the case if timespec is positive or negative
    time_ts.tv_nsec = (time_ms - time_ts.tv_sec*1e3) * 1e6;         // remaining time transformed in nanoseconds
    return time_ts; 
}

timespec timespec_now()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);                            // get the current time
    return now;
}

timespec timespec_negate(const timespec& time_ts)
{
    struct timespec time_neg;                                       
    time_neg.tv_sec = -(time_ts.tv_sec + 1);                        // transform the timespec into negative time
    time_neg.tv_nsec = 1e9 - time_ts.tv_nsec;
    return time_neg;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
    struct timespec time_sum;                                       
    time_sum.tv_sec = time1_ts.tv_sec + time2_ts.tv_sec;            // adding two variables timespec
    if(time1_ts.tv_nsec + time2_ts.tv_nsec >= 1e9){                 // handle the case if the sum between nanoseconds gives more than 1 second
        time_sum.tv_sec += 1;
        time_sum.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec - 1e9;
    }
    else{
        time_sum.tv_nsec = time1_ts.tv_nsec + time2_ts.tv_nsec;
    }
    return time_sum;
}

timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts)
{
    struct timespec time_sub;
    time_sub.tv_sec = time1_ts.tv_sec - time2_ts.tv_sec;            // subtracting two variables timespec
    if(time1_ts.tv_nsec - time2_ts.tv_nsec < 0)                     // handle the case if the subtraction between nanoseconds becomes negative
    {
        time_sub.tv_sec -= 1;
        time_sub.tv_nsec =  1e9 - abs(time1_ts.tv_nsec - time2_ts.tv_nsec);
    }
    else
    {
        time_sub.tv_nsec = time1_ts.tv_nsec - time2_ts.tv_nsec;
    }
    return time_sub;
}

timespec timespec_wait(const timespec& delay_ts)
{
    struct timespec remaining;                                      
    if(nanosleep(&delay_ts, &remaining) == -1)                      //handle the case if the wait is interrupted and it still remains some time
    {
        if(errno == EINTR)
        {
            timespec_wait(remaining);
        }
    }
    return remaining;
}

timespec  operator- (const timespec& time_ts)                       // polymorphism of the negative operator -
{
    return timespec_negate(time_ts);
}

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)    // polymorphism of the sum operator +
{
    return timespec_add(time1_ts, time2_ts);
}

timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)    // polymorphism of the difference operator -
{
    return timespec_subtract(time1_ts, time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)          // polymorphism of the sum operator +=
{
    time_ts = timespec_add(time_ts, delay_ts);
    return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)          // polymorphism of the sum operator -=
{
    time_ts = timespec_subtract(time_ts, delay_ts); 
    return time_ts;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts)        // polymorphism of the equal condition operator ==
{
    return (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec == time2_ts.tv_nsec);
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)        // polymorphism of the not equal condition operator ==
{
    return (time1_ts.tv_sec != time2_ts.tv_sec || time1_ts.tv_nsec != time2_ts.tv_nsec);
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)          // polymorphism of the smaller condition operator <
{
    return (time1_ts.tv_sec < time2_ts.tv_sec || (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec < time2_ts.tv_nsec));
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)          // polymorphism of the smaller condition operator >
{
    return (time1_ts.tv_sec > time2_ts.tv_sec || (time1_ts.tv_sec == time2_ts.tv_sec && time1_ts.tv_nsec > time2_ts.tv_nsec));
}