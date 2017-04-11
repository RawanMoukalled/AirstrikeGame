#include "Game.h"
#include <cmath>


Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
  target = new Target();
  //obstacle = new Obstacle();
  strike = new Strike();
  score[4] = 0;
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->setPenSolid(true);
  Place_Objects();  
  Initialize_Life(); //Initialize Life
}

void Game::Clear_Objects() {
  screen->setPenSolid(true);

  //clear plane
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , blackColour);
  screen->circle(target->x, target->y, target->radius, blackColour);
  if (strike->x != 0 and strike->y != 0)
  {
    screen->circle(strike->x, strike->y, strike->radius, blackColour);
  }
  //delay(10);
}

void Game::Increment_Object_Positions() {
  plane->Move();    
  target->Move();


  //Move the strike
  if (strike->x != 0 and strike->y != 0)
  {
    strike->Move();
  }
  
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
//
// if ( distance(target->x, target->y, strike->x, strike->y) <= (target->radius + strike->radius) )
//  {
//    score[0] += 1;
//    tm1637.display(0,score[0]);
//    tm1637.display(1,score[1]);
//    tm1637.display(2,score[2]);
//    tm1637.display(3,score[3]);
//
//    if (score[0] == 9){
//      score[0] = 0;
//      score[1] += 1;
//    }
//    if (score[0] == 9 && score[1] ==9){
//      score[0] = 0;
//      score[1] = 0;
//      score[2] +=1;
//    }
//    if (score[0] == 9 && score[1] == 9 && score[2] == 9){
//      score[0] = 0;
//      score[1] = 0;
//      score[2] = 0;
//      score[3] +=1;
//    }    

//    
//    screen->circle(target->x, target->y, target->radius, blackColour); //Instead of this function, delete the target
//  }
  
  //delay(50);
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

double Game::distance(int x1, int y1, int x2, int y2) {
  return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
}

