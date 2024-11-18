#pragma once

#include "main.h"

namespace auton {
    void FLAToggleFlipAware() {
        if (pid::PID_FLIPPED) {
            bot::toggleFrontRightArm();
        } else {
            bot::toggleFrontLeftArm();
        }
    }

    void FRAToggleFlipAware() {
        if (!pid::PID_FLIPPED) {
            bot::toggleFrontRightArm();
        } else {
            bot::toggleFrontLeftArm();
        }
    }
}