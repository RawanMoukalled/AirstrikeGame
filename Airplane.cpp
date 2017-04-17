#include "Airplane.h"

Airplane::Airplane() {
  Initialize_Parameters();
}

void Airplane::Initialize_Parameters() {
  x1 = 48;
  y1 = 128;
  x2 = 59;
  y2 = 115;
  x3 = 70;
  y3 = 128;
  currX = 1400; // initialize x axis position as straight horizontal
  planeLife = 3;
  planeLifeX = 115; //location of the life (keep track of the life)
}

void Airplane::Load_Parameters(int x1, int y1, int x2, int y2, int x3, int y3, int currX) {
  this->x1 = x1;
  this->y1 = y1;
  this->x2 = x2;
  this->y2 = y2;
  this->x3 = x3;
  this->y3 = y3;
  this->currX = currX; // initialize x axis position as straight horizontal
}

//read accelerometer values and decide whether to move left or right
void Airplane::Move() {
  
  //update previous and current positions
  prevX = currX;
  currX = (int)analogRead(xAxisPin);
  
  if(currX < 1090) {
    currX = 1090;
  } else if(currX > 1800) {
    currX = 1800;
  }
  currX = map(currX, 1090, 1800, 0, 128);
  Change_Points((currX-prevX));  
  
}

//change values of the three triangle points according to accelerometer input
void Airplane::Change_Points(int delta) {
  int newX3 = x3 + delta;
  int newX1 = x1 + delta;
  
  if(newX3 < 128 && newX1 > 0) {
    x1=newX1;
    x2+=delta;
    x3=newX3;
  }
}

////check the airplane Life
//void Airplane::Plane_Life(){
//  planeLife -=1;
//}


