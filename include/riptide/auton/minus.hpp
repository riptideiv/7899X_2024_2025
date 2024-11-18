#pragma once

#include "autonUtils.hpp"
#include "main.h"

using pid::drive, pid::driveWait, pid::arcWait, pid::turn, pros::delay;

namespace auton {
    void minusRushAWP() {
        arcWait(90, 0.8, -0.8, true);
        printf("minusRushAWP was run\n");
    }
    void minusRushNoAWP() {
        printf("minusRushNoAWP was run\n");
    }
    void minusSafeAWP() { // line up with back on driver's wall, line up end of drivetrain's outer c channel to the third tooth on the row closer to the driver's wall for red, or the row farther for blue, -90 deg for red or 90 deg for blue
        drive(-525, 800);
        bot::bigArm.set_target(12500);
        turn(0, 700, false);
        drive(-400, 550);
        bot::bigArm.set_target(bot::bigArm.posHigh + 200);
        delay(500);
        bot::pwrIntakePct(100);
        delay(400);
        bot::pwrIntakePct(0);
        delay(250);

        driveWait(200, 0.8, 0.8, true);
        turn(140, 1000, false);
        bot::bigArm.reset();
        bot::pwrIntakePct(-100);

        driveWait(-500, 0.8, 0.8, true);
        driveWait(-800, 0.4, 0.4, false);
        bot::toggleGoalClamp();
        pid::set_mogo(true);
        driveWait(-900, 0.4, 0.4, false);
        turn(270, 1000, false);
        printf("minusSafeAWP was run\n");
    }
    void minusSafeNoAWP() {
        printf("minusSafeNoAWP was run\n");
    }
}