#pragma once
#include "pros/apix.h"

namespace xrobot {
    extern double prevL, prevR, prevS, prevAngle, odomX, odomY;
    void updatePos(bool log);
    void initTracking();
    extern pros::Task *odomTask;
}