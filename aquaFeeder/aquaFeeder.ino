//Developed and Maintained by Aniket Patra
//Created on Arduino IDE v1.8.15
//Version 0.0.1 - 10 October 2021
//*Initial Release
#include <Servo.h> //For servo controlling the feeder

Servo myservo; //servo object
int count = 0; //to make sure the servo feeds only once and not infinitely

void setup()
{
  myservo.attach(9); //servo is connected at pin 9 (PWM) and initialized

  //Serial.begin(9600);
}

void loop()
{
  //Serial.println(rtc.getTimeStr(FORMAT_LONG,false));

  giveFood();
  //delay(5000);
}

void giveFood()
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
}
