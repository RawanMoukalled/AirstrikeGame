#ifndef obstacle_h
#define obstacle_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>
#include "Airplane.h"

class Obstacle {
  public: 
    Obstacle();
    Obstacle(int x, int y, int len);
    void Initialize_Parameters(int x, int y, int len);
    void Move(Airplane *plane);
    bool On_Border();
    void Detect_Collision(Airplane *plane);

    Airplane *plane;
    int x1, y1, x2, y2;
    int len;
    bool collided;
    
};

#endif

