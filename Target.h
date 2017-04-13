#ifndef target_h
#define target_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>

class Target {
  public: 
    Target();
    void Initialize_Parameters();
    void Move();
    int x, y, radius;
};

#endif

