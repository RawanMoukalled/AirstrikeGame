#ifndef airplane_h
#define airplane_h

#if defined(ENERGIA) // LaunchPad MSP430, Stellaris and Tiva, Experimeter Board FR5739 specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

// Following includes for Energia only
#include <SPI.h>

#define xAxisPin 23                  // x-axis of the accelerometer
//#define ypin 24                  // y-axis
//#define zpin 25                  // z-axis (only on 3-axis models)

class Airplane {
  public: 
    Airplane();
    void Move();
    void Change_Points(int delta);
    void Initialize_Parameters();
    
    int x1, y1, x2, y2, x3, y3; // lcd positions for the triangle
    int currX, prevX; //x axis positions for the accelerometer
    
};

#endif
