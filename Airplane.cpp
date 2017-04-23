#include "Airplane.h"

Airplane::Airplane() {
  Initialize_Parameters();
  y1 = 128;
  y2 = 115;
  y3 = 128;
  collided = false;
}

void Airplane::Initialize_Parameters() {
  x1 = 48;
  x2 = 59;
  x3 = 70;
  currX = 1400; // initialize x axis position as straight horizontal
}

void Airplane::Load_Parameters(int x1) {
  this->x1 = x1;
  this->x2 = x1 + 11;
  this->x3 = x1 + 22;
  this->currX = map(x1, 0, 128, 1700, 2350);
}

//read accelerometer values and decide whether to move left or right
void Airplane::Move() {
  
  //update previous and current positions
  prevX = currX;
  currX = (int)analogRead(xAxisPin);

  
  if(currX < 1700) {
    currX = 1700;
  } else if(currX > 2350) {
    currX = 2350;
  }
  currX = map(currX, 1700, 2350, 0, 128);
  Change_Points((currX-prevX));  


//  if(currX < 1250) {
//    currX = 1250;
//  } else if(currX > 1650) {
//    currX = 1650;
//  }
//  currX = map(currX, 1250, 1650, 0, 128);
//  Change_Points((currX-prevX));  
  
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



