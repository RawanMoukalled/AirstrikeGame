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
/// @date April 21, 2017
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
#define blueLED 37 //blue LED on joystick board
#define greenLED 38 //green LED on joystick board 
#define redLED 39 //red LED on joystick board 

#define Enter 32 //pin for the Push button
#define EnterUpper 33 //pin for the upper push button

Display * display;
volatile uint16_t flag_1sec = 1; 
volatile uint8_t count_timer_1sec = 100;

volatile uint16_t flag_random = 1; 
volatile uint16_t count_timer_random = 1000;

//Prototypes
void ReadEnterIntHandler();
void StrikeIntHandler();
void Timer1IntHandler(void);
void Timer_1sec(uint16_t period0);
void Timer_Random(uint16_t period0);


// Add setup code
void setup() {
  Serial.begin(9600); //UART with its baudrate
  delay(100);
  
  //Declare inputs
  pinMode(Enter, INPUT_PULLUP);
  pinMode(joystickSEL, INPUT_PULLUP);

  //turn off green and blue LEDs
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
      
  display = new Display();
  display->screen->begin();
  display->screen->setOrientation(0);  
  display->Initialize_Screen();  //Print first the message: "Airstrike Game"
  delay(2000);  
  display->screen->clear();   //Go to the next page
  display->Display_Select_Type();   //User can choose between a new game or to load a saved game  

  attachInterrupt(Enter, ReadEnterIntHandler, FALLING);
  attachInterrupt(EnterUpper, ReadEnterIntHandler, FALLING);
}

void loop() {  
  if(display->mode == SELECTTYPE || display->mode == SELECTDIFFICULTY || display->mode == PAUSE){
    display->Read_Joystick();
    delay(200);  
  }

  else if(display->mode == GAME) {
    display->game->Clear_Objects();
    display->game->Increment_Object_Positions();
    display->game->Place_Objects();
  }
}

void ReadEnterIntHandler() {
  if(display->mode == SELECTTYPE || display->mode == SELECTDIFFICULTY || display->mode == PAUSE){
    display->Read_Enter();
  }
  
  if(display->mode == GAME){
    //right after loading a new game onto the screen using the enter pushbutton,
    //the same enter is being read after loading the game and so the create strike function 
    //is called. so this boolean prevents it from being called the first time, and then enables it
    if(display->right_after_display) {
      display->right_after_display = false;
    } else {
      display->game->Create_New_Strike();
    }
  }
  
  delay(100);
}

void StrikeIntHandler() {
  if(display->mode == GAME){
    display->game->Create_New_Strike();
  }
}

void Timer1IntHandler(void){
  //Required to launch next interrupt
  ROM_TimerIntClear(TIMER1_BASE, TIMER_A);
  flag_1sec +=1;
  if (flag_1sec == 1600){
      count_timer_1sec -=1;
  }
}

void TimerRandomIntHandler(void){
    if(display->mode == GAME) {
      display->game->Generation_Timer();
    }
}


//Timer of 1 sec code
void Timer_1sec(uint16_t period0){
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // Enable Timer 1 Clock
  ROM_IntMasterEnable(); // Enable Interrupts
  ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC); // Configure Timer Operation as Periodic
  
  // Configure Timer Frequency
  // Frequency is given by MasterClock / CustomValue
  ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, SysCtlClockGet()/period0);
  TimerIntRegister(TIMER1_BASE, TIMER_A, &Timer1IntHandler);
  ROM_IntEnable(INT_TIMER1A);  // Enable Timer 1A Interrupt
  ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // Timer 1A Interrupt when Timeout
  ROM_TimerEnable(TIMER1_BASE, TIMER_A); // Start Timer 1A
}

//Timer of 1 sec code
void Timer_Random(uint16_t period0){
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); // Enable Timer 0 Clock
  ROM_IntMasterEnable(); // Enable Interrupts
  ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Configure Timer Operation as Periodic
  
  // Configure Timer Frequency
  // Frequency is given by MasterClock / CustomValue
  ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/period0);
 TimerIntRegister(TIMER0_BASE, TIMER_A, &TimerRandomIntHandler);
  ROM_IntEnable(INT_TIMER0A);  // Enable Timer 0A Interrupt
  ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Timer 0A Interrupt when Timeout
  ROM_TimerEnable(TIMER0_BASE, TIMER_A); // Start Timer 0A
}




