#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton{
    void autonSkills(){
        bot::bigArm.reset();
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
        bot::spin_intk(100);
        pros::delay(550);
        mv2pt(0, 10, 1000);
    }
}