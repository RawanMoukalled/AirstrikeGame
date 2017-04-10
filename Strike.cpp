#include "Strike.h"

Strike::Strike() {
  Initialize_Parameters();
  //airplane = new Airplane();
}

void Strike::Initialize_Parameters() {
  x = 0;
  y = 0; 
  radius = 5; 
}

void Strike::Move() {
  y -= 10; 
}

