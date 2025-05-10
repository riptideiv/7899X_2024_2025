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
            auton_running = false;
            bot::bigArm.reset();
            pros::delay(100);
            if (bot::intakeLiftUp) bot::toggleIntakeLift();
            if (bot::frontRightArmDown) bot::toggleFrontRightArm();
            if (bot::frontLeftArmDown) bot::toggleFrontLeftArm();
            if (auton::selectedRoute == 0) bot::deactivate_all_pistons();
        }
    }

    void autonomous() {
        // turn2hd(180, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 80 });
        // test::testMotorAccels();
        auton::runSelectedAuton();
    }

    void opcontrol() {
        // getChass()->setPose(0, 0, 0);
        // getChass()->moveToPoint(0, 48, 5000);
        // test::pidTune();
        while (1) {
            bot::handleControllerInput();
            pros::delay(8);
        }
    }
}