#include "Game.h"
#include "Display.h"
#include <cmath>

Game::Game(Screen_HX8353E *screen){  
  this->screen = screen;
  plane = new Airplane();
  Initialize_Game();
}

void Game::Initialize_Game() {

  flag_random = 1;
  random_time = 20;

  score = 0; //initialize score to 0
  life = 3; 
  lifePos = 115;

  new_strike = false;
  pause = false;
  gameover = false;
}

void Game::Load_Game(String parameters) {

  String param = "";
  int pcount = 0;
  char c;
 
  for(int i = 0; i < parameters.length(); ++i) {
    c = parameters[i];
    if(c == ';') {
      
      int paramnum = 0;
      if((pcount >= 0 && paramnum <=10) || pcount == 14) {
        paramnum = param.toInt();  
      }
      
      if(pcount == 0) {
        flag_random = paramnum;
      } 
      
      else if (pcount == 1) {
        random_time = paramnum;
      }

      else if(pcount == 2) {
        score = paramnum;
      }

      else if(pcount == 3) {
       life = paramnum; 
      }

      else if(pcount == 4) {
        lifePos = paramnum;
      }

      else if(pcount == 5) {
        new_strike = paramnum;
      }

      else if(pcount == 6) {
        pause = paramnum;
      }

      else if(pcount == 7) {
        gameover = paramnum;
      }

      else if(pcount == 8) {
        flag_1sec = paramnum;
      }

      else if(pcount == 9) {
        remaining_time = paramnum;
      }

      else if(pcount == 10) {
        level = (level_t)paramnum;
      }

      else if(pcount == 11) {
        Load_Targets(param);
      }

      else if(pcount == 12) {
        Load_Obstacles(param);
      }

      else if(pcount == 13) {
        Load_Strikes(param);
      }

      else if(pcount == 14) {
        plane->Load_Parameters(paramnum);
      }
          
      pcount++;
      c = ' ';
      param = "";
      
    } 
    
    else {
      param+=c;
    }
  }
  
}

void Game::Load_Targets(String parameters) {
  
  String param = "";
  int pcount = 0;
  char c;
  std::vector<int> positions;
  
  for(int i = 0; i < parameters.length(); ++i) {
    c = parameters[i];
    if(c == ',') {
      positions.push_back(param.toInt());

      c = ' ';
      param = "";
    } 

    else {
      param += c;
    }    
  }

  for(std::vector<int>::iterator it = positions.begin(); it != positions.end(); it = it + 2) {
    targets.push_back(new Target((*it), (*(it+1))));
  }
}

void Game::Load_Obstacles(String parameters) {
    String param = "";
  int pcount = 0;
  char c;
  std::vector<int> positions;
  
  for(int i = 0; i < parameters.length(); ++i) {
    c = parameters[i];
    if(c == ',') {
      positions.push_back(param.toInt());

      c = ' ';
      param = "";
    } 

    else {
      param += c;
    }    
  }

  for(std::vector<int>::iterator it = positions.begin(); it != positions.end(); it = it + 2) {
    obstacles.push_back(new Obstacle((*it), (*(it+1))));
  }
}

void Game::Load_Strikes(String parameters) {
  String param = "";
  int pcount = 0;
  char c;
  std::vector<int> positions;
  
  for(int i = 0; i < parameters.length(); ++i) {
    c = parameters[i];
    if(c == ',') {
      positions.push_back(param.toInt());

      c = ' ';
      param = "";
    } 

    else {
      param += c;
    }    
  }

  for(std::vector<int>::iterator it = positions.begin(); it != positions.end(); it = it + 2) {
    strikes.push_back(new Strike((*it), (*(it+1))));
  }
}

void Game::Display_Game() {
  screen->clear(blackColour);
  screen->setFontSolid(false);
  screen->setFontSize(1);
  screen->setPenSolid(true);
  screen->gText(1, 5, "Score:");
  Place_Objects();  
  //CHANGE
  Draw_Life(); //Initialize Life
  Display_Score(); //Initialize score on Screen
  Display::Set_7Seg(remaining_time);
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
    Decrease_Life();
  } else {
    Color_Plane(whiteColour);
  }

  if(new_strike) {
    Create_New_Strike();
    new_strike = false;
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

void Game::Delete_All_Objects() {
  //first free memory then clear the vectors  
  for (std::vector<Strike*>::iterator it=strikes.begin(); it!=strikes.end(); ++it) {
    delete (*it);
  }
  for (std::vector<Target*>::iterator it=targets.begin(); it!=targets.end(); ++it) {
    delete (*it);
  }
  for (std::vector<Obstacle*>::iterator it=obstacles.begin(); it!=obstacles.end(); ++it) {
    delete (*it);
  }
  targets.clear();
  obstacles.clear();
  strikes.clear();
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
void Game::Draw_Life(){
  uint16_t color = blackColour;
  for(int i = 0; i < life; i++) {
    switch(i) {
      case 2: color = greenColour; break;
      case 1: color = yellowColour; break;
      case 0: color = redColour; break;
      default:;
    }
    screen->dRectangle(115 - 10*(2-i), 5, 10, 10, color);
  }
}

//Initialize Game score
void Game::Display_Score(){ 
  screen->dRectangle(50,5,30,10,blackColour);
  screen->gText(50, 5, String(score));
}

//Decrease the Life on the screen
void Game::Decrease_Life(){
  screen->dRectangle(lifePos, 5, 10, 10, blackColour);
  lifePos -= 10;
  life--;
  if(life == 0) {
    gameover = true;
  }
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
  //Color_Strikes(yellowColour);
}

void Game::Increment_Timer_Flag() {
  flag_1sec++;
}

void Game::Decrease_Remaining_Time() {
  remaining_time--;
}

void Game::Set_Level(level_t level) {
  this->level = level;
  if(level == HARD){
    this->flag_1sec = 1;
    this->remaining_time = 150; //in seconds 
  } else {
    this->flag_1sec = 1;
    this->remaining_time = 0;
  }
}

