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
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
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

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            bigArm.manual_move(-100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            bigArm.manual_move(100);
        } else if (bigArm.manual) {
            bigArm.manual_move(0);
        }

        // front arms
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            toggleFrontRightArm();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            toggleFrontLeftArm();
        }

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            if (bot::goalClampClosed) {
                bot::toggleGoalClamp();
                autoMogoCnt = -10;
            }
        }

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && !bot::goalClampClosed) {
            autoMogoCnt++;
            if (autoMogoCnt > 10) {
                if (bot::mogoDist.get() < 40) {
                    bot::toggleGoalClamp();
                }
            }
        } else {
            if (autoMogoCnt > 0 && autoMogoCnt <= 10) {
                bot::toggleGoalClamp();
            }
            autoMogoCnt = 0;
        }
    }
}