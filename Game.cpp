#include "Game.h"

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
  target = new Target();
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->setPenSolid(true);
  Place_Objects();
}

void Game::Clear_Objects() {
  screen->setPenSolid(true);

  //clear plane
  //screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , blackColour);
  screen->circle(target->x, target->y, target->radius, blackColour);
}

void Game::Increment_Object_Positions() {
  //plane->Move();    
  target->Move();
  delay(1000);
}

void Game::Place_Objects() {
  //screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
  screen->circle(target->x, target->y, target->radius, whiteColour);
}

void Game::Initialize_Objects() {
  plane->Initialize_Parameters();
}

