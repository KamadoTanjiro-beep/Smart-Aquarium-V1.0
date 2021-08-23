#include <DS3231.h> //For RTC Clock, check Github Readme for more info.
#include <string.h>
#include <stdio.h>
DS3231 rtc(SDA, SCL);

#define light 7
#define filter 8
#define lightOn digitalWrite(light, HIGH)
#define lightOff digitalWrite(light, LOW)
#define filterOn digitalWrite(filter, HIGH)

char light_off[9] = "18 30 00"; //24-hours timings as string
char light_on[9] = "08 30 00";

void setup()
{
  rtc.begin();

  pinMode(light, OUTPUT);
  pinMode(filter, OUTPUT);
  lightOn;
  filterOn;
  //Serial.begin(9600);
  //rtc.setTime(16,05,00);       //Use this to set correct time into RTC Module, remember to again comment this after use
  //rtc.setDate(23,12,2021);
  //rtc.setDOW(7);

  char temp[7];
  strcpy(temp, removeSpaces(rtc.getTimeStr(FORMAT_LONG, false)));
  temp[5] = 0;
  int x = atoi(temp); //holds current time upto ex.17:12:4, therefor 10:30:33 will be represented as 10303
  int l_off = 18300, l_on = 8300;

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
