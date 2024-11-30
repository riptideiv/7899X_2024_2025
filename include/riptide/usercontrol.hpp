#pragma once

#include "main.h"

namespace bot {
    int autoMogoCnt = 0;

    void handleControllerInput() {
        if (auton::autonSelectTask->get_state() != pros::E_TASK_STATE_DELETED) {
            return;
        }

#ifndef DISABLE_DRIVING
        // driving
        double leftStickY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double rightStickX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        getChass()->arcade(leftStickY, rightStickX);
#endif

        // intake
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            spin_intk(100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            spin_intk(-100);
        } else {
            spin_intk(0);
        }

        // big arm
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            bigArm.raiseToScore();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            bigArm.toggleUp();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            bigArm.reset();
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            bigArm.manual_move(-100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            bigArm.manual_move(100);
        } else if (bigArm.manual) {
            bigArm.manual_move(0);
        }

        // front arms
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
            toggleFrontRightArm();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            toggleFrontLeftArm();
        }

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            toggleGoalClamp();
        }
    }
}