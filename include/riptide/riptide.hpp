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
            if (bot::frontRightArmDown) bot::toggleFrontRightArm();
            if (auton::selectedRoute == 0) bot::deactivate_all_pistons();
        }
    }

    void autonomous() {
        // turn2hd(180, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 80 });
        intake.set_colorsort(0, 0);
        spin_intk(100);
        int minVal = 0x7fffffff;
        int maxVal = 0;
        for (int i = 333; i--;) {
            pros::delay(3);
            if (colorSortSensor.get_proximity() > 200) {
                if (colorSortSensor.get_hue() < minVal) minVal = colorSortSensor.get_hue();
                if (colorSortSensor.get_hue() > maxVal) maxVal = colorSortSensor.get_hue();
            }
        }
        std::cout << "minVal: " << minVal << std::endl;
        std::cout << "maxVal: " << maxVal << std::endl;
        // test::testMotorAccels();
        auton::runSelectedAuton();
        auton::autonSelectTask->remove();
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