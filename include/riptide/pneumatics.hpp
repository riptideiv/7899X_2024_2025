#pragma once

#include "main.h"

namespace bot {
    pros::adi::DigitalOut frontLeftArm('F'), frontRightArm('C');
    bool frontLeftArmDown = false, frontRightArmDown = false;

    pros::adi::DigitalOut goalClamp('B');
    bool goalClampClosed = false;

    pros::adi::DigitalOut intakeLift('A');
    bool intakeLiftUp = false;

    void toggleFrontRightArm() {
        frontRightArmDown = !frontRightArmDown;
        frontRightArm.set_value(frontRightArmDown);
    }

    // toggleGoalClamp is in robot.hpp

    void toggleIntakeLift() {
        intakeLiftUp = !intakeLiftUp;
        intakeLift.set_value(intakeLiftUp);
    }

    void toggleFrontLeftArm() {
        // frontLeftArmDown = !frontLeftArmDown;
        // frontLeftArm.set_value(frontLeftArmDown);
        toggleIntakeLift();
    }
}