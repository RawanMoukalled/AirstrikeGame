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

#include <vector>
#include "Game.h"

Screen_HX8353E screen_main; 
Screen_HX8353E *screen = &screen_main; //pointer to the screen  




#define ROWS 80 // max 80
#define COLS 60 // max 60

#define ALIVE   0x08
#define DEAD    0x00

#define joystickX 2 //pin for the joystick X coordinates
#define joystickY 26 //pin for the joystick Y coordinates
#define Enter 32 //pin for the Push button


//function prototypes
void Initialize_Screen();
void Display_Select_Type();
void Place_Arrow(uint16_t x, uint16_t y);
void Read_Joystick();
void Display_Select_Difficulty();
void Display_New_Page(uint16_t y);
void Read_Enter();

// Define variables and constants
uint16_t jsX, jsY, arrowX, arrowY; //current positions of the joystick and arrow 

// Which mode of the game we are at
enum screen_mode_t {
  SELECTTYPE, GAME, PAUSE, LOADGAME,
  SELECTDIFFICULTY
} mode = SELECTTYPE; // main mode to be used 

// Display Airstrike Game 
void Initialize_Screen(){
  screen->clear(cyanColour);
  screen->setFontSolid(true);
  screen->setFontSize(1);
  screen->gText(13, 50, "AirStrike Game");
}

//Select between a new game or loading one 
void Display_Select_Type(){
  mode = SELECTTYPE;
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  arrowX = 3;
  arrowY = 50;
  screen->gText(arrowX, arrowY, ">");
  screen->gText(15, 50, "New Game");
  screen->gText(15, 70, "Load Game");
}

void Place_Arrow(uint16_t x, uint16_t y){
    uint16_t minY, maxY;
    if(mode == SELECTTYPE) {
      minY = 50; 
      maxY = 70;
    } 

    else if (mode == SELECTDIFFICULTY) {
      minY = 50;
      maxY = 90;
    }

    //erase current arrow by placing a full black box on it
    screen->setPenSolid(true);
    screen->dRectangle(arrowX, arrowY, 9, 10, blackColour);

    //loop to bottom or top if the next y position exceeds the 
    //current menu items position range
    if( y > maxY) {
      arrowY = minY;
    } else if (y < minY) {
      arrowY = maxY;
    } else{ //update arrow position 
      arrowX = x;
      arrowY = y;  
    }
    screen->gText(arrowX, arrowY, ">");
}

//checks the joystick movements
void Read_Joystick() {
  
  //convert from input to output range, Y goes from 0 to 128 top to bottom of the screen
  jsX = map(analogRead(joystickX), 0, 4096, 0, 128);
  jsY = map(analogRead(joystickY), 0, 4096, 128, 0);
  
  //joystick was moved down
  if( jsY > 90) {
    Place_Arrow(arrowX, arrowY + 20);
  } else if (jsY < 30) { 
    Place_Arrow(arrowX, arrowY - 20);
  }

}

void Display_Select_Difficulty() {
  mode = SELECTDIFFICULTY;
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->gText(40, 10, "Select");
  screen->gText(25, 30, "Difficulty");
  arrowX = 3;
  arrowY = 50;
  screen->gText(arrowX, arrowY, ">");
  screen->gText(15, 50, "Easy");
  screen->gText(15, 70, "Hard");
  screen->gText(15, 90, "Back");
}

//Displays new page according to the position of the arrow 
//which means, which menu item position was selected
void Display_New_Page(uint16_t y) {
  
  if(mode == SELECTTYPE){
    if(y == 50){
      
      Display_Select_Difficulty();
    }else if(y == 70) {
      //Display_Load_Game();
    }
  } 
  
  else if(mode == SELECTDIFFICULTY) {
    //easy mode
    if(y == 50){
      //easy
      mode = GAME; 
      //Display_Gameplay();
      Game * game = new Game(screen);
      game->Display_Game();
      Serial.println("easy");
    } 
    //hard mode
    else if(y == 70) {
       //hard
       mode = GAME; 
       //Display_Gameplay();
       Serial.println("hard");
    }
    //back to select type
    else if(y == 90) {
      Display_Select_Type();
    }
  } 
}

// check for the push button being pressed
void Read_Enter() {
  int enterState = digitalRead(Enter);
  
  //button has been pushed
  if(enterState == LOW) {
    if(mode == SELECTTYPE || mode == SELECTDIFFICULTY){
      Display_New_Page(arrowY);
    } 
  }

}

// Add setup code
void setup() {
  Serial.begin(9600); //UART with its baudrate
  delay(100);
  pinMode(Enter, INPUT_PULLUP);
    
  screen->begin();
  screen->setOrientation(0);
    
  Initialize_Screen();  //Print first the message: "Airstrike Game"
  delay(2000);
    
  screen->clear();   //Go to the next page
    
  Display_Select_Type();   //User can choose between a new game or to load a saved game  
}

// Add loop code
void loop() {
  if(mode == SELECTTYPE || mode == SELECTDIFFICULTY){
    Read_Joystick();
    Read_Enter();
    delay(200);  
  } 
}





