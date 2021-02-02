#ifndef LEDblink_h
#define LEDblink_h
#include "Arduino.h"
#include "define.h"

class LEDblink
{
public:
    LEDblink(int pin);
    void chika_led1(int count_led1,int interval_led1);
    void chika_led2();
    void chika_led3();

private:
    int pin_num;
    int count_led1;
    int interval_led1;
    int count_led2;
    int interval_led2;
    int count_led3;
    int interval_led3;
};

#endif