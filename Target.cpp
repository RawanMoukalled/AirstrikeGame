
#include "Target.h"

//target is going to have 2 constructors, one for loading and one for new game

//new game target constructor
Target::Target() {
  Initialize_Parameters(random(10,118), 24);
}

Target::Target(int x, int y) {
  Initialize_Parameters(x, y);
}
void Target::Initialize_Parameters(int x, int y) {
  this->x = x;
  this->y = y;
  this->radius = 7;
  struck = false;  
}

void Target::Move() {
  y += 10; 

}

bool Target::On_Border(Airplane *plane) {
  bool close_to_plane = (x>= plane->x1 && x <= plane->x3 && y >= plane->y2 - 5);
  if(!(y >= 24 && y <= 118) || close_to_plane) {
    return true;
  } else {
    return false;
  }
}

