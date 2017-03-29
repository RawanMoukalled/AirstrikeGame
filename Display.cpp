#include "Display.h"

Display::Display() {
  screen  = &(Display::screen_main);  
}
 

// Display Airstrike Game 
void Display::Initialize_Screen(){
  screen->clear(cyanColour);
  screen->setFontSolid(true);
  screen->setFontSize(1);
  screen->gText(13, 50, "AirStrike Game");
}

//Select between a new game or loading one 
void Display::Display_Select_Type(){
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

void Display::Place_Arrow(uint16_t x, uint16_t y){
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
void Display::Read_Joystick() {
  
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

void Display::Display_Select_Difficulty() {
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
void Display::Display_New_Page(uint16_t y) {
  
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
      game = new Game(screen);
      mode = GAME;
      game->Display_Game();
      Serial.println("easy");
    } 
    //hard mode
    else if(y == 70) {
       Serial.println("hard");
    }
    //back to select type
    else if(y == 90) {
      Display_Select_Type();
    }
  } 
}

// check for the push button being pressed
void Display::Read_Enter() {
  int enterState = digitalRead(Enter);
  
  //button has been pushed
  if(enterState == LOW) {
    if(mode == SELECTTYPE || mode == SELECTDIFFICULTY){
      Display_New_Page(arrowY);
    } 
  }

}
