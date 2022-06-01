//Developed and Maintained by Aniket Patra
//Created on Arduino IDE v1.8.15
//Version 0.0.1 - 10 October 2021
//Version 0.0.2 - 01 June 2022
//*Initial Release
#include <Wire.h>
#include "RTClib.h"
#include <Servo.h> //For servo controlling the feeder

RTC_DS3231 rtc;
Servo myservo; //servo object
#define ledOn digitalWrite(LED_BUILTIN,HIGH);
#define ledOff digitalWrite(LED_BUILTIN,LOW);
unsigned long lastTime = 0;
const long timerDelay = 900; // check relay status every 30 seconds

void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
  myservo.attach(9); //servo is connected at pin 9 (PWM) and initialized
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.begin(9600);
}

void loop()
{ledOff;
  if ((millis() - lastTime) > timerDelay)
  {ledOn;
    DateTime now = rtc.now();
    /*Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();*/

    if ((now.year() == 2022) && (now.month() == 6) && (now.day() == 1) && (now.hour() == 22) && (now.minute() == 27) && (now.second() == 0))
    {
      giveFood();
    }
    
    lastTime = millis();
  }
}

void giveFood()
{
  int times = 10; //increase this for increasing amount of food and decrease this for lower amount of food
  myservo.attach(9); //uncomment this to use food function infinitely and comment line number 42


  for (int i = 0; i < times; i++)
  {
    myservo.write(0);
    delay(500); //increase this delay for wider angle movements
    myservo.detach();
    delay(300);
    myservo.attach(9);
    myservo.write(120);
    delay(800); //increase this delay for wider angle movements
  }



  myservo.write(180); // return to the top. For me 180 degree was at the top, i.e. the feeder opening at the top, as a safety feature
  delay(1000);
  myservo.detach(); //I used detach() everywhere to reduce the servo humming noise
}
