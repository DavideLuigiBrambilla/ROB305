/**
 * @file TimeSpec.h
 * @author Davide Luigi Brambilla
 * @brief functions used to handle easily the timespec type
 * @version 0.1
 * @date 2019-12-01
 * 
 */
#ifndef TimeSpec_h_INCLUDED
#define TimeSpec_h_INCLUDED
#include <time.h>

/**
 * @brief  transformation from timespec (seconds and nanoseconds) to seconds 
 * 
 * @param time_ts time to convert in ms
 * @return double : time in ms
 */
double timespec_to_ms(const timespec& time_ts);

/**
 * @brief transformation from ms to seconds
 * 
 * @param time_ms time to convert in timespec
 * @return timespec : time in timespec
 */
timespec timespec_from_ms(double time_ms);

/**
 * @brief get the current time
 * 
 * @return timespec : time now in timespec
 */
timespec timespec_now();

/**
 * @brief negate the timespec time
 * 
 * @param time_ts 
 * @return timespec : negated time
 */
timespec timespec_negate(const timespec& time_ts);

/**
 * @brief adding two timespec
 * 
 * @param time1_ts first timespec operand
 * @param time2_ts second timespec operand
 * @return timespec : result of the operation
 */
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief subtracting two timespec
 * 
 * @param time1_ts first timespec operand
 * @param time2_ts second timespec operand
 * @return timespec : result of the operation
 */
timespec timespec_subtract(const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief waiting for a time defined as timespec
 * 
 * @param delay_ts timespec that we have to wait
 * @return timespec : remaining time to wait
 */
timespec timespec_wait(const timespec& delay_ts);

/**
 * @brief polymorphism of the operator negation
 * 
 * @param time_ts time to negate
 * @return timespec : result of the operation
 */
timespec  operator- (const timespec& time_ts);

/**
 * @brief polymorphism of the operator add +
 * 
 * @param time1_ts first element of the operation
 * @param time2_ts second element of the operation
 * @return timespec : result of the operation
 */
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief polymorphism of the operator subtraction -
 * 
 * @param time1_ts first element of the operation
 * @param time2_ts second element of the operation
 * @return timespec : result of the operation
 */
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief polymorphism of the operator add +=
 * 
 * @param time_ts first element of the operation
 * @param delay_ts second element of the operation
 * @return timespec& : result of the operation
 */
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);

/**
 * @brief polymorphism of the operator subtraction -=
 * 
 * @param time_ts first element of the operation
 * @param delay_ts second element of the operation
 * @return timespec& : result of the operation
 */
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);

/**
 * @brief polymorphism of the equal condition ==
 * 
 * @param time1_ts first element of the operation
 * @param time2_ts second element of the operation
 * @return true if is equal
 * @return false if is not equal
 */
bool operator== (const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief polymorphism of the notequal condition !=
 * 
 * @param time1_ts first element of the operation
 * @param time2_ts second element of the operation
 * @return true if is different
 * @return false if is equal
 */
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief polymorphism of the smaller condition <
 * 
 * @param time1_ts first element of the operation
 * @param time2_ts second element of the operation
 * @return true if time1_ts is smaller than time2_ts
 * @return false if time1_ts in not smaller that time2_ts
 */
bool operator< (const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief polymorphism of the bigger condition >
 * 
 * @param time1_ts first element of the operation
 * @param time2_ts second element of the operation
 * @return true if time1_ts is bigger than time2_ts
 * @return false if time1_ts is not bigger than time2_ts
 */
bool operator> (const timespec& time1_ts, const timespec& time2_ts);

#endif
