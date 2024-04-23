#ifndef _Oldbuttons_h
#define _Oldbuttons_h

#include "settings.h"
//All the button controls and debouncing

//#include "settings.h"


//buttonstate variables
//const int pinL1 = 25;
int L1 = 1;
int L2 = 1;
int L3 = 1;
int L4 = 1;
int R1 = 1;
int R2 = 1;
//int R3 = 0;
//int R4 = 0;

void initButtons(){
  
  pinMode(L1p,INPUT_PULLUP);
  pinMode(L2p,INPUT_PULLUP);
  pinMode(L3p,INPUT_PULLUP);
  pinMode(L4p,INPUT_PULLUP);
  //pinMode(R1p,INPUT_PULLUP);
  //pinMode(R2p,INPUT_PULLUP);
  //pinMode(R3p, INPUT_PULLUP);
  //pinMode(R4p, INPUT_PULLUP);
  }
  
int buttonPressed(){
  L1 = digitalRead(L1p);
  L2 = digitalRead(L2p);
  L3 = digitalRead(L3p);
  L4 = digitalRead(L4p);
  //R1 = digitalRead(R1p);
  //R2 = digitalRead(R2p);
  //R3 = digitalRead(buttonPin);
  //R4 = digitalRead(buttonPin);

  if (L1 == 0){
    Serial.println("L1 Pressed");
    return 1;
    }
  /*else if (L2 = 0){
    return 2;
    }
    else if (L3 = 0){
    return 4;
    }
    else if (L4 = 0){
    return 4;
    }
    else if (R1 = 0){
    return 5;
    }
    else if (R2 = 0){
    return 6;
    }*/
   else {
    return 0;
    }

  }
 #endif
