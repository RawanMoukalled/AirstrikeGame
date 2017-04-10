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
  
  if(newX3 <= 128 && newX1 >= 0) {
    x1=newX1;
    x2+=delta;
    x3=newX3;
  }
}

////check the airplane Life
//void Airplane::Plane_Life(){
//  planeLife -=1;
//}

