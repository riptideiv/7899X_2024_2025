#pragma once
#include "main.h"
namespace xrobot{
    extern double prevL,prevR,prevAngle,odomX,odomY;
    struct constants;
    void updatePos();
    void initTracking();
    pros::Task *odomTask;
}