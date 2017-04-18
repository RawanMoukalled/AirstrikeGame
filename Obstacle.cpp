#include "Obstacle.h"

Obstacle::Obstacle() {
  Initialize_Parameters(random(10, 118), 20 ,10);
}

Obstacle::Obstacle(int x, int y, int len) {
  Initialize_Parameters(x, y, len);
}

void Obstacle::Initialize_Parameters(int x, int y, int len) {
  this->x = x;
  this->y = y; 
  this->len = len;
}

void Obstacle::Move() {
  y+=10;
}

bool Obstacle::On_Border() {
  if(!(y >= 24 && y <= 118)) {
    return true;
  } else {
    return false;
  }
}

