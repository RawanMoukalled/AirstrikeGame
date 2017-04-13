#ifndef obstacle_h
#define obstacle_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>

class Obstacle {
  public: 
    Obstacle(int x, int y);
    void Initialize_Parameters(int x, int y);
    void Move();

    int x, y;
    
};

#endif
