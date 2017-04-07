#ifndef target_h
#define target_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>

class Obstacle {
  public: 
    Obstacle();
    void Initialize_Parameters();
    void Move();
    
};

#endif
