#ifndef target_h
#define target_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>
#include "Airplane.h"

class Target {
  public: 
    Target(); //default constructor for new creation
    Target(int x, int y); //constructor for loaded games (premade target)
    void Initialize_Parameters(int x, int y);
    void Move();
    bool On_Border(Airplane *plane);
    
    bool struck;
    int x, y, radius;
};

#endif

