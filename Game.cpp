#include "Game.h"

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->triangle(40, 128, 60, 128, 50, 100, whiteColour);
}

