#include <DS3231.h>
#include<string.h>
#include<stdio.h>
//#include <EEPROM.h>
#include <Servo.h>
Servo myservo;

DS3231  rtc(SDA, SCL);

//int lt=EEPROM.read(0),fltr=EEPROM.read(6);
//EEPROM.update(0,lt);
#define dlay 1000
#define light 7
#define filter 8
#define off LOW
#define on HIGH

char light_off[9]="21 00 00";
char light_on[9]="09 30 00";
char filterDayOff[9]="10 00 00";
char filterDayOn[9]="10 30 00";
char filterNightOff[9]="22 00 00";
char filterNightOn[9]="22 30 00";

void setup() {
  rtc.begin(); 
  myservo.attach(9); 
  pinMode(light,OUTPUT);
  pinMode(filter,OUTPUT);
  digitalWrite(light,on);
  digitalWrite(filter,on);
  Serial.begin(9600);    
  //rtc.setTime(16,05,00);

  //##############################  fail-safe checking  #################################################
  char temp[7];
  strcpy(temp,removeSpaces(rtc.getTimeStr(FORMAT_LONG,false)));
  temp[5]=0;
  int x=atoi(temp);  //holds current time upto ex.17:12:4
  int l_off=21000,l_on=9300,fd_off=10000,fd_on=10300,fn_off=22000,fn_on=22300;
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
    Serial.println("Filter Should be OFF!");
    digitalWrite(filter,off);
    digitalWrite(light,on); 
    food();
  }
    myservo.write(45);
    delay (300);
    myservo.write(90);
    delay (300);
    myservo.detach();
  
  //####################################################################################################
  //delay(5000);
}

void loop() {
 Serial.println(rtc.getTimeStr(FORMAT_LONG,false));
 
 if(strcmp(light_off,rtc.getTimeStr(FORMAT_LONG,false))==0)      //Light ON or OFF
 {
  digitalWrite(light,off);
 }
 else if(strcmp(light_on,rtc.getTimeStr(FORMAT_LONG,false))==0)
 {
  digitalWrite(light,on);
 }

 if(strcmp(filterDayOff,rtc.getTimeStr(FORMAT_LONG,false))==0)       //Filter Day ON or OFF
 {
  digitalWrite(filter,off);
    food();
 }
 else if(strcmp(filterDayOn,rtc.getTimeStr(FORMAT_LONG,false))==0)
 {
  digitalWrite(filter,on);
 }

 if(strcmp(filterNightOff,rtc.getTimeStr(FORMAT_LONG,false))==0)       //Filter Night ON or OFF
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

char *removeSpaces(char *str) 
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
  myservo.attach(9);
    for (int i=0;i<50;i++)
    {
       myservo.write(45);
       delay (300);
       myservo.write(90);
       delay (300);
    }
    
  myservo.detach();
}
