#include "Target.h"

Target::Target() {
  Initialize_Parameters();
}

void Target::Initialize_Parameters() {
  x = 20;
  y = 20; 
  radius = 20; 
}

void Target::Move() {
  y += 10; 
}

