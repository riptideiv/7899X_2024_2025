#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace blue {
    void neg_rrush() {}

    void neg6_1() {

    }

    void pos_trush() {
        mv2pt(6.01001, 29.5364, 1000, { .minSpeed = 1, .earlyExitRange = 10 });
        mv2pt(6.01001, 29.5364, 1000, { .minSpeed = 100, .earlyExitRange = 2 });
        toggleFrontRightArm();
        swing2pt(13.7675, 53.9935, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(13.7675, 53.9935, 1000, { .minSpeed = 1, .earlyExitRange = 11 });
    }
}