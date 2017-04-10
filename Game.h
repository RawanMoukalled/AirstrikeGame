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

#include <vector>
#include "Airplane.h"
#include "Target.h"
#include "Obstacle.h"
#include "Strike.h"

class Game {
  public:
    Game(Screen_HX8353E *screen);
    void Initialize_Objects();
    void Display_Game();
    void Clear_Objects();
    void Increment_Object_Positions();
    void Place_Objects();
    void Create_New_Strike();

    void Initialize_Life();
    void Start_Timer_1sec();
    void Decrease_Life();
    void Change_Plane_Color(); //When a collision happens between the airplane and a target/obstacle, change the plane's color to red

    double distance(int x1, int y1, int x2, int y2);

    
    Screen_HX8353E *screen;
    Airplane * plane;
    //Vector<Target*> targets;
    Target * target;
    //Vector<Obstacle*> obstacles;
    //Obstacle *obstacle;
    Strike *strike;
    
    int score = 0; //increment in case strike hits target
  private:
    
};

#endif
