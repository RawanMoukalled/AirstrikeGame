///
/// @mainpage  Airstrike Game
///
/// @details  EECE 425 Project 
/// @n
/// @n
/// @n @a       
///
/// @author Anthony Gebrayel
/// @author Jean Abou Rahal
/// @author Rawan Moukalled
///
/// @date April 25, 2017
/// @version  1
///
///
/// @see  README.txt for references
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
Screen_HX8353E screen;


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

enum mode_t {
  SELECTGAME, GAME, PAUSE, LOADGAME
  }, 
  mode = SELECTGAME;

void Initialize_Screen(){
    screen.clear(cyanColour);
    screen.setFontSolid(true);
    screen.setFontSize(1);
    screen.gText(13, 50, "AirStrike Game");
}

void Select_Game_Option(){
  screen.clear(blackColour);
  screen.setFontSolid(false);
  screen.setFontSize(1);
  screen.gText(3, 50, ">");
  screen.gText(15, 50, "New Game");
  screen.gText(15, 70, "Load Game");
}

void Arrow_Move(){
  x = analogRead(joystickX);
  y = analogRead(joystickY);
  
}

// Add setup code
void setup() {
    Serial.begin(9600); //UART with its baudrate
    delay(100);
    
    screen.begin();
    screen.setOrientation(0);
    joystickX00 = 0;
    joystickY00 = 0;

    Initialize_Screen();  //Print first the message: "Airstrike Game"
    delay(2000);
    
    screen.clear();   //Go to the next page
    
    Select_Game_Option();   //User can choose between a new game or to load a saved game

}

// Add loop code
void loop() {
    if(mode == SELECTGAME){
      Arrow_Move();
    }
    
}





