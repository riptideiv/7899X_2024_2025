#pragma once

namespace riptide {
    void initialize();
    void autonomous();
    void opcontrol();
    void testChassisSpeedDifference();
}

#include "config.hpp"
#include "robot.hpp"
#include "pid.hpp"
#include "auton.hpp"
#include "display.hpp"
#include "usercontrol.hpp"
#include "tests.hpp"

namespace riptide {
    void initialize() {
        bot::initialize();
        auton::initialize();
        display::initialize();
        pid::initialize();
    }

    void disabled() {
        while (1) {
            bot::bigArm.reset();
            pros::delay(100);
            bot::deactivate_all_pistons();
        }
    }

    void autonomous() {
        auton::runSelectedAuton();
    }

    void opcontrol() {
        while (1) {
            bot::handleControllerInput();
            pros::delay(20);
        }
    }
}