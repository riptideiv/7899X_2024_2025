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
            bot::deactivate_all_pistons();
        }
    }

    void autonomous() {
        // test::pidTune();
        auton::runSelectedAuton();
    }

    void opcontrol() {
        // test::pidTune();
        while (1) {
            bot::handleControllerInput();
            test::handleDebugInputs();
            pros::delay(20);
        }
    }
}