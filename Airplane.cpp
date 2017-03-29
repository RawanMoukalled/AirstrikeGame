#include "Airplane.h"

Airplane::Airplane() {
  x1 = 48;
  y1 = 128;
  x2 = 64;
  y2 = 109;
  x3 = 80;
  y3 = 128;

}

//increment the three triangle coordinates 
void Airplane::Move(int increment) {
  //Serial.println(((int) analogRead(xpin))); 
  xAxisPos = (int)analogRead(xAxisPin);
  if(x1 >= 32  
}

