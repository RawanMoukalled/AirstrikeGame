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
//#include "Display.h"

#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

// Which mode of the game we are at
enum level_t {
  EASY, HARD, NONE
}; // main mode to be used 

class Game {
  public:
    Game(Screen_HX8353E *screen);
    void Initialize_Game();
    void Display_Game();
    
    void Clear_Objects();
    void Increment_Object_Positions();
    void Place_Objects();
    
    void Create_New_Strike();
    
    void Draw_Life();
    void Display_Score();
    
    void Increase_score();
    void Decrease_Life();
    
    void Delete_Outlier_Targets();
    void Delete_Outlier_Obstacles();
    void Delete_Outlier_Strikes();
    void Delete_Struck_Targets();
    void Delete_Expired_Strikes();
    void Delete_All_Objects();
    
    void Color_Targets(const uint16_t color);
    void Color_Obstacles(const uint16_t color);
    void Color_Strikes(const uint16_t color);
    void Color_Plane(const uint16_t color);
    
    void Detect_Strike_Hits();

    void Increment_Timer_Flag();
    void Decrease_Remaining_Time();

    void Set_Level(level_t level);
    
    //generation pseudo-timer handler
    void Generation_Timer();
    
    Screen_HX8353E *screen;
    Airplane * plane;
    std::vector<Target*> targets;
    std::vector<Obstacle*> obstacles;
    std::vector<Strike*> strikes;
    int score;
    int life;
    int lifePos;
    bool new_strike;
    bool pause;
    bool gameover;
    level_t level;
    
    //hard timer variables
    volatile uint16_t flag_1sec; 
    volatile uint8_t remaining_time;

    //obstacle and target generation timer variables
    volatile uint16_t flag_random; 
    int random_time; //randomizes the times in which a new obstacle or target are created
};

#endif

