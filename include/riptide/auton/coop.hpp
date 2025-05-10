#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace auton {
    void coopSlot() {
        toggleIntakeLift();
        toggleGoalClamp();
        pros::delay(500);
        cornerMacro();
    }
}