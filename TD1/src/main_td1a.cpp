/**
 * @file main_td1a.cpp
 * @author Davide Luigi Brambilla
 * @brief main function to verify TimeSpec
 * @version 0.1
 * @date 2019-12-01
 * 
 */

#include"TimeSpec.h"
#include <iostream>

using namespace std;

int main()
{
    struct timespec t;
    struct timespec timeW;
    struct timespec timeVar;
    struct timespec timeVar2;
    struct timespec timeDel;   
    struct timespec timeVerif;   
    double time_d;

    //verification timespec_now() and timespec_to_ms 
    t = timespec_now();
    cout << "HelloWorld TimeSpec!\n Now it's Sec:" << t.tv_sec << "      Nsec: " << t.tv_nsec << "\n\n";

    cout << "HelloWorld ms! Now it's " << timespec_to_ms(t) << "\n\n";
   
    //verification timespec_from_ms
    timeVar.tv_sec = -3;
    timeVar.tv_nsec = 800000000;
    time_d = timespec_to_ms(timeVar); 
    cout << "Verification time_to_ms " << time_d << "\n";
    timeVar = timespec_from_ms(time_d); 
    cout << "Verification time_from_ms\n Sec:" << timeVar.tv_sec << "      Nsec: " << timeVar.tv_nsec << "\n\n";


    //verification negation 
    timeVerif = timespec_negate(timeVar);
    time_d = timespec_to_ms(timeVerif); 
    cout << "Negated time in ms is " << time_d << "\n\n";
    
    timeVar2.tv_sec = 3;
    timeVar2.tv_nsec = 600000000;

    cout << "timeVar  Sec:" << timeVar.tv_sec << "      Nsec: " << timeVar.tv_nsec << "\n\n";
    cout << "timeVar2 Sec:" << timeVar2.tv_sec << "      Nsec: " << timeVar2.tv_nsec << "\n\n";


    //verification time_add
    timeVerif = timespec_add(timeVar, timeVar2);
    cout << "Verification time_add\n Sec:" << timeVerif.tv_sec << "      Nsec: " << timeVerif.tv_nsec << "\n\n";

    //verification time_subtract
    timeVerif = timespec_subtract(timeVar, timeVar2);
    cout << "Verification time_subtract\n Sec:" << timeVerif.tv_sec << "      Nsec: " << timeVerif.tv_nsec << "\n\n";

    timeDel.tv_sec = 3;
    timeDel.tv_nsec = 100000000;

    //Verification timespec_wait
    timeW = timespec_wait(timeDel);

    //verification operators
    cout << "Verification operators\n";
    cout << "timeVar: sec:" << timeVar.tv_sec << "      Nsec: " << timeVar.tv_nsec << "\n \n";
    cout << "timeVar2: sec:" << timeVar2.tv_sec << "      Nsec: " << timeVar2.tv_nsec << "\n \n";
    
    //verification op-
    timeVerif = -timeVar;
    cout << "Verification op-\n Sec:" << timeVerif.tv_sec << "      Nsec: " << timeVerif.tv_nsec << "\n \n";    
    
    //verification op+
    timeVerif = timeVar + timeVar2;
    cout << "Verification op+\n Sec:" << timeVerif.tv_sec << "      Nsec: " << timeVerif.tv_nsec << "\n \n";    
    
    //verification op-
    timeVerif = timeVar - timeVar2;
    cout << "Verification op-\n Sec:" << timeVerif.tv_sec << "      Nsec: " << timeVerif.tv_nsec << "\n \n";
    
    //verification op+=
    timeVar += timeVar2;
    cout << "Verification op+=\n Sec:" << timeVar.tv_sec << "      Nsec: " << timeVar.tv_nsec << "\n \n";
    
    //verification op-=
    timeVar -= timeVar2;
    cout << "Verification op-=\n Sec:" << timeVar.tv_sec << "      Nsec: " << timeVar.tv_nsec << "\n \n";
    
    //verification op==
    cout << "Verification op==\n Value True:" << (timeVar == timeVar) << "      Value False " << (timeVar == timeVerif) << "\n \n";
    
    //verification op!=
    timeVar.tv_sec = timeVar2.tv_sec;
    timeVar.tv_nsec = timeVar2.tv_nsec;
    cout << "Verification op!=\n Value True:" << (timeVar != timeVerif) << "      Value False " << (timeVar != timeVar) << "\n \n";

    //verification op>
    timeVar.tv_sec = timeVar2.tv_sec + 1;
    timeVar.tv_nsec = timeVar2.tv_nsec + 1;
    cout << "Verification op>\n Value True:" << (timeVar > timeVar2) << "      Value False " << (timeVar2 > timeVar) << "\n \n";

    //verification op<
    timeVar.tv_sec = timeVar2.tv_sec - 1;
    timeVar.tv_nsec = timeVar2.tv_nsec - 1;
    cout << "Verification op<\n Value True:" << (timeVar < timeVar2) << "      Value False " << (timeVar2 < timeVar) << "\n \n";
    
    return 0;
}
