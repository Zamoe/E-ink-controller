// Rotary Encoder Inputs
#define CLK 14 //B
#define DT 15 //A
#define SW 27  //C

#include "led.h"
#include "rotary.h"
#include "display.h"
#include "mqtt.h"
#include "buttons.h"
#include "settings.h"


int rotState = 0;
//int prevCount = 0;

String mode = "default";

void setup() {
  delay( 3000 ); // power-up safety delay
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  setupLed();
  ledLoop(1);
  setup_wifi();
  ledLoop(2);
  initdisplay(); 
  ledLoop(3);
  setupMQTT();
  ledLoop(4);
  initButtons();
  ledLoop(5);
  initRotBtn();
  ledLoop(6);
  setup_wifi();
  ledLoop(7);
  defaultPage();
  ledLoop(8);
  delay(10);
  ledLoop(10);
  //setupLed();
  FastLED.clear();

  }

void loop(){
  //Serial.println("Program Running");
  if (!client.connected())  // Reconnect if connection is lost
  {
    reconnect();
  }
  client.loop();
  //ledLoop();
  //buttonRead();
  manager.loop();
  rotBtn.read();
  //updateStates();
  int time1 = millis();
  int temp =   rotary();
  mqttRotary(temp);
  /*int count = rotary() + count;
  count = count/4;
  /*if (buttonPressed()== 1){
    Serial.println("buttonPressed");
    digitalWrite(2,HIGH);
    }*/
 // else{digitalWrite(2,LOW);};
  /*if (count != rotState){
     Serial.println(count);
     rotState = count;

  //display
  display.setPartialWindow(5, 10, 50, 50);//x,y,w,h
  display.firstPage();

  do{
    display.setTextColor(GxEPD_BLACK);
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(5, 10);
    display.print(volume);
    Serial.print("volume=");
    Serial.println(volume);
  }while(display.nextPage());
    }
   if (count > prevCount){
    prevCount = count;
    Serial.println("Prev Count increased = %d");
    client.publish("CW", "on");
    Serial.print(prevCount);
    }
  if (count < prevCount){
    prevCount = count;
    Serial.println("Prev Count decreased = %d");
    client.publish("CCW", "on");
    Serial.print(prevCount);
    }*/
   //delay(10);
  /* if (rotButtonRead() == true){
    String test= "";
    Serial.println("Button Pressed long");
    //display.refresh();
    client.publish("room/light", "on");
    Serial.println( " => on");
    //count = 0;
    //buttonState = 0;
    }*/
    
    
   }
  
