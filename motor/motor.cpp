#include "motor.h"

Motor::Motor(PinName m11, PinName m12, PinName m21, PinName m22) :
 _m11(m11), _m12(m12), _m21(m21), _m22(m22)
{
    _m11 = _m12 = _m21 = _m22 = 0;
}

void Motor::forward(){
    _m12 = _m22 = 0;
    _m11 = _m21 = 1;
    wait(0.1);
}

void Motor::back(){
    _m11 = _m21 = 0;
    _m12 = _m22 = 1;
    wait(0.1);
}

void Motor::right(){
    _m12 = _m21 = _m22 = 0;
    _m11 = 1;
    wait(0.1);
}

void Motor::left(){
    _m11 = _m12 = _m22 = 0;
    _m21 = 1;
    wait(0.1);
}

void Motor::stop(){
    _m11 = _m12 = _m21 = _m22 = 0;
    wait(0.1);
}

void Motor::turnRight(){
    _m12 = _m21 = 0;
    _m11 = _m22 = 1;
    wait(0.1);
}

void Motor::turnLeft(){
    _m11 = _m22 = 0;
    _m12 = _m21 = 1;
    wait(0.1);
}