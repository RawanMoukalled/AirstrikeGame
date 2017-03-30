#include "Game.h"



Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
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
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , blackColour);
}

void Game::Increment_Object_Positions() {
  plane->Move();    
  delay(500);
}

void Game::Place_Objects() {
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , whiteColour);
}

void Game::Initialize_Objects() {
  plane->Initialize_Parameters();
}

