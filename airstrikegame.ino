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
#include "inc/hw_ints.h"
#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#define joystickSEL 5 //pin for the joystick push button
#define pushButton1 33 //push button for Pause option


Display * display;
volatile int strikeFlag = HIGH;
volatile int pauseFlag = HIGH;
volatile uint16_t flag_1sec = 1; 
volatile uint8_t count_timer_1sec = 100;

void strikeInterrupt()
{
  if(display->mode == GAME){
    //strikeFlag = HIGH;
    display->game->Create_New_Strike();
  }
  pauseFlag = LOW;
}

void Timer1IntHandler(void){
  //Required to launch next interrupt
  ROM_TimerIntClear(TIMER1_BASE, TIMER_A);
  flag_1sec +=1;
  if (flag_1sec == 1600){
      count_timer_1sec -=1;
    Serial.println(count_timer_1sec);  
  }
}

//Timer of 1 sec code
void Timer_1sec(uint16_t period0){
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // Enable Timer 0 Clock
  ROM_IntMasterEnable(); // Enable Interrupts
  ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC); // Configure Timer Operation as Periodic
  
  // Configure Timer Frequency
  // Frequency is given by MasterClock / CustomValue
  // Examples: 120MHz / 120k = 1000 kHz ; 120MHz / 120M = 1 Hz
  ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet()/period0);
  Serial.println(SysCtlClockGet()); 
  TimerIntRegister(TIMER1_BASE, TIMER_A, &Timer1IntHandler);
  //ROM_IntEnable(INT_TIMER1A);  // Enable Timer 0A Interrupt
  //ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // Timer 0A Interrupt when Timeout
  ROM_TimerEnable(TIMER1_BASE, TIMER_A); // Start Timer 0A
}



//void pauseOption()
//{
//  if(display->mode == GAME){
//    //strikeFlag = HIGH;
//    display->game->Create_New_Strike();
//  }
//  strikeFlag = LOW;
//}


// Add setup code
void setup() {
  Serial.begin(9600); //UART with its baudrate
  delay(100);
  //Declare inputs
  pinMode(Enter, INPUT_PULLUP);
  pinMode(joystickSEL, INPUT_PULLUP);
  pinMode(pushButton1, INPUT_PULLUP);
     
  display = new Display();
    
  display->screen->begin();
  display->screen->setOrientation(0);
    
  display->Initialize_Screen();  //Print first the message: "Airstrike Game"
  delay(2000);
    
  display->screen->clear();   //Go to the next page
    
  display->Display_Select_Type();   //User can choose between a new game or to load a saved game  

  attachInterrupt(joystickSEL, strikeInterrupt, FALLING); // Interrupt is fired whenever joystick button is pressed
  //attachInterrupt(pushButton1, pauseOption, FALLING); // Interrupt is fired whenever joystick button is pressed
  
  //display->game->Timer_1sec(uint16_t period0); //configure timer for hard game (timer of 1sec)
  Timer_1sec(50000);  //50000 * 1/80M = 1/1600
}


// Add loop code
void loop() {
  if(display->mode == SELECTTYPE || display->mode == SELECTDIFFICULTY || display->mode == PAUSE){
    display->Read_Joystick();
    display->Read_Enter();
    delay(200);  
  }

  else if(display->mode == GAME) {
    if (strikeFlag){
      strikeFlag = LOW;
    }
    display->game->Clear_Objects();
    display->game->Increment_Object_Positions();
    display->game->Place_Objects();
    display->Read_Enter();    //Change this to become an interrupt -->optimal
  }
}



