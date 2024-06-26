                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              #ifndef _rotary_h
#define _rotary_h

// Rotary Encoder Inputs
#define CLK 14 //B
#define DT 15 //A
#define SW 27  //C
//const unsigned int rotBtnPin = 27;
//int buttonState = 0;

/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
#include <BfButton.h> 
#include <Encoder.h>

//#include "mqtt.h"
#include "settings.h"

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(14,15);
//   avoid using pins with LEDs attached

void initRotary() {
  //Serial.begin(115200);
  pinMode(SW, INPUT);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;
int count = 0;

int rotary() {
  long newPosition = myEnc.read()/4;
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    count = newPosition;
    Serial.println(count);
    //mqttRotary(count);
  }

  return count;
}


/*String rotBtnState = "";
void pressHandlerRotBtn(BfButton *btn, BfButton::press_pattern_t pattern) {
  Serial.print(btn->getID());
  int whichButton = btn->getID();
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println(" pressed.");
      buttonPress(whichButton, 0);
      break;
    case BfButton::DOUBLE_PRESS:
      Serial.println(" double pressed.");
      buttonPress(whichButton, 1);
      break;
    case BfButton::LONG_PRESS:
      Serial.println(" long pressed.");
      buttonPress(whichButton, 2);
      break;
  }
}*/



#endif
