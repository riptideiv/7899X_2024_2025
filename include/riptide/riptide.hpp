#pragma once

namespace riptide {
    void initialize();
    void autonomous();
    void opcontrol();
}

#include "config.hpp"
#include "pidConsts.hpp"
#include "robot.hpp"
#include "auton.hpp"
#include "display.hpp"
#include "usercontrol.hpp"
#include "tests.hpp"

namespace riptide {
    void initialize() {
        bot::initialize();
        auton::initialize();
        display::initialize();
    }

    void disabled() {
        while (1) {
            bot::bigArm.reset();
            pros::delay(100);
            if (bot::intakeLiftUp) bot::toggleIntakeLift();
            if (auton::selectedRoute == 0) bot::deactivate_all_pistons();
        }
    }

    void autonomous() {
        auton::runSelectedAuton();
    }

    void opcontrol() {
        while (1) {
            bot::handleControllerInput();
            pros::delay(8);
        }
    }
}