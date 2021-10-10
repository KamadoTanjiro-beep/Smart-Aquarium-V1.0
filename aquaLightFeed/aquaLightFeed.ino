//Developed and Maintained by Aniket Patra
//Created on Arduino IDE v1.8.15
//Version 0.0.1 - 10 October 2021
//*Initial Release
#include <Servo.h>  //For servo controlling the feeder
#include <DS3231.h> //For RTC Clock, check Github Readme for more info.
#include <string.h> //For certain string related op.
#include <stdio.h>
DS3231 rtc(SDA, SCL); //DS3231 initialize
Servo myservo;        //servo object
//int count = 0;        //to make sure the servo feeds only once and not infinitely

#define light 7
#define feeder 8
#define lightOn digitalWrite(light, HIGH)
#define lightOff digitalWrite(light, LOW)
#define feederOn digitalWrite(feeder, HIGH)
#define feederOff digitalWrite(feeder, LOW)

const char light_off[9] = "21 00 00"; //24-hours timings as string
const char light_on[9] = "12 00 00";
const char feeder_on[9] = "09 05 00";
const char feeder_off[9] = "09 07 00";

void setup()
{
  rtc.begin();
  myservo.attach(9); //servo is connected at pin 9 (PWM) and initialized
  pinMode(light, OUTPUT);
  pinMode(feeder, OUTPUT);
  lightOn;
  //Serial.begin(9600);
  //rtc.setTime(16,05,00);       //Use this to set correct time into RTC Module, remember to again comment this after use
  //rtc.setDate(23,12,2021);
  //rtc.setDOW(7);

  char temp[7];
  strcpy(temp, removeSpaces(rtc.getTimeStr(FORMAT_LONG, false)));
  temp[5] = 0;
  int x = atoi(temp); //holds current time upto ex.17:12:4, therefor 10:30:33 will be represented as 10303
  int l_off = 21000, l_on = 12000;

  if (x >= l_on && x < l_off)
  {
    //Serial.println("Light Should be ON!");
    lightOn;
  }
  else
  {
    //Serial.println("Light Should be OFF!");
    lightOff;
  }

  //####################################################################################################
  //delay(5000);
}

void loop()
{
  //Serial.println(rtc.getTimeStr(FORMAT_LONG,false));

  if (strcmp(light_off, rtc.getTimeStr(FORMAT_LONG, false)) == 0) //Light ON or OFF, it compares current time with your aforementioned time strings
  {
    lightOff;
  }
  else if (strcmp(light_on, rtc.getTimeStr(FORMAT_LONG, false)) == 0)
  {
    lightOn;
  }

  if (strcmp(feeder_off, rtc.getTimeStr(FORMAT_LONG, false)) == 0)
  {
    feederOff;
  }
  else if (strcmp(feeder_on, rtc.getTimeStr(FORMAT_LONG, false)) == 0)
  {
    feederOn;
    //count = 0;
    //giveFood();
  }
}

char *removeSpaces(char *str) //this function removes spaces from strings
{
  int i = 0, j = 0;
  while (str[i])
  {
    if (str[i] != ' ')
      str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
  return str;
}

/*void giveFood()
{
  int times = 10; //increase this for increasing amount of food and decrease this for lower amount of food
  //myservo.attach(9); //uncomment this to use food function infinitely and comment line number 42
  if (count == 0)
  {
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
    count = 1;
  }

  myservo.write(180); // return to the top. For me 180 degree was at the top, i.e. the feeder opening at the top, as a safety feature
  delay(1000);
  myservo.detach(); //I used detach() everywhere to reduce the servo humming noise
}*/
