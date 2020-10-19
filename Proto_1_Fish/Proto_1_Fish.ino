//Developed and Maintained by Aniket Patra
//Created on Arduino IDE v1.8.13
//Version 0.0.3

#include <DS3231.h>   //For RTC Clock, check Github Readme for more info.
#include<string.h>
#include<stdio.h>
#include <Servo.h>       //For servo controlling the feeder
Servo myservo;

DS3231  rtc(SDA, SCL);   //Connect to the Arduino Default SDA SCL Pins, Google it further for more info.
            
#define light 7          //Relay for light connected pin
#define filter 8          //Relay for Filter connected pin
#define off LOW           //My relay module was active-low, I used Normally-Open (N.O. pin) as off
#define on HIGH           //And Normally-Closed (N.C.) as default connection, so that I can operate the 
                          //light and filter without the arduino being turned ON. Little imagination will help :)
char light_off[9]="21 00 00";            //24-hours timings as string
char light_on[9]="09 30 00";
char filterDayOff[9]="10 00 00";         //filter off time, during day time feeding
char filterDayOn[9]="10 05 00";
char filterNightOff[9]="22 00 00";         //same as above
char filterNightOn[9]="22 05 00";

void setup() {
  rtc.begin();               
  myservo.attach(9);                //servo is connected at pin 9 (PWM)
  pinMode(light,OUTPUT);
  pinMode(filter,OUTPUT);
  digitalWrite(light,on);
  digitalWrite(filter,on);
  Serial.begin(9600);    
  //rtc.setTime(16,05,00);       //Use this to set correct time into RTC Module, remember to again comment this after use

  //##############################  fail-safe checking  #################################################
  //This part of code checks status of light, filter and feeder when the device is turned on.
  //Particularly useful after a Power loss. It takes the current time and decides the things that should have been done.
  //I will update it again with EEPROM function so that it remembers what were done before power cut.
  char temp[7];
  strcpy(temp,removeSpaces(rtc.getTimeStr(FORMAT_LONG,false)));
  temp[5]=0;
  int x=atoi(temp);  //holds current time upto ex.17:12:4, therefor 10:30:33 will be represented as 10303
  int l_off=21000,l_on=9300,fd_off=10000,fd_on=10050,fn_off=22000,fn_on=22050;   //l_off is light off, fd is filter during day, fn is filter during night
                                                                                 //Be sure to update this as well when you update above timings, I will update it later
                                                                                 //for automatic setting
  if (x>=l_on && x<l_off)
  {
    //Serial.println("Light Should be ON!");
    digitalWrite(light,on);  
  }
  else
  {
    //Serial.println("Light Should be OFF!");
    digitalWrite(light,off); 
  }

  if ((x>=fd_off && x<fd_on)||(x>=fn_off && x<fn_on))
  {
    //Serial.println("Filter Should be OFF!");
    digitalWrite(filter,off);
    digitalWrite(light,on); 
    food();
  }
    myservo.write(45);              //just to chcek if servos are working or not
    delay (300);
    myservo.write(90);
    delay (300);
    myservo.detach();
  
  //####################################################################################################
  //delay(5000);
}

void loop() {
 //Serial.println(rtc.getTimeStr(FORMAT_LONG,false));
 
 if(strcmp(light_off,rtc.getTimeStr(FORMAT_LONG,false))==0)      //Light ON or OFF, it compares current time with your aforementioned time strings
 {
  digitalWrite(light,off);
 }
 else if(strcmp(light_on,rtc.getTimeStr(FORMAT_LONG,false))==0)
 {
  digitalWrite(light,on);
 }

 if(strcmp(filterDayOff,rtc.getTimeStr(FORMAT_LONG,false))==0)       //Filter Day ON or OFF, it compares current time with your aforementioned time strings
 {
  digitalWrite(filter,off);
    food();
 }
 else if(strcmp(filterDayOn,rtc.getTimeStr(FORMAT_LONG,false))==0)
 {
  digitalWrite(filter,on);
 }

 if(strcmp(filterNightOff,rtc.getTimeStr(FORMAT_LONG,false))==0)       //Filter Night ON or OFF, it compares current time with your aforementioned time strings
 {
  digitalWrite(filter,off);
  digitalWrite(light,on); 
  food();
 }
 else if(strcmp(filterNightOn,rtc.getTimeStr(FORMAT_LONG,false))==0)
 {
  digitalWrite(filter,on);
  digitalWrite(light,off); 
 } 
}

char *removeSpaces(char *str)                                            //this function removes spaces from strings
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

void food(){  
  int amount = 50;                                     //increase this for increasing amount of food and decrease this for decreasing
  myservo.attach(9);
    for (int i=0;i<amount;i++)
    {
       myservo.write(45);
       delay (300);
       myservo.write(90);
       delay (300);
    }
    
  myservo.detach();                        //I used this for removing the servo humming noise
}
