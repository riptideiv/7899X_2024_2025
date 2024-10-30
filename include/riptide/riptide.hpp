#pragma once

#include "config.hpp"
#include "robot.hpp"
#include "usercontrol.hpp"

namespace riptide {
    void initialize() {
        bot::initialize();
    }

    void autonomous() {}

    void opcontrol() {
        while (1) {
            bot::handleControllerInput();
            pros::delay(20);
        }
    }
}