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

#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"


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
    void Initialize_Score();
    void Increase_score();
    void Start_Timer_1sec();
    void Decrease_Life();
    void Change_Plane_Color(); 
    void Delete_Outlier_Targets();
    void Delete_Outlier_Obstacles();
    void Delete_Outlier_Strikes();
    void Delete_Strikes_Targets();
    void Color_Targets(const uint16_t color);
    void Color_Obstacles(const uint16_t color);
    void Color_Strikes(const uint16_t color);
    void Detect_Strike_Hits();
    
    
    double distance(int x1, int y1, int x2, int y2);

    //hard timer handler
    void Hard_Timer();

    //generation timer handler
    void Generation_Timer();
    
    Screen_HX8353E *screen;
    Airplane * plane;
    std::vector<Target*> targets;
    std::vector<Obstacle*> obstacles;
    std::vector<Strike*> strikes;
    
    int score;
    
    //Strike *strike;

    //hard timer variables
    volatile uint16_t flag_1sec; 
    volatile uint8_t remaining_time;

    //obstacle and target generation timer variables
    volatile uint16_t flag_random; 
    int random_time; //randomizes the times in which a new obstacle or target are created

};

#endif

