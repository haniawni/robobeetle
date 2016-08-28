/*
This script has the ATtiny 



This library is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

*/

#include "looper.h"
#include <SoftwareSerial.h>
// Definitions
#define rxPin 3
#define txPin 4
#define LED1 0
#define LED2 1

looper myScheduler; //create a new instance of the class leOS
SoftwareSerial mySerial(rxPin, txPin);  //

//variabiles to control the LEDs
byte ledStatus[] = {0,0};
byte tasks[] = {1,1};

//program setup
void setup() {
    pinMode(LED1, OUTPUT);
    mySerial.begin(9600);
    
    //add the tasks at the scheduler
    myScheduler.addJob(flashLed1, 1000);
    myScheduler.addJob(flashLed2, 500);
}


//main loop
void loop() {
  if(mySerial.available()){
    byte c = mySerial.read();
    mySerial.println(c);
    if(c==107){
      if(tasks[0]){
        myScheduler.pauseJob(flashLed1);
        ledStatus[0]=0;
        digitalWrite(LED1, 0);
      } else {
        myScheduler.restartJob(flashLed1);
      }
      tasks[0]^=1;
    }
    if(c==106){
      if(tasks[1]){
        myScheduler.pauseJob(flashLed2);
        ledStatus[1]=0;
        digitalWrite(LED2, 0);
      } else {
        myScheduler.restartJob(flashLed2);
      }
      tasks[1]^=1;
    }
  }
  //mySerial.println("checking in");
  myScheduler.scheduler();
}


//flashing tasks
void flashLed1() {
    ledStatus[0]^=1;
    digitalWrite(LED1, ledStatus[0]);
}

void flashLed2() {
    ledStatus[1]^=1;
    digitalWrite(LED2, ledStatus[1]);
}
