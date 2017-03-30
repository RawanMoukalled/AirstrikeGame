#include "Airplane.h"

Airplane::Airplane() {
  Initialize_Parameters();
}

void Airplane::Initialize_Parameters() {
  x1 = 48;
  y1 = 128;
  x2 = 64;
  y2 = 109;
  x3 = 80;
  y3 = 128;
  currX = 1400; // initialize x axis position as straight horizontal
}

//read accelerometer values and decide whether to move left or right
void Airplane::Move() {
  
  //update previous and current positions
  prevX = currX;
  currX = (int)analogRead(xAxisPin);
  Change_Points(10*(currX-prevX));  
}

//change values of the three triangle points according to accelerometer input
void Airplane::Change_Points(int delta) {
  int newX3 = x3 + delta;
  int newX1 = x1 + delta;
  
  if(newX3 <= 128 && newX1 >= 0) {
    x1=newX1;
    x2+=delta;
    x3+=newX3;
  }
}

