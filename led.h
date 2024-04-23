#ifndef _led_h
#define _led_h

#include <FastLED.h>
#include "settings.h"

#define LED_PIN     25
#define NUM_LEDS    20
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

void setupLed(){

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  }

void ledLoop(float input){

  
  int numLedsToLight =   input;
  //int numLedsToLight = map(input, 0, 10, 0, 10);
        // First, clear the existing led values
        //int start = 
        int upper = NUM_LEDS/2;
        int lower = NUM_LEDS/2 -1;
        FastLED.clear();
        for(int led = 0; led < numLedsToLight; led++) { 
            leds[lower] = CRGB::Orange; 
            leds[upper] = CRGB::Orange; 
            upper++;
            lower--;
        }
        FastLED.show();
  
  }
void ledButtonPress(int input){
        //int numLedsToLight =   rotary() ;
        //int numLedsToLight = map(val, 0, 100, 0, NUM_LEDS);
        // First, clear the existing led values
        FastLED.clear();
        int count = 0;
        int upper = input;
        int lower = input;
        int upper1 = input;
        int lower1 = input;
        int j = 1;
        for(int led = 0; led < NUM_LEDS; led++) { 
            //leds[upper] = CRGB::Blue; 
            //leds[lower] = CRGB::Orange;
            //leds[upper - 5] = CRGB::Black; 
            //leds[lower + 5] = CRGB::Black;
            if (upper == NUM_LEDS-1){
              upper  = 0;
              }
            if (lower == 0){
              lower  = NUM_LEDS-1;
              }
            if (upper1 == NUM_LEDS-1){
              upper1  = 0;
              }
            if (lower1 == 0){
              lower1  = NUM_LEDS-1;
              }           
            if (led >=NUM_LEDS/2){
              while(j == 1){
                Serial.println("REVRESE");
                
                int upper = input;
                int lower = input;
                j = 0;
                
                }
              leds[upper1] = CRGB::Black; 
              leds[lower1] = CRGB::Black;
              upper1++;
              lower1--;
              }
            else{
              leds[upper] = CRGB::MediumTurquoise; 
              leds[lower] = CRGB::MediumTurquoise;
              }
            upper++;
            lower--;
            //Serial.println(count);
            count++;
            delay(20);
            FastLED.show();
        }
      FastLED.clear();   
  }

 /*void ledLoad(int input){
  FastLED.clear();
  input = input/10;
  int upper = NUM_LEDS/2;
  int lower = NUM_LEDS/2 -1;
  for(int led = 0; led<NUM_LEDS;led++){
    leds[upper] = CRGB::MediumTurquoise;
    leds[center-input] = CRGB::MediumTurquoise;
    }
  }*/
  
#endif
