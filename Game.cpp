#include "Game.h"

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
  target = new Target();
  //obstacle = new Obstacle();
  strike = new Strike();
  count_timer_1sec = 100;
  flag_1sec = 1;
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->setPenSolid(true);
  Place_Objects();  
  Initialize_Life(); //Initialize Life
  Start_Timer_1sec(); //
}

void Game::Clear_Objects() {
  screen->setPenSolid(true);

  //clear plane
  //screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , blackColour);
  screen->circle(target->x, target->y, target->radius, blackColour);
  if (strike->x != 0 and strike->y != 0)
  {
    screen->circle(strike->x, strike->y, strike->radius, blackColour);
  }
  //delay(10);
}

void Game::Increment_Object_Positions() {
  //plane->Move();    
  target->Move();
  Serial.println(target->y);
  Serial.println(plane->y2);

  //Move the strike
  if (strike->x != 0 and strike->y != 0)
  {
    strike->Move();
  }
  
  //In case of collision between plane and target
  if (target->y  == plane->y2)
  {
    plane-> planeLife -=1;  //decrease plane's life
    Change_Plane_Color();
    if (plane->planeLife == 0)
    {
      //GameOver    
    }
    else{
      Decrease_Life();  //decrease the life bar on the screen
    }
  }

  if (strike->y - target->y < 10 )
  {
    score += 1;
    screen->circle(target->x, target->y, target->radius, blackColour);
  }
  
  Serial.println(plane->planeLife);
  delay(50);
}

void Game::Place_Objects() {
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
  screen->circle(target->x, target->y, target->radius, whiteColour);
  if (strike->x != 0 and strike->y != 0)
  {
    screen->circle(strike->x, strike->y, strike->radius, yellowColour);
  }
  delay(200);
}


void Game::Initialize_Life(){
  screen->dRectangle(115,5,10,10,greenColour);
  screen->dRectangle(105,5,10,10,yellowColour);
  screen->dRectangle(95,5,10,10,redColour);
}

//Create a new strike target and store its values here
void Game::Create_New_Strike(){
  strike->x = plane->x2;
  strike->y = plane->y2-5;
  screen->circle(strike->x, strike->y, strike->radius, yellowColour);
  //delay(100);
}

void Game::Initialize_Objects() {
  plane->Initialize_Parameters();
  target->Initialize_Parameters();
}


//Decrease the Life on the screen
void Game::Decrease_Life(){
  screen->dRectangle(plane->planeLifeX,5,10,10,blackColour);
  plane->planeLifeX -= 10;
}

//in case of collision with target
void Game::Change_Plane_Color(){
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , redColour);
  delay(200);
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
}   
