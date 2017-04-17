#include "Game.h"
#include <cmath>

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
 
  //Timer variables
  flag_1sec = 1;
  remaining_time = 120; //in seconds

  flag_random = 1;
  random_time = 20;

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
  for(std::vector<Target*>::iterator it = targets.begin(); it != targets.end(); ++it) {
      screen->circle((*it)->x, (*it)->y, (*it)->radius, blackColour); 
  }

  
}

void Game::Increment_Object_Positions() {
  plane->Move(); // increment plane position
  //increment target positions

  for(std::vector<Target*>::iterator it = targets.begin(); it != targets.end(); ++it) {
    (*it)->Move();
  }

  for (std::vector<Target*>::iterator its=targets.begin(); its!=targets.end(); ) 
  {
     if((*its)->On_Border()) 
        its = targets.erase(its);
    else 
        ++its;
   }

}

void Game::Place_Objects() {
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
  for(std::vector<Target*>::iterator it = targets.begin(); it != targets.end(); ++it) {
      screen->circle((*it)->x, (*it)->y, (*it)->radius, whiteColour); 
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
//void Game::Create_New_Strike(){
//  strike->x = plane->x2;
//  strike->y = plane->y2-5;
//  screen->circle(strike->x, strike->y, strike->radius, yellowColour);  
//}

void Game::Initialize_Objects() {
//  plane->Initialize_Parameters();
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
  flag_random +=1;   
  if (flag_random == random_time){
    flag_random = 1;
    random_time = random(5, 20);
    targets.push_back(new Target);
    Serial.print("targets size: ");
    Serial.println(targets.size());   
  } 
}


