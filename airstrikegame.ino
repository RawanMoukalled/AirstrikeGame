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

#include "Display.h"
#include "Game.h"

Display * display;

// Add setup code
void setup() {
  Serial.begin(9600); //UART with its baudrate
  delay(100);
  pinMode(Enter, INPUT_PULLUP);
  
  display = new Display();
    
  display->screen->begin();
  display->screen->setOrientation(0);
    
  display->Initialize_Screen();  //Print first the message: "Airstrike Game"
  delay(2000);
    
  display->screen->clear();   //Go to the next page
    
  display->Display_Select_Type();   //User can choose between a new game or to load a saved game  
}

// Add loop code
void loop() {
  if(display->mode == SELECTTYPE || display->mode == SELECTDIFFICULTY){
    display->Read_Joystick();
    display->Read_Enter();
    delay(200);  
  }

  else if(display->mode == GAME) {
    display->game->plane->Read_Movement();
  }
}



