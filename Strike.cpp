#include "Strike.h"

Strike::Strike(int x, int y) {
  Initialize_Parameters(x, y);
}

void Strike::Initialize_Parameters(int x, int y) {
  this->x = x;
  this->y = y;
  this->radius = 3;
  this->expired = false;
}

void Strike::Move() {
  y -= 10; 
}

bool Strike::On_Border() {
  if(!(y >= 24 && y <= 118)) {
    return true;
  } else {
    return false;
  }
}

bool Strike::Hit(Target *t) {
   Serial.println("entered function");
  bool hit = false;
  double distance = sqrt( (x - t->x)*(x - t->x) + (y - t->y)*(y - t->y)  );
  if(distance <= (radius + t->radius) ) {
    hit = true;
  }
   Serial.println("exited function");
      
  return hit;
}

