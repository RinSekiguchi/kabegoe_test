#include <Arduino.h>
#include "RoboClaw.h"
#include <Mstimer2.h>
#include "define.h"
#include <HardwareSerial.h>
#include "LEDblink.h"

RoboClaw MD(&SERIAL_ROBOCLAW, 1);
LEDblink Lchika(LED1);

bool flag_10ms = false;
int print_count = 0;
int s_count = 0;
int s_count1 = 0;
int y = 0;
int w = 0;
int u = 0;
int d = 0;
int r = 0;
int l = 0;

int pre_y = 0;
int y_count = 0;

//void enccount(uint8_t status1, uint8_t status2, bool vailed1, bool vailed2)
void enccount(void)
{
  bool valid1, valid3;
  uint8_t status1, status3;
  int32_t enc1 = MD.ReadEncM1(ADD, &status1, &valid1);
  int32_t speed1 = MD.ReadSpeedM1(ADD, &status3, &valid3);
  if (valid1)
  {
    digitalWrite(LED1, HIGH);
    Serial.print("Encoder1:");
    Serial.print(enc1, DEC);
    Serial.print(" ");
  }
  else
  {
    Serial.print("invalid");
  }
  if (valid3)
  {
    digitalWrite(LED2, HIGH);
    Serial.print("Speed1:");
    Serial.print(speed1, DEC);
    Serial.print(" ");
  }
  else
  {
    Serial.print("invalid");
  }
  Serial.println();
}

void timer_warikomi()
{
  if (pre_y >> y)
  {
    y_count++;
  }
  if (print_count >= 100)
  {
    s_count++;
    print_count = 0;
  }
  if (s_count1 == 5)
  {
    Serial.print(s_count);
    Serial.print(" ");
    Serial.print("y_count");
    Serial.println(y_count);
    /*Serial.print("white");
    Serial.print(w);
    Serial.print("up");
    Serial.print(u);
    Serial.print("down");
    Serial.print(d);
    Serial.print("right");
    Serial.print(r);
    Serial.print("left");
    Serial.print(l);*/
    //Serial.println("\n");
    s_count1 = 0;
  }
  flag_10ms = true;
  pre_y = y;
  s_count1++;
  print_count++;
}
void setup()
{
  Serial.begin(115200);
  SERIAL_ROBOCLAW.begin(115200);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(WHITE_BUTTON, INPUT);
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
  pinMode(LEFT_BUTTON, INPUT);
  MsTimer2::set(10, timer_warikomi); // 10ms period
  MsTimer2::start();
  Serial.println("starting");
}

void loop()
{
  Lchika.chika_led1(10,100);
  y = digitalRead(YELLOW_BUTTON);
  w = digitalRead(WHITE_BUTTON);
  u = digitalRead(UP_BUTTON);
  d = digitalRead(DOWN_BUTTON);
  r = digitalRead(RIGHT_BUTTON);
  l = digitalRead(LEFT_BUTTON);

  if (flag_10ms)
  {
    /*if (s_count1 >= 1)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      if (s_count1 >= 2)
      {
        digitalWrite(PIN_LED_RED, LOW);
        s_count1 = 0;
      }
    }*/
    if (y_count == 1)
    {
      MD.SpeedAccelDeccelPositionM1(ADD, 0, 2200, 0, 324, 1);
      for (uint8_t i = 0; i < 100; i++)
      {
        enccount();
        delay(10);
      }
      digitalWrite(PIN_LED_GREEN, HIGH);
    }
    if (y_count == 2)
    {
      //MD.ResetEncoders(ADD);
      MD.SpeedAccelDeccelPositionM1(ADD, 0, 2200, 0, -324, 1);
      for (uint8_t i = 0; i < 100; i++)
      {
        enccount();
        delay(10);
      }
      digitalWrite(PIN_LED_GREEN, LOW);
    }
    if (y_count == 3)
    {
      y_count = 0;
    }
    //long last = millis();
    //while (millis() - last < 5000)
    //{
    //digitalWrite(LED3, HIGH);
    //enccount();
    //delay(50);
    //}
    flag_10ms = false;
  }
}
