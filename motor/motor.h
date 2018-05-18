#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "mbed.h"

class Motor{
public:
    Motor(PinName m11,
          PinName m12,
          PinName m21,
          PinName m22
          );

    void forward();
    void back();
    void right();
    void left();
    void stop();
    void turnRight();
    void turnLeft();
    
private:
    DigitalOut _m11;
    DigitalOut _m12;
    DigitalOut _m21;
    DigitalOut _m22;
};

#endif