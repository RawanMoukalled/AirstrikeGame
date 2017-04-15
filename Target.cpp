#include "Target.h"

//target is going to have 2 constructors, one for loading and one for new game

//new game target constructor
Target::Target() {
  Initialize_Parameters(random(0, 118), 24, random(7,9));
}

void Target::Initialize_Parameters(int x, int y, int radius) {
  this->x = x;
  this->y = y;
  this->radius = radius; 
}

void Target::Move() {
  y += 10; 
}


