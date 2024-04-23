#ifndef _display_h
#define _display_h

#include "bitmaps.h"
#include "settings.h"
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h> // including both doesn't use more code or ram
//#include <GxEPD2_3C.h> // including both doesn't use more code or ram
#include <U8g2_for_Adafruit_GFX.h>

GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT> display(GxEPD2_290_T94_V2(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEM029T94, Waveshare 2.9" V2 variant

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

uint16_t fg = GxEPD_WHITE;
uint16_t bg = GxEPD_BLACK;
uint16_t foreground = GxEPD_WHITE;
uint16_t background = GxEPD_BLACK;

void initdisplay(){
  display.init();
  display.setTextColor(foreground);
  display.fillScreen(background);
  display.setFullWindow();
  display.setRotation(0);
  display.firstPage();
  display.hibernate();
}
void DrawAngledLine(int x, int y, int x1, int y1, int size, int color) {
  float dx = (size / 2.0) * (x - x1) / sqrt(sq(x - x1) + sq(y - y1));
  float dy = (size / 2.0) * (y - y1) / sqrt(sq(x - x1) + sq(y - y1));
  display.fillTriangle(x + dx, y - dy, x - dx,  y + dy,  x1 + dx, y1 - dy, color);
  display.fillTriangle(x - dx, y + dy, x1 - dx, y1 + dy, x1 + dx, y1 - dy, color);
}

void icons(int i, int x, int y, const unsigned char *icon, String string){ 
  //gets state from mqtt and renders icon
  int x2 = x+50;
  int y2 = y+50;
  int x3 = (x+x2)/2;
  int y3 = (y+y2)/2;
  display.setPartialWindow(x, y, 60, 60);
  display.fillScreen(background);
  if (i == 1){
  do
    {
      //display.fillRect(6,11,48,48,background);
      display.fillScreen(background);
      display.drawBitmap(x+1, y+1, icon, 48, 48,foreground);
    }
  while (display.nextPage());
  }

  else if (i == 0) {
    do
    {
      display.fillScreen(background);
      display.drawBitmap(x+1, y+1, icon, 48, 48,foreground);
      DrawAngledLine(x+5,y+5,x2-5,y2-5,3,foreground);
    }
    while (display.nextPage());
  }
  else if (i == 4){
    do
    {
      //display.fillRect(6,11,48,48,background);
      display.fillScreen(background);
      display.drawBitmap(x+1, y+1, icon, 48, 48,foreground);
      int16_t tbx, tby; uint16_t tbw, tbh;
      //center the text
      display.getTextBounds(string, x, y, &tbx, &tby, &tbw, &tbh);
      tbw = tbw/2;
      display.setCursor(x3-tbw,y+48);
      display.print(string);
    }
  while (display.nextPage());
    }

  else{
    do
    {
      display.fillScreen(background);
      display.drawBitmap(x+1, y+1, icon, 48, 48,foreground);
      DrawAngledLine(x+10,y+10,x2-10,y2-10,3,foreground);
      display.drawBitmap(x+1, y+1, circle, 48, 48,foreground);
    }
    while (display.nextPage());
    }
}

void displaySpotify(int i,String string){
  int x0 = 5;
  int y0 = display.height()-50;
  int x1 = display.width()-5;
  int y1 = display.height()-2;
  int x3 = (x0+x1)/2;
  int y3 = (y0+y1)/2;
  
  display.setPartialWindow(38, 191, 50, 50);
  display.drawBitmap(40, 191, spotify, 48, 48,foreground);
  
  if (i == 1){
    display.setPartialWindow(x0, y0, x1-x0, 20);
    //display.drawRect(x0+1,y0+1,x1-x0-1,20-1,foreground);
    display.fillScreen(background);
    do
    {
      //display.fillRect(6,11,48,48,background);
      display.fillScreen(background);
      int16_t tbx, tby; uint16_t tbw, tbh;
      //center the text
      display.getTextBounds(string, x0, y0, &tbx, &tby, &tbw, &tbh);
      tbw = tbw/2;
      //display.drawRect(tbx,tby,tbw,tbh,foreground);
      display.setCursor(x3-tbw,y0 + tbh);
      display.print(string);
      Serial.print("Height");
      Serial.println(tbh);
    }
  while (display.nextPage());
    }
  
  else if (i == 2){
    y0 +=20;
    display.setPartialWindow(x0, 296-20, x1-x0, 18);
    display.fillScreen(background);
    do
    {
      //display.fillRect(6,11,48,48,background);
      display.fillScreen(background);
      int16_t tbx, tby; uint16_t tbw, tbh;
      //center the text
      display.getTextBounds(string, x0, 296-20, &tbx, &tby, &tbw, &tbh);
      tbw = tbw/2;
      display.setCursor(x3-tbw,276);
      display.print(string);
      Serial.print("Source print: ");
      Serial.println(string);
    }
  while (display.nextPage());
    }
  
  }
/*void updateStates(){
  if (allStatesNew != allStatesOld){
    icons(ceilingState,ceilingx,ceilingy,ceiling);
    icons(lampState,lampx,lampy,lamp);
    icons(backlightState,backlightx,backlighty,backlight);
    icons(tvState,tvx,tvy,tv);
    icons(bedState,bedx,bedy,bed);
    icons(1,nextx,nexty,next);
    icons(1,prevx,prevy,prev);
    allStatesOld = allStatesNew;
    }
  }*/

void defaultPage(){
  display.setTextColor(foreground);
  display.fillScreen(background);
  display.firstPage();
  do
  {
    display.fillScreen(background);
    // comment out next line to have no or minimal Adafruit_GFX code
    //display.drawRect(5,10,50,50,foreground);
    //display.drawRect(5,70,50,50,foreground);
    //display.drawRect(5,130,50,50,foreground);
    //display.drawRect(5,190,50,50,foreground);

    //display.drawRect(73,10,50,50,foreground);
    //display.drawRect(73,70,50,50,foreground);
    //display.drawRect(73,130,50,50,foreground);
    //display.drawRect(73,190,50,50,foreground);
    //display.drawBitmap(55, 250, lightbulb, 50, 50,foreground);
    display.drawBitmap(prevx+1, prevy+1, prev, 48, 48,foreground); 
    display.drawBitmap(nextx+1, nexty+1, next, 48, 48,foreground);
    display.drawBitmap(46, 193, spotify, 36, 36,foreground);
  }
  while (display.nextPage());
  }

/*
void initdisplay(){
  display.init();
  display.setTextColor(GxEPD_BLACK);
  display.setRotation(0);
  display.firstPage();

  u8g2Fonts.begin(display); // connect u8g2 procedures to Adafruit GFX
  delay(1000);

  uint16_t bg = GxEPD_WHITE;
  uint16_t fg = GxEPD_BLACK;
  u8g2Fonts.setForegroundColor(fg);         // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(bg);
    do{
    display.fillScreen(GxEPD_WHITE);

    u8g2Fonts.setFont(u8g2_font_fub20_tr);   //font is set
    u8g2Fonts.setCursor(20, 80);             //cursor(x,y)
    u8g2Fonts.print("Volume");   //print the text
  }while (display.nextPage());
}*/


#endif
