#pragma once

#include "main.h"
#include<iostream>
#include<vector>

namespace bot {
    struct keybinds {
        pros::controller_digital_e_t debugPrint;
        pros::controller_digital_e_t colorSortToggle;
        pros::controller_digital_e_t intakeIn;
        pros::controller_digital_e_t intakeOut;
        pros::controller_digital_e_t intakeLiftToggle;
        pros::controller_digital_e_t bigArmRaise;
        pros::controller_digital_e_t bigArmToggle;
        pros::controller_digital_e_t bigArmDown;
        pros::controller_digital_e_t bigArmUp;
        pros::controller_digital_e_t frontRightArmToggle;
        pros::controller_digital_e_t frontLeftArmToggle;
        pros::controller_digital_e_t mogoToggle;
    };

    std::vector<keybinds> keybindsList = {
        {
            .debugPrint = pros::E_CONTROLLER_DIGITAL_UP,
            .colorSortToggle = pros::E_CONTROLLER_DIGITAL_DOWN,
            .intakeIn = pros::E_CONTROLLER_DIGITAL_R1,
            .intakeOut = pros::E_CONTROLLER_DIGITAL_R2,
            .intakeLiftToggle = pros::E_CONTROLLER_DIGITAL_LEFT,
            .bigArmRaise = pros::E_CONTROLLER_DIGITAL_X,
            .bigArmToggle = pros::E_CONTROLLER_DIGITAL_A,
            .bigArmDown = pros::E_CONTROLLER_DIGITAL_L2,
            .bigArmUp = pros::E_CONTROLLER_DIGITAL_L1,
            .frontRightArmToggle = pros::E_CONTROLLER_DIGITAL_Y,
            .frontLeftArmToggle = pros::E_CONTROLLER_DIGITAL_RIGHT,
            .mogoToggle = pros::E_CONTROLLER_DIGITAL_B
        },
        {
            .debugPrint = pros::E_CONTROLLER_DIGITAL_UP,
            .colorSortToggle = pros::E_CONTROLLER_DIGITAL_DOWN,
            .intakeIn = pros::E_CONTROLLER_DIGITAL_R1,
            .intakeOut = pros::E_CONTROLLER_DIGITAL_R2,
            .intakeLiftToggle = pros::E_CONTROLLER_DIGITAL_Y, // asking michael rn
            .bigArmRaise = pros::E_CONTROLLER_DIGITAL_X,
            .bigArmToggle = pros::E_CONTROLLER_DIGITAL_A,
            .bigArmDown = pros::E_CONTROLLER_DIGITAL_L2,
            .bigArmUp = pros::E_CONTROLLER_DIGITAL_L1,
            .frontRightArmToggle = pros::E_CONTROLLER_DIGITAL_LEFT,
            .frontLeftArmToggle = pros::E_CONTROLLER_DIGITAL_RIGHT,
            .mogoToggle = pros::E_CONTROLLER_DIGITAL_B
        }
    };

    int autoMogoCnt = 0;

    bool toggleMogo = 0;
    pros::Task toggleMogoTask([]() {
        while (pros::Task::notify_take(true, TIMEOUT_MAX)) {
            bot::toggleGoalClamp();
            pros::Task::delay(25);
            bot::master.rumble(".");
        }
        });

    void handleControllerInput() {
        if (auton::autonSelectTask->get_state() != pros::E_TASK_STATE_DELETED) {
            return;
        }

        bot::intake.doAntiStuck = true;

        // debug & program
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            std::cout << (bot::chass[0]->getPose().x) << ", " << (bot::chass[0]->getPose().y) << ", " << (bot::chass[0]->getPose().theta) << std::endl;
        }

        // fix colorsort
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            intake.colorSortRed = !intake.colorSortRed;
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
        // intake lift
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            toggleIntakeLift();
        }

        // big arm
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            bigArm.raise();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            bigArm.toggleUp();
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            bigArm.manual_move(-100);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            bigArm.manual_move(100);
        } else if (bigArm.manual) {
            bigArm.manual_move(0);
        }

        // front arms
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            toggleFrontRightArm();
        }
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            toggleFrontLeftArm();
        }

        // mogo
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            if (bot::goalClampClosed) {
                bot::toggleGoalClamp();
                autoMogoCnt = -30;
            }
        }
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B) && !bot::goalClampClosed) {
            autoMogoCnt++;
            if (autoMogoCnt > 10) {
                if (bot::mogoInRange()) {
                    toggleMogoTask.notify();
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