#include "Obstacle.h"

Obstacle::Obstacle(int x, int y) {
  Initialize_Parameters(x, y);
}

void Obstacle::Initialize_Parameters(int x, int y) {
  this->x = x;
  this->y = y; 
}

void Obstacle::Move() {
  y+=10;
}


