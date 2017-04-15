#include "Game.h"
#include <cmath>

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
  target = new Target();
  //obstacle = new Obstacle();
  //CHANGE
  strike = new Strike();

  flag_1sec = 1;
  remaining_time = 120; //in seconds

  flag_random = 1;
  count_timer_random = 10; //placeholder value to be later determined

  score = 0; //initialize score to 0
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->setPenSolid(true);
  Place_Objects();  
  //CHANGE
  Initialize_Life(); //Initialize Life
  Initialize_Score(); //Initialize score on Screen
}

void Game::Clear_Objects() {
  screen->setPenSolid(true);

  //clear plane
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , blackColour);
  screen->circle(target->x, target->y, target->radius, blackColour);

  //CHANGE
  //if strike goes out of the screen delete it
  if (strike->x != 0 and strike->y != 0)
  {
    screen->circle(strike->x, strike->y, strike->radius, blackColour);
  }
  //delay(10);
}

void Game::Increment_Object_Positions() {
  plane->Move();    
  target->Move();


  //CHANGE move if it's still in the bound obv
  //Move the strike
  if (strike->y != 20)
  {
    strike->Move();
  }

  //CHANGE
  //In case of collision between plane and target
  if (distance(target->x, target->y, plane->x1, plane->y1)  <= target->radius || distance(target->x, target->y, plane->x2, plane->y2)  <= target->radius || distance(target->x, target->y, plane->x3, plane->y3)  <= target->radius )
  {
    plane-> planeLife -=1;  //decrease plane's life
    Change_Plane_Color();
    //DELETE THE TARGET
    if (plane->planeLife == 0)
    {
      //GameOver    
    }
    else{
      Decrease_Life();  //decrease the life bar on the screen
    }
  }

 if ( distance(target->x, target->y, strike->x, strike->y) <= (target->radius + strike->radius) )
  {
    score += 1;
    Increase_score();
  }
  
  
}

void Game::Place_Objects() {
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
  screen->circle(target->x, target->y, target->radius, whiteColour);
  if (strike->x != 0 and strike->y != 0)
  {
    screen->circle(strike->x, strike->y, strike->radius, yellowColour);
  }
  delay(100);
}

//Initialize Airplane Life on screen
void Game::Initialize_Life(){
  screen->dRectangle(115,5,10,10,greenColour);
  screen->dRectangle(105,5,10,10,yellowColour);
  screen->dRectangle(95,5,10,10,redColour);
}

//Initialize Game score
void Game::Initialize_Score(){
  screen->gText(1, 5, "Score:");
  screen->gText(50, 5, String(score));
}

//Create a new strike target and store its values here
void Game::Create_New_Strike(){
  strike->x = plane->x2;
  strike->y = plane->y2-5;
  screen->circle(strike->x, strike->y, strike->radius, yellowColour);  
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

//Increase score on screen
void Game::Increase_score(){
  screen->dRectangle(50,5,10,10,blackColour);
  screen->gText(50,5,String(score));
}


//in case of collision with target
void Game::Change_Plane_Color(){
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , redColour);
  delay(200);
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
}   

double Game::distance(int x1, int y1, int x2, int y2) {
  return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

void Game::Hard_Timer() {
  
}

void Game::Generation_Timer() {
   //Required to launch next interrupt
  ROM_TimerIntClear(TIMER0_BASE, TIMER_A);
  flag_random +=1;
  if (flag_random == 8000){
      count_timer_random -=1;
      Serial.println(count_timer_random);
  } 
}


