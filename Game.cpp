#include "Game.h"
#include <cmath>

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
 
  //Timer variables
  flag_1sec = 1;
  remaining_time = 120; //in seconds

  flag_random = 1;
  random_time = 20;

  score = 0; //initialize score to 0
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->setPenSolid(true);
  screen->gText(1, 5, "Score:");
  Place_Objects();  
  //CHANGE
  Initialize_Life(); //Initialize Life
  Display_Score(); //Initialize score on Screen
}

void Game::Clear_Objects() {
  screen->setPenSolid(true);

  //clear plane
  Color_Plane(blackColour);
  Color_Targets(blackColour);
  Color_Strikes(blackColour);
  Color_Obstacles(blackColour);
  Delete_Struck_Targets();
}

void Game::Increment_Object_Positions() {
  plane->Move(); // increment plane position
  
  //increment target positions
  for(std::vector<Target*>::iterator it = targets.begin(); it != targets.end(); ++it) {
    (*it)->Move();
  }
  
  //increment strikes positions
  for(std::vector<Strike*>::iterator it = strikes.begin(); it != strikes.end(); ++it) {
    (*it)->Move();
  }

  //increment obstacles positions
  for(std::vector<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it) {
    (*it)->Move(plane);
  }

  Delete_Outlier_Targets();
  Delete_Outlier_Strikes();
  Delete_Outlier_Obstacles();
}

void Game::Place_Objects() {
    
  Detect_Strike_Hits();    
  Delete_Expired_Strikes();

  if(plane->collided){
    Color_Plane(redColour);
    plane->collided = false;
  } else {
    Color_Plane(whiteColour);
  }
  
  Color_Targets(whiteColour);
  Color_Strikes(yellowColour);
  Color_Obstacles(whiteColour);
  delay(100);
}

void Game::Delete_Outlier_Targets() {
    for (std::vector<Target*>::iterator it=targets.begin(); it!=targets.end(); ) {
     if((*it)->On_Border(plane)) {
        delete (*it);
        it = targets.erase(it);
     } else { 
        ++it;
     }
   }
}

void Game::Delete_Outlier_Obstacles() {
    for (std::vector<Obstacle*>::iterator it=obstacles.begin(); it!=obstacles.end(); ) {
     if((*it)->On_Border()) {
        delete (*it);
        it = obstacles.erase(it);
     } else { 
        ++it;
     }
   }  
}

void Game::Delete_Outlier_Strikes() {
  for (std::vector<Strike*>::iterator it=strikes.begin(); it!=strikes.end(); ) {
    if((*it)->On_Border()) {
      delete (*it);
      it = strikes.erase(it);
    } else { 
      ++it;
    }
   }
}

void Game::Delete_Struck_Targets() {
  for (std::vector<Target*>::iterator it=targets.begin(); it!=targets.end(); ) {
    if((*it)->struck) {
      delete (*it);
      it = targets.erase(it);
      score += 10;
      Display_Score(); 
    } else { 
      ++it;
    }
   }
}

void Game::Delete_Expired_Strikes() {
     for (std::vector<Strike*>::iterator it=strikes.begin(); it!=strikes.end(); ) {
    if((*it)->expired) {
      screen->circle((*it)->x, (*it)->y, (*it)->radius, blackColour);
      delete (*it);
      it = strikes.erase(it);
    } else { 
      ++it;
    }
   }
}

void Game::Color_Targets(const uint16_t color) {
  for(std::vector<Target*>::iterator it = targets.begin(); it != targets.end(); ++it) {
    if(color != blackColour && (*it)->struck) {
      //means it has been hit by the strike
      screen->circle((*it)->x, (*it)->y, (*it)->radius, greenColour); 
    } else {
      screen->circle((*it)->x, (*it)->y, (*it)->radius, color);
    }
  }
}

void Game::Color_Obstacles(const uint16_t color) {
    for(std::vector<Obstacle*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it) {
    //if(color != blackColour && (*it)->struck) {
      //means it has been hit by the strike
      //screen->dRectangle((*it)->x, (*it)->y, (*it)->radius, greenColour); 
    //} else {
      screen->rectangle((*it)->x1, (*it)->y1, (*it)->x2, (*it)->y2, color);
    //}
  }  
}

void Game::Color_Strikes(const uint16_t color) {
  for(std::vector<Strike*>::iterator it = strikes.begin(); it != strikes.end(); ++it) {
    screen->circle((*it)->x, (*it)->y, (*it)->radius, color); 
  }
}

void Game::Color_Plane(const uint16_t color) {
  screen->triangle(plane->x1, plane->y1, plane->x2, plane->y2, plane->x3, plane->y3 , color);
}

void Game::Detect_Strike_Hits() { 
 for(std::vector<Strike*>::iterator strike = strikes.begin(); strike != strikes.end(); ++strike) {
   for(std::vector<Target*>::iterator target = targets.begin(); target != targets.end(); ++target) {
     if( (*strike)->Hit(*target)) {
       (*target)->struck = true;
       (*strike)->expired = true;
       
     }
   }
 }
}

//Initialize Airplane Life on screen
void Game::Initialize_Life(){
  screen->dRectangle(115,5,10,10,greenColour);
  screen->dRectangle(95,5,10,10,redColour);
}

//Initialize Game score
void Game::Display_Score(){ 
  screen->dRectangle(50,5,30,10,blackColour);
  screen->gText(50, 5, String(score));
}


void Game::Initialize_Objects() {
//  plane->Initialize_Parameters();
}


//Decrease the Life on the screen
void Game::Decrease_Life(){
  screen->dRectangle(plane->planeLifeX, 5, 10, 10, blackColour);
  plane->planeLifeX -= 10;
}

//Increase score on screen
void Game::Increase_score(){
  screen->dRectangle(50,5,10,10,blackColour);
  screen->gText(50,5,String(score));
}

void Game::Generation_Timer() {
  flag_random +=1;   
  if (flag_random == random_time){
    flag_random = 1;
    random_time = random(5, 20);
    int object_type = random(0,2);
    if(object_type == 0){
      targets.push_back(new Target());
    } else {
      obstacles.push_back(new Obstacle());  
    }
  } 
}

void Game::Create_New_Strike() {
  strikes.push_back(new Strike(plane->x2, plane->y2 - 5));
  Color_Strikes(yellowColour);
}

void Game::Hard_Timer() {
  
}
