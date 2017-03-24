///
/// @mainpage  LCD_screen_Logos
///
/// @details  Energia logo for Educational BoosterPack 2
/// @n
/// @n
/// @n @a       Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author Rei VILO
/// @author http://embeddedcomputing.weebly.com
///
/// @date Dec 14, 2103
/// @version  104
///
/// @copyright  (c) Rei VILO, 2013
/// @copyright  CC = BY SA NC
///
/// @see  ReadMe.txt for references
///


///
/// @file LCD_screen_Logos.ino
/// @brief  Main sketch
///
/// @details  Energia logo for Educational BoosterPack 2
/// @n @a Developed with [embedXcode](http://embedXcode.weebly.com)
///
/// @author Rei VILO
/// @author http://embeddedcomputing.weebly.com
/// @date 26/07/13 20:26
/// @version  <#version#>
///
/// @copyright  (c) Rei VILO, 2013
/// @copyright  CC = BY SA NC
///
/// @see  ReadMe.txt for references
/// @n
///


// Core library for code-sense
#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>

#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>
Screen_HX8353E myScreen;


#define ROWS 80 // max 80
#define COLS 60 // max 60

#define ALIVE   0x08
#define DEAD    0x00


#define NewGame 33
#define Load Game 32

#define joystickX 2
#define joystickY 26


// Define variables and constants
uint8_t _screen[2][ROWS][COLS];
uint32_t chrono;
uint8_t page;
uint16_t colours[16];
uint16_t generation;
uint8_t rowSize, colSize;
uint8_t i, j;
uint16_t x, y, x00, y00; //joystick location


// Define variables and constants

#include "Energia_logo_100_132.h"

//void logo50()
//{
//    uint32_t p;
//    uint16_t c;
//    uint16_t x00 = 0;
//    uint16_t y00 = 0;
//    uint16_t i00 = 0;
//    uint16_t j00 = 0;
//    
//    if ((myScreen.screenSizeX() > x_Energia_logo_100_132_bmp)) {
//        x00 = (myScreen.screenSizeX() - x_Energia_logo_100_132_bmp) / 2;
//    } else {
//        i00 = (x_Energia_logo_100_132_bmp - myScreen.screenSizeX()) / 2;
//    }
//    if ((myScreen.screenSizeY() > y_Energia_logo_100_132_bmp)) {
//        y00 = (myScreen.screenSizeY() - y_Energia_logo_100_132_bmp) / 2;
//    } else {
//        j00 = (y_Energia_logo_100_132_bmp - myScreen.screenSizeY()) / 2;
//    }
//    p = (uint32_t)x_Energia_logo_100_132_bmp * y_Energia_logo_100_132_bmp;
//    
//    for (uint16_t i=0; i<x_Energia_logo_100_132_bmp; i++) {
//        for (uint16_t j=0; j<y_Energia_logo_100_132_bmp; j++) {
//            if ((x00+i < myScreen.screenSizeX()) && (y00+j < myScreen.screenSizeY())) {
//                c = pic_Energia_logo_100_132_bmp[i*y_Energia_logo_100_132_bmp + j];
//                myScreen.point(x00+i-i00, y00+j-j00, c);
//            }
//        }
//    }
//}


void Initialize_Screen(){
    myScreen.clear(cyanColour);
    myScreen.setFontSolid(true);
    myScreen.setFontSize(1);
    myScreen.gText(13, 50, "AirStrike Game");
}

void Select_Game_Option(){
  myScreen.clear(blackColour);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(1);
  myScreen.gText(3, 50, ">");
  myScreen.gText(15, 50, "New Game");
  myScreen.gText(15, 70, "Load Game");

//  while(1){
//    x = map(analogRead(joystickX), 0, 4096, 0, 128);
//    y = map(analogRead(joystickY), 0, 4096, 128, 0);
//    if (x < 1)      x = 1;
//    if (x > 126)    x = 126;
//    if (y < 1)      y = 1;
//    if (y > 126)    y = 126;
//    if ((x00 != x) || (y00 != y)) {
//       
//        myScreen.dRectangle(x00-1, y00-1, 3, 3, whiteColour);
//        myScreen.dRectangle(x-1, y-1, 3, 3, whiteColour);
//        x00 = x;
//        y00 = y;
//    }
//
//    myScreen.gText(0, myScreen.screenSizeY()-myScreen.fontSizeY(),
//                   "x=" + i32toa((int16_t)x-64, 10, 1, 6) +" y=" + i32toa(64-(int16_t)y, 10, 1, 6),
//                   whiteColour);
//  }
  }
  



// Add setup code
void setup() {
    Serial.begin(9600);
    delay(100);
    Serial.println("WITH_LOGO example for LCD_screen");
    
    myScreen.begin();
    String s = myScreen.WhoAmI();
    myScreen.setOrientation(0);
    x00 = 0;
    y00 = 0;
}

// Add loop code
void loop() {

    Initialize_Screen();  //Print first the message: "Airstrike Game"
    delay(2000);
    
    myScreen.clear();   //Go to the next page
    
    Select_Game_Option();   //User can choose between a new game or to load a saved game


    while(1)
    {
    }
}
    //chrono = millis();
    //logo50();
    //Serial.println(millis() - chrono, DEC);



