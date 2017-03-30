#ifndef display_h
#define display_h


#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

#include <SPI.h>

#include <LCD_screen.h>
#include <LCD_screen_font.h>
#include <LCD_utilities.h>
#include <Screen_HX8353E.h>
#include <Terminal12e.h>
#include <Terminal6e.h>
#include <Terminal8e.h>

#include "Game.h"

#define joystickX 2 //pin for the joystick X coordinates
#define joystickY 26 //pin for the joystick Y coordinates
#define Enter 32 //pin for the Push button

// Define variables and constants


// Which mode of the game we are at
enum screen_mode_t {
  SELECTTYPE, GAME, PAUSE, LOADGAME,
  SELECTDIFFICULTY
}; // main mode to be used 


class Display {
  public:
    Display();
    void Initialize_Screen();
    void Display_Select_Type();
    void Place_Arrow(uint16_t x, uint16_t y);
    void Read_Joystick();
    void Display_Select_Difficulty();
    void Display_New_Page(uint16_t y);
    void Read_Enter();
    void Display_Paused_Game();

    screen_mode_t mode;

    uint16_t jsX, jsY, arrowX, arrowY; //current positions of the joystick and arrow 

    Screen_HX8353E screen_main; 
    Screen_HX8353E *screen;//pointer to the screen

    Game * game;

};

#endif
