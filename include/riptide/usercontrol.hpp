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
        { // xr_c
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
        { // alt_f4_jpg
            .debugPrint = pros::E_CONTROLLER_DIGITAL_UP,
            .colorSortToggle = pros::E_CONTROLLER_DIGITAL_UP,
            .intakeIn = pros::E_CONTROLLER_DIGITAL_R1,
            .intakeOut = pros::E_CONTROLLER_DIGITAL_R2,
            .intakeLiftToggle = pros::E_CONTROLLER_DIGITAL_DOWN,
            .bigArmRaise = pros::E_CONTROLLER_DIGITAL_X,
            .bigArmToggle = pros::E_CONTROLLER_DIGITAL_A,
            .bigArmDown = pros::E_CONTROLLER_DIGITAL_L2,
            .bigArmUp = pros::E_CONTROLLER_DIGITAL_L1,
            .frontRightArmToggle = pros::E_CONTROLLER_DIGITAL_RIGHT,
            .frontLeftArmToggle = pros::E_CONTROLLER_DIGITAL_LEFT,
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

    void alliStakeMacro() {
        bool immed = bigArm.move_target >= bigArm.posHigh;
        getChass()->setPose(0, 0, 0);
        if (immed) {
            bigArm.setMaxSpeed(70);
            bigArm.set_target(14300);
            bigArm.kP = 5;
        }
        mv2pt(0, -8.5, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 3 });
        if (!immed) {
            bigArm.setMaxSpeed(70);
            bigArm.set_target(14300);
            bigArm.kP = 5;
        }
        mv2pt(0, -8.5, 500, { .forwards = false }, true);
        while (getChass()->isInMotion() && bigArm.rotation->get_position() > 15650) pros::delay(3);
        getChass()->cancelAllMotions();
        pros::delay(10);
        drWait(1, 1, -4);
        bigArm.setMaxSpeed(100);
        bigArm.reset();
    }

    void debugPrint() {
        std::cout << "x,y,theta: " << (bot::chass[0]->getPose().x) << ", " << (bot::chass[0]->getPose().y) << ", " << (bot::chass[0]->getPose().theta) << ", lWall: " << (bot::lWallDist.get()) << ", rWall: " << (bot::rWallDist.get()) << ", mogoDist: " << (bot::mogoDist.get()) << std::endl;
    }

    bool skillsMacroRan = 0;

    void handleControllerInput() {
        if (auton::autonSelectTask->get_state() != pros::E_TASK_STATE_DELETED) {
            return;
        }

        set_brake_mode(pros::MotorBrake::coast);

        if (auton::selectedRoute == 0 && !skillsMacroRan) {
            skillsMacroRan = true;
            bigArm.reset();

            // alliance stake
            intake.mtr->set_zero_position(0);
            spin_intk(100);
            double distAvg = 0;
            for (int i = 0; i < 5; i++) {
                distAvg += mogoDist.get();
                pros::delay(5);
            }
            while (intake.mtr->get_position() < 500) pros::delay(5);
            pros::delay(100);
            spin_intk(-50);
            getChass()->setPose(0, (distAvg / 5 - 151) * 0.0393701, 0);

            // get mogo
            mv2pt(0, 11, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
            spin_intk(0);
            turn2pt(20.6659, 12.5, 600, { .forwards = false });
            toggleFrontRightArm(); // expand the aligner
            mv2pt(20.6659, 12.5, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 12 });
            toggleFrontRightArm();
            mv2pt(20.6659, 12.5, 1000, { .forwards = false, .maxSpeed = 40, .minSpeed = 30, .earlyExitRange = 3 });
            toggleGoalClamp();
            pros::delay(150);
        }

        bot::intake.doAntiStuck = true;

        // // debug & program
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].debugPrint)) {
            debugPrint();
        }

        // // fix colorsort
        // if (master.get_digital_new_press(keybindsList[selectedKeybinds].colorSortToggle)) {
        //     intake.colorSortRed = !intake.colorSortRed;
        // }

        // alliance stake macro
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            alliStakeMacro();
        }

#ifndef DISABLE_DRIVING
        // driving
        double leftStickY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        double rightStickX = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        getChass()->arcade(leftStickY, rightStickX);
#endif

        // intake
        if (master.get_digital(keybindsList[selectedKeybinds].intakeIn)) {
            spin_intk(100);
        } else if (master.get_digital(keybindsList[selectedKeybinds].intakeOut)) {
            spin_intk(-100);
        } else {
            spin_intk(0);
        }
        // intake lift
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].intakeLiftToggle)) {
            toggleIntakeLift();
        }

        // big arm
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].bigArmRaise)) {
            bigArm.raise();
        }
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].bigArmToggle)) {
            bigArm.toggleUp();
        }
        if (master.get_digital(keybindsList[selectedKeybinds].bigArmDown)) {
            bigArm.manual_move(-100);
        } else if (master.get_digital(keybindsList[selectedKeybinds].bigArmUp)) {
            bigArm.manual_move(100);
        } else if (bigArm.manual) {
            bigArm.manual_move(0);
        }

        // front arms
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].frontRightArmToggle)) {
            toggleFrontRightArm();
        }
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].frontLeftArmToggle)) {
            toggleFrontLeftArm();
        }

        // mogo
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].mogoToggle)) {
            if (bot::goalClampClosed) {
                bot::toggleGoalClamp();
                autoMogoCnt = -30;
            }
        }
        if (master.get_digital(keybindsList[selectedKeybinds].mogoToggle) && !bot::goalClampClosed) {
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