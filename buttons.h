//buttons.h: controlling and callback for analog button arrays
#ifndef _buttons_h
#define _buttons_h

#include "settings.h"

#include <BfButtonManager.h>
#include <BfButton.h>

//circuit diagram and library reference: https://github.com/mickey9801/ButtonFever
BfButtonManager manager(btnPinA, 8);
BfButton rotBtn(BfButton::STANDALONE_DIGITAL, rotBtnPin, true, LOW);

BfButton btnA1(BfButton::ANALOG_BUTTON_ARRAY, 0);
BfButton btnA2(BfButton::ANALOG_BUTTON_ARRAY, 1);
BfButton btnA3(BfButton::ANALOG_BUTTON_ARRAY, 2);
BfButton btnA4(BfButton::ANALOG_BUTTON_ARRAY, 3);
BfButton btnB1(BfButton::ANALOG_BUTTON_ARRAY, 4);
BfButton btnB2(BfButton::ANALOG_BUTTON_ARRAY, 5);
BfButton btnB3(BfButton::ANALOG_BUTTON_ARRAY, 6);
BfButton btnB4(BfButton::ANALOG_BUTTON_ARRAY, 7);

int buttonPress(int btn, int pressed){
  //1 = single, 2 = double, 3 = long
  //27 = rotButton
  mqttButtons(btn, pressed);
  int buttonState = 0;
  int  btn1 = btn*10;
  buttonState = btn1 + pressed;
  Serial.print("ButtonID: ");
  Serial.println(btn);
  Serial.print("Pressed: ");
  Serial.println(pressed);
  
  switch (btn) {
    case 0:
        ledButtonPress(3);
      break;
    case 1:
        ledButtonPress(4);
      break;
    case 2:
        ledButtonPress(5);
      break;
    case 3:
        ledButtonPress(6);
      break;
    case 4:
        ledButtonPress(18);
      break;
    case 5:
        ledButtonPress(17);
      break;
    case 6:
        ledButtonPress(16);
      break;
    case 7:
        ledButtonPress(15);
      break;
    case 27:
        ledButtonPress(10);
      break;
  } 
  
  
  /*if (btn == 0){
    if (pressed == 1){
      client.publish("homeassistant/sensor/left1/state","short");
      }
    Serial.println(pressed);
    return buttonState;
    }
   else if(btn == 1){
    Serial.println(pressed);
    return buttonState;
    }
   else if(btn == 2){
    Serial.println(pressed);
    return buttonState;
    }
   else if(btn == 3){
    Serial.println(pressed);
    return buttonState;
    }
   else if(btn == 27){
    Serial.println(pressed);
    return buttonState;
    }*/
   Serial.print("ButtonState: ");
   Serial.println(buttonState);

   return buttonState;
  
}



//presshandler handles the callback for button presses
void pressHandler(BfButton *btn, BfButton::press_pattern_t pattern) {
  //Serial.print(btn->getID());
  int whichButton = btn->getID();
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println(" pressed.");
      buttonPress(whichButton, 1);
      break;
    case BfButton::DOUBLE_PRESS:
      Serial.println(" double pressed.");
      buttonPress(whichButton, 2);
      break;
    case BfButton::LONG_PRESS:
      Serial.println(" long pressed.");
      buttonPress(whichButton, 3);
      break;
  }
}

void initButtons() {

  btnA1.onPress(pressHandler);
  btnA1.onDoublePress(pressHandler);
  btnA1.onPressFor(pressHandler, 1000);
  manager.addButton(&btnA1, 3500, 3900);
  
  btnA2.onPress(pressHandler);
  btnA2.onDoublePress(pressHandler);
  btnA2.onPressFor(pressHandler, 1000);
  manager.addButton(&btnA2, 2900, 3100);

  // You may change event handler methods in any order!
  btnA3.onPress(pressHandler);
  btnA3.onDoublePress(pressHandler);
  btnA3.onPressFor(pressHandler, 1000);
  manager.addButton(&btnA3, 2450, 2600);
  
  btnA4.onPress(pressHandler);
  btnA4.onDoublePress(pressHandler);
  btnA4.onPressFor(pressHandler, 1000);
  manager.addButton(&btnA4, 2000, 2150);

  btnB1.onPress(pressHandler);
  btnB1.onDoublePress(pressHandler);
  btnB1.onPressFor(pressHandler, 1000);
  manager.addButton(&btnB1, 1550, 1700);

  btnB2.onPress(pressHandler);
  btnB2.onDoublePress(pressHandler);
  btnB2.onPressFor(pressHandler, 1000);
  manager.addButton(&btnB2, 1100, 1250);

  btnB3.onPress(pressHandler);
  btnB3.onDoublePress(pressHandler);
  btnB3.onPressFor(pressHandler, 1000);
  manager.addButton(&btnB3, 600, 800);

  btnB4.onPress(pressHandler);
  btnB4.onDoublePress(pressHandler);
  btnB4.onPressFor(pressHandler, 1000);
  manager.addButton(&btnB4, 200, 350);

  manager.begin();
}
void initRotBtn(){
rotBtn.onPress(pressHandler)
      .onDoublePress(pressHandler) // default timeout
      .onPressFor(pressHandler, 1000); // custom timeout for 1 second
  }


/*boolean rotButtonRead(){
  rotBtn.read();
  if (buttonState == 27){
    return true;
    }
  else{
    return false;}
  
  
  }*/



#endif
