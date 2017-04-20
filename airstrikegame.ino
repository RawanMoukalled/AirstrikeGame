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

#define blueLED 37 //blue LED on joystick board
#define greenLED 38 //green LED on joystick board 
#define redLED 39 //red LED on joystick board 

#define Enter 32 //pin for the Push button
#define BUZZER_PIN 40
#define JoystickPress 5 //pin for the upper push button 

Display * display;
volatile uint16_t flag_1sec = 1; 
volatile uint8_t count_timer_1sec = 100;

//Prototypes
void ReadEnterIntHandler();
void ReadJoystickPressIntHandler();
void Timer1IntHandler(void);
void Timer_1sec(uint16_t period0);


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

  pinMode(BUZZER_PIN, OUTPUT);  
  //digitalWrite(BUZZER_PIN, HIGH);
  //delay(200);
  //digitalWrite(BUZZER_PIN, LOW);
      
  display = new Display();
  display->screen->begin();
  display->screen->setOrientation(0);  
  display->Initialize_Screen();  //Print first the message: "Airstrike Game"
  delay(2000);  
  display->screen->clear();   //Go to the next page
  display->Display_Select_Type();   //User can choose between a new game or to load a saved game  
  
  randomSeed(analogRead(0)); //seed for generating random numbers

  attachInterrupt(Enter, ReadEnterIntHandler, FALLING);
  attachInterrupt(JoystickPress, ReadJoystickPressIntHandler, FALLING);

  Timer_1sec(50000);
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
    display->game->Generation_Timer();
  }
}

void ReadJoystickPressIntHandler() {
  if(display->mode == GAME) {
    display->Read_Enter();
  }
}

void ReadEnterIntHandler() {
  if(display->mode == SELECTTYPE || display->mode == SELECTDIFFICULTY || display->mode == PAUSE){
    display->Read_Enter();
    delay(100);
  }
  else if(display->mode == GAME){
    //right after loading a new game onto the screen using the enter pushbutton,
    //the same enter is being read after loading the game and so the create strike function 
    //is called. so this boolean prevents it from being called the first time, and then enables it
    if(display->right_after_display) {
      display->right_after_display = false;
    } else {
      //display->game->Create_New_Strike();
      display->game->new_strike = true;
      delay(100);
    }
  } 
}

void Timer1IntHandler(void){
  //Required to launch next interrupt
  ROM_TimerIntClear(TIMER1_BASE, TIMER_A);
  if(display->mode == GAME && display->game->level == HARD) {
    display->game->Increment_Timer_Flag();
  
    if (display->game->flag_1sec == 450){
      display->game->Decrease_Remaining_Time();
      //Serial.println(display->game->remaining_time);
      Display::Set_7Seg(display->game->remaining_time);
    }
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

