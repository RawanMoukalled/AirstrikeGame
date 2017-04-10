#include "Target.h"

Target::Target() {
  Initialize_Parameters();
}

void Target::Initialize_Parameters() {
  x = 59;
  y = 5; 
  radius = 7; 
}

void Target::Move() {
  y += 10; 
}

