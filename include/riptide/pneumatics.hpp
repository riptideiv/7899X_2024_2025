#pragma once

#include "main.h"

namespace bot {
    pros::adi::DigitalOut frontLeftArm('C'), frontRightArm('D');
    bool frontLeftArmDown = false, frontRightArmDown = false;

    pros::adi::DigitalOut goalClamp('A');
    bool goalClampClosed = false;

    pros::adi::DigitalOut intakeLift('E');
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
        frontLeftArmDown = !frontLeftArmDown;
        frontLeftArm.set_value(frontLeftArmDown);
        // toggleIntakeLift();
    }
}