#include "Arduino.h"
#include "define.h"
#include "LEDblink.h"

LEDblink::LEDblink(int pin)
{
    pinMode(pin, OUTPUT);
    pin_num = pin;
}

void LEDblink::chika_led1(int,int)
{
    for (int i = 0; i < count_led1; i++)
    {
        delay(interval_led1);
        digitalWrite(pin_num, HIGH);
        delay(interval_led1);
        digitalWrite(pin_num, LOW);
    }
}
void LEDblink::chika_led2()
{
    digitalWrite(pin_num, HIGH);
    delay(250);
    digitalWrite(pin_num, LOW);
    delay(250);
}
void LEDblink::chika_led3()
{
    digitalWrite(pin_num, HIGH);
    delay(250);
    digitalWrite(pin_num, LOW);
    delay(250);
}