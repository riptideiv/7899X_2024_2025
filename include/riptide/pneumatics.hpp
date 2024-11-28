#pragma once

#include "main.h"

namespace bot {
    pros::adi::DigitalOut frontLeftArm('F'), frontRightArm('A');
    bool frontLeftArmDown = false, frontRightArmDown = false;

    pros::adi::DigitalOut goalClamp('H');
    bool goalClampClosed = false;

    void toggleFrontLeftArm() {
        frontLeftArmDown = !frontLeftArmDown;
        frontLeftArm.set_value(frontLeftArmDown);
    }

    void toggleFrontRightArm() {
        frontRightArmDown = !frontRightArmDown;
        frontRightArm.set_value(frontRightArmDown);
    }

    void toggleGoalClamp() {
        goalClampClosed = !goalClampClosed;
        goalClamp.set_value(goalClampClosed);
        MOGO = goalClampClosed;
    }
}