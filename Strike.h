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

class Strike {
  public: 
    Strike();
    void Initialize_Parameters();
    void Move();
    int x, y, radius;
    Airplane *airplane;
};

#endif
