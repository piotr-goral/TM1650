#include <Wire.h>
#include "FD650.h"

FD650 d;

void setup() 
{
  Wire.begin(); //Join the bus as master

  Serial.begin(9600); //Start serial communication at 9600 for debug statements
  Serial.println("FD650 Example Code");

  d.init();
   
}

void loop() 
{
  d.displayOff();
  d.displayString("----");
  d.setBrightness(FD650_MIN_BRIGHT);
  d.displayOn();
  delay(2000);
  char line[] = "ABCD";

  d.displayString(line);
  d.setBrightnessGradually(FD650_MAX_BRIGHT);
  delay(2000);
  d.setBrightnessGradually(FD650_MIN_BRIGHT);
  d.displayOff();
  delay(1000);
  
//  line[0] |= 64;
  d.displayOn();
  d.setBrightnessGradually(FD650_MAX_BRIGHT);
  d.displayString(line);
  delay(2000);
  
  for (int i=0; i<8; i++) {
    d.setBrightness(i);
    delay(500);
  }
  
  d.displayString("EFGH");
  delay(2000);

  d.displayString("IJLN");
  delay(2000);
  
  if (d.displayRunning("0123456789ABCDEFGHIJLNOPQRSTUYabcdefghijlnopqrstuy")) {
    while (d.displayRunningShift()) delay(300);
  }
  delay(2000);
  
  for (int i = 0; i<20; i++) {
    d.displayOff();
    delay(200);
    d.displayOn();
    delay(200);
  }
  
  for (int i = 0; i<20; i++) {
    d.setBrightness(1);
    delay(200);
    d.setBrightness(7);
    delay(200);
  }

  for (int i = 0; i<10; i++) {
    for (int j = 0; j<4; j++) {
       d.setDot(j,true);
       delay(200);
    }
    for (int j = 0; j<4; j++) {
       d.setDot(j,false);
       delay(200);
    }
  }

  
}




