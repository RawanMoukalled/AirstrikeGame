#include "Display.h"
#include <string>
#include <sstream>

Display::Display() {
  screen  = &(Display::screen_main);  
  game = new Game(screen);
  
  tm1637 = new TM1637(39, 38);   
  tm1637->init();
  tm1637->set(BRIGHT_TYPICAL);

  Display::Set_7Seg(0);

  right_after_display = true;
}

TM1637* Display::tm1637;

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

    else if (mode == SELECTDIFFICULTY || mode == PAUSE || mode == LOADGAME) {
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

void Display::Display_Load_Game() {
  mode = LOADGAME;
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->gText(25, 10, "Load Game");
  arrowX = 3;
  arrowY = 50;
  screen->gText(arrowX, arrowY, ">");
  
  screen->gText(15, 50, "1)");
  screen->gText(15, 70, "2)");
  screen->gText(15, 90, "3)");

  for(int i = 0; i < 5; i++) {
    
    if( i == 0) {
      screen->gText(30, 50, "Game 1");
    } else if (i == 1) {
      screen->gText(30, 70, "Game 2");
    } else if (i == 2) {
      screen->gText(30, 90, "Game 3");
    }
  }
  
}

//Displays new page according to the position of the arrow 
//which means, which menu item position was selected
void Display::Display_New_Page(uint16_t y) {
  
  if(mode == SELECTTYPE){
    //new game
    if(y == 50){
      Display_Select_Difficulty();
    }
    //load game
    else if(y == 70) {
      Display_Load_Game();
    }
  } 
  
  else if(mode == SELECTDIFFICULTY) {
    //easy mode
    if(y == 50){
      right_after_display = true;
      mode = GAME;
      game->Set_Level(EASY);
      game->Display_Game();
    } 
    //hard mode
    else if(y == 70) {
      right_after_display = true;
      mode = GAME;
      game->Set_Level(HARD);
      game->Display_Game();
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
      game->Initialize_Game();
      game->Delete_All_Objects();
      Display::Set_7Seg(0);
      Display_Select_Type();
    }

    //save and exit
    else if(y == 70) {
      //restore game objects to initial state in case of
      //future new game 
      game->Initialize_Game();
      game->Delete_All_Objects();
      Display::Set_7Seg(0);
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

  else if(mode == LOADGAME) {
    
    //Query Game 1
    if( y == 50) {
      
    } 

    //Query Game 2
    else if ( y == 70) {
      
    }
    
    //Query Game 3
    else if (y == 90) {
      
    }

    game->Load_Game("1;12;19;20;2;105;0;0;0;3;100;1;98,50,34,60,;80,80,;95,50,;20;");
    mode = GAME;
    game->Display_Game();
  }
}

// check for the push button being pressed
void Display::Read_Enter() {
  //display mode 
  if(mode == SELECTTYPE || mode == SELECTDIFFICULTY || mode == GAME || mode == PAUSE || mode == LOADGAME){
    delay(1000);
    Serial.println("pressed");
    Display_New_Page(arrowY);
    
  }
}

void Display::Display_Game_Over() {
  mode = GAMEOVER; 
  screen->setPenSolid(true);
  screen->rectangle(10, 50, 120, 90, whiteColour);
  screen->setFontSolid(false);
  screen->setFontSize(2);
  screen->gText(12, 65, "GAME OVER", blackColour);
  
  game->Initialize_Game();
  game->Delete_All_Objects();
  Display::Set_7Seg(0);
  delay(3000);
  Display_Select_Type();
  
}

void Display::Set_7Seg(int num) {
   int seconds = num%60; 
   int mins = num/60;
    
   
   //tm1637->display(0,(num/1000)%10);
   //tm1637->display(1,(num/100)%10);
   tm1637->display(1, mins);
   
   tm1637->display(2,(seconds/10)%10);
   tm1637->display(3,seconds%10);
   
}



