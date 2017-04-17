#ifndef strike_h
#define strike_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>

#include "Airplane.h"
#include "Target.h"
#include <cmath>

class Strike {
  public: 
    Strike(int x, int y);
    void Initialize_Parameters(int x, int y);
    void Move();
    bool On_Border();
    bool Hit(Target *t);
    bool expired; //it already hit a target, should be deleted
    
    int x, y, radius;
    Airplane *airplane;
};

#endif

