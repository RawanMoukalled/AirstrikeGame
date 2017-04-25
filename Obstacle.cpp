#include "Obstacle.h"

Obstacle::Obstacle() {
  Initialize_Parameters(random(10, 118), 20);
}

Obstacle::Obstacle(int x, int y) {
  Initialize_Parameters(x, y);
}

void Obstacle::Initialize_Parameters(int x, int y) {
  this->x1 = x;
  this->y1 = y; 
  this->len = 11;
  this->x2 = x + len;
  this->y2 = y + len;
  collided = false;
}

void Obstacle::Move(Airplane *plane) {
  y1+=7;
  y2+=7;
  if(!collided && (y2 >= (plane->y2))) {
    Detect_Collision(plane); 
  }
}

bool Obstacle::On_Border() {
  if(!(y2 >= 24 && y2 <= 125)) {
    return true;
  } else {
    return false;
  }
}

void Obstacle::Detect_Collision(Airplane *plane) {
  int lx = x2 - len;
  bool leftSide = (x2 >= plane->x1) &&(x2 <= plane->x3);
  bool rightSide = (lx >= plane->x1) && ( lx <= plane->x3);
  if( leftSide || rightSide ) {
    collided = true;
    plane->collided = true;  
  }
}

