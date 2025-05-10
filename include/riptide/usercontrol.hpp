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
        pros::controller_digital_e_t frontRightArmToggle;
        pros::controller_digital_e_t frontLeftArmToggle;
        pros::controller_digital_e_t mogoToggle;
    };

    std::vector<keybinds> keybindsList = {
        { // ryan
            .debugPrint = pros::E_CONTROLLER_DIGITAL_RIGHT,
            .colorSortToggle = pros::E_CONTROLLER_DIGITAL_DOWN,
            .intakeIn = pros::E_CONTROLLER_DIGITAL_R1,
            .intakeOut = pros::E_CONTROLLER_DIGITAL_A,
            .intakeLiftToggle = pros::E_CONTROLLER_DIGITAL_DOWN,
            .frontRightArmToggle = pros::E_CONTROLLER_DIGITAL_UP,
            .frontLeftArmToggle = pros::E_CONTROLLER_DIGITAL_LEFT,
            .mogoToggle = pros::E_CONTROLLER_DIGITAL_R2
        },
        { // alt
            .debugPrint = pros::E_CONTROLLER_DIGITAL_UP,
            .colorSortToggle = pros::E_CONTROLLER_DIGITAL_UP,
            .intakeIn = pros::E_CONTROLLER_DIGITAL_R1,
            .intakeOut = pros::E_CONTROLLER_DIGITAL_R2,
            .intakeLiftToggle = pros::E_CONTROLLER_DIGITAL_DOWN,
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

    void debugPrint() {
        std::cout << "x,y,theta: " << (bot::chass[0]->getPose().x) << ", " << (bot::chass[0]->getPose().y) << ", " << (bot::chass[0]->getPose().theta) << ", bigArm: " << (bot::bigArm.rotation->get_position()) << std::endl;
    }

    bool skillsMacroRan = 0;

    void handleControllerInput() {
        if (!auton_ran || auton_running) {
            pros::delay(50);
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
            while (intake.mtr->get_position() < 520) pros::delay(3);
            pros::delay(50);
            spin_intk(-50);
            getChass()->setPose(0, (distAvg / 5 - 151) * 0.0393701, 0);

            // get mogo
            mv2pt(0, 11, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
            spin_intk(0);
            turn2pt(20.6659, 12.5, 600, { .forwards = false });
            toggleFrontRightArm(); // expand the aligner
            mv2pt(20.6659, 12.5, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 12 });
            mv2pt(20.6659, 12.5, 1000, { .forwards = false, .maxSpeed = 40, .minSpeed = 30, .earlyExitRange = 3 });
            toggleGoalClamp();
            pros::delay(150);
            toggleFrontRightArm();
        }

        bot::bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

        bot::intake.doAntiStuck = true;

        // // debug & program
        // if (master.get_digital_new_press(keybindsList[selectedKeybinds].debugPrint)) {
        //     debugPrint();
        // }
        if (master.get_digital_new_press(keybindsList[selectedKeybinds].colorSortToggle)) {
            intake.colorSortRed = !intake.colorSortRed;
            debugPrint();
        }

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
        if (selectedKeybinds == 1) { // alt
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
                bigArm.raise();
            }
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
                bigArm.toggleUp();

                double gravityTheta = (bigArm.rotation->get_position() - 18193) / 18000.0 * M_PI;
                std::cout << "Gravity: " << gravityTheta << std::endl;
                std::cout << "sin: " << std::sin(gravityTheta) << std::endl;
            }
            // if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            //     bigArm.reset();
            // }
            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
                bigArm.manual_move(100);
            } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
                bigArm.manual_move(-100);
            } else if (bigArm.manual) {
                bigArm.manual_move(0);
            }
        } else if (selectedKeybinds == 0) { // ryan
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
                bigArm.cycle();
            }
            if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
                if (bigArm.move_target > posHigh) {
                    bigArm.set_target(posHigh);
                } else {
                    bigArm.set_target(posLow);
                }
            }
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
            bot::toggleGoalClamp();
        }
    }
}