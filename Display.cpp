#include "Display.h"
#include <string>
#include <sstream>

Display::Display() {
  screen  = &(Display::screen_main);  
  
  tm1637 = new TM1637(39, 38);   
  tm1637->init();
  tm1637->set(BRIGHT_TYPICAL);

  Set_7Seg(9999);

  right_after_display = true;
}
 

// Display Airstrike Game 
void Display::Initialize_Screen(){
  screen->clear(cyanColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->gText(13, 50, "AirStrike Game", blackColour);
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
  screen->gText(25, 10, "Airstrike!");
  screen->gText(15, 50, "New Game");
  screen->gText(15, 70, "Load Game");
}

void Display::Place_Arrow(uint16_t x, uint16_t y){
    uint16_t minY, maxY;
    if(mode == SELECTTYPE) {
      minY = 50; 
      maxY = 70;
    } 

    else if (mode == SELECTDIFFICULTY || mode == PAUSE) {
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

void Display::Display_Paused_Game() {
  mode = PAUSE;
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->gText(40, 10, "Pause");
  arrowX = 3;
  arrowY = 50;
  screen->gText(arrowX, arrowY, ">");
  screen->gText(15, 50, "Exit");
  screen->gText(15, 70, "Save and Exit");
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
      right_after_display = true;
      game = new Game(screen);
      mode = GAME;
      game->Display_Game();
     
    } 
    //hard mode
    else if(y == 70) {
      delay(50);
    }
    //back to select type
    else if(y == 90) {
      Display_Select_Type();
    }
  }

  else if(mode == PAUSE) {

    //exit
    if(y == 50) {
      //restore game objects to initial state in case of
      //future new game 
      game->Initialize_Objects();
      Display_Select_Type();
    }

    //save and exit
    else if(y == 70) {
      //restore game objects to initial state in case of
      //future new game 
      game->Initialize_Objects();
      Display_Select_Type();
    }

    //back to game
    else if(y == 90) {
      mode = GAME;
      game->Display_Game();
    }
  }

  else if(mode == GAME) {
    Display_Paused_Game();
  }
}

// check for the push button being pressed
void Display::Read_Enter() {
      if(mode == SELECTTYPE || mode == SELECTDIFFICULTY || mode == GAME || mode == PAUSE){
        Display_New_Page(arrowY);
        //NEW
        delay(100);
  }
}

void Display::Set_7Seg(int num) {
   tm1637->display(0,(num/1000)%10);
   tm1637->display(1,(num/100)%10);
   tm1637->display(2,(num/10)%10);
   tm1637->display(3,num%10);
}



