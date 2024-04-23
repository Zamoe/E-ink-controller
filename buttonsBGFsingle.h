#include <BfButton.h>
#include "settings.h"

//initialise BfButton objects
BfButton L1(BfButton::STANDALONE_DIGITAL, L1p, true, LOW);
//BfButton L2(BfButton::STANDALONE_DIGITAL, L2p, true, LOW);
//BfButton L3(BfButton::STANDALONE_DIGITAL, L3p, true, LOW);
//BfButton L4(BfButton::STANDALONE_DIGITAL, L4p, true, LOW);

void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
  if (btn->getID()== L1p){
    Serial.print("L1");
    }
  else if(btn->getID()== L2p){
    Serial.print("L2");
    }
  /*else if(btn->getID()== L3p){
    Serial.print("L3");
    }
  else if(btn->getID()== L4p){
    Serial.print("L4");
    }*/
  //Serial.print(btn->getID());
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println(" pressed.");
      break;
    case BfButton::DOUBLE_PRESS:
      Serial.println(" double pressed.");
      break;
    case BfButton::LONG_PRESS:
      Serial.println(" long pressed.");
      break;
  }
}

void initButtons(){
  L1.onPress(pressHandler)
     .onDoublePress(pressHandler) // default timeout
     .onPressFor(pressHandler, 1000); // custom timeout for 1 second
  L2.onPress(pressHandler)
     .onDoublePress(pressHandler) // default timeout
     .onPressFor(pressHandler, 1000); // custom timeout for 1 second
  /*L3.onPress(pressHandler)
     .onDoublePress(pressHandler) // default timeout
     .onPressFor(pressHandler, 1000); // custom timeout for 1 second
  L4.onPress(pressHandler)
     .onDoublePress(pressHandler) // default timeout
     .onPressFor(pressHandler, 1000); // custom timeout for 1 second */
  }
void buttonRead(){
  //reads the states of the buttons
  L1.read();
  L2.read();
  //L3.read();
  //L4.read();
  }
