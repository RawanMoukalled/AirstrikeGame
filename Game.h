#ifndef game_h
#define game_h

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

#include "Airplane.h"

class Game {
  public:
    Game(Screen_HX8353E *screen);
    void Display_Game();
    void Clear_Objects();
    void Increment_Object_Positions();
    void Place_Objects();

    Screen_HX8353E *screen;
    Airplane * plane;
    
  private:
    
};

#endif
