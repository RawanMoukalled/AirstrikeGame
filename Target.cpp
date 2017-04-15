#include "Target.h"

Target::Target() {
  Initialize_Parameters();
}

void Target::Initialize_Parameters() {
  x = 70;
  y = 20; 
  radius = 7; 
}

void Target::Move() {
  y += 10; 
}


