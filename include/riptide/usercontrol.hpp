#pragma once

#include "main.h"

namespace bot {
    void handleControllerInput() {
#ifndef DISABLE_DRIVING
        // driving
        double leftStickY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double rightStickX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        double leftPower = leftStickY + rightStickX;
        double rightPower = leftStickY - rightStickX;

        pwrChassPct(leftPower, rightPower);
#endif

        // intake
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            pwrIntakePct(100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            pwrIntakePct(-100);
        } else {
            pwrIntakePct(0);
        }

        // front arms
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
            toggleFrontRightArm();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            toggleFrontLeftArm();
        }

        // big arm
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            pwrBigArmPct(100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            pwrBigArmPct(-100);
        } else {
            pwrBigArmPct(0);
        }

        // goal clamp
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            toggleGoalClamp();
        }
    }
}