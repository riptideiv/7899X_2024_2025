#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void autonSkills() {
        bot::bigArm.reset();
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;


    }
}