#pragma once

#include "main.h"

#include "../auton.hpp"

#include "plus.hpp"
#include "minus.hpp"

namespace auton {
    enum class Color { Red, Blue };
    enum class Side { Plus, Minus };
    enum class Mode { Risk, Safe };

    // Color selectedColor = Color::Red;
    Side selectedSide = Side::Plus;
    Mode selectedMode = Mode::Risk;
    bool AWP = false;

    bool FLIPPED = false;

    pros::Task *autonSelectTask;

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", "(N/A)", selectedSide == Side::Plus ? "Right" : "Left");
        pros::delay(100);
        bot::master.print(2, 0, "%s;; %s    ", AWP ? "Mid" : "NoMid", selectedMode == Mode::Risk ? "Risk" : "Safe");
    }

    void runSelectedAuton() {
        bot::set_brake_mode(pros::MotorBrake::brake);

        // if (selectedColor == Color::Blue) {
        //     FLIPPED = true;
        // } else {
        //     FLIPPED = false;
        // }

        if (selectedSide == Side::Plus) {
            if (selectedMode == Mode::Risk) {
                if (AWP) {
                    plusRiskAWP();
                } else {
                    plusRiskNoAWP();
                }
            } else {
                if (AWP) {
                    plusSafeAWP();
                } else {
                    plusSafeNoAWP();
                }
            }
        } else {
            if (selectedMode == Mode::Risk) {
                if (AWP) {
                    minusRiskAWP();
                } else {
                    minusRiskNoAWP();
                }
            } else {
                if (AWP) {
                    minusSafeAWP();
                } else {
                    minusSafeNoAWP();
                }
            }
        }
    }

    void autonSelectLoop() {
        printf("Auton select loop started\n");
        pros::delay(500);
        bot::master.clear();
        pros::delay(100);
        displaySelectedAuton();
        while (!pros::competition::is_disabled()) {
            bool update = 0;

            // if (bot::master.get_digital_new_press(DIGITAL_X)) {
            //     selectedColor = (selectedColor == Color::Red) ? Color::Blue : Color::Red;
            //     update = 1;
            // }

            if (bot::master.get_digital_new_press(DIGITAL_A)) {
                selectedSide = (selectedSide == Side::Plus) ? Side::Minus : Side::Plus;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_B)) {
                selectedMode = (selectedMode == Mode::Risk) ? Mode::Safe : Mode::Risk;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_Y)) {
                AWP = !AWP;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_LEFT) ||
                bot::master.get_digital_new_press(DIGITAL_RIGHT) ||
                bot::master.get_digital_new_press(DIGITAL_UP) ||
                bot::master.get_digital_new_press(DIGITAL_DOWN)) {
                runSelectedAuton();
            }

            if (bot::master.get_digital_new_press(DIGITAL_L1) ||
                bot::master.get_digital_new_press(DIGITAL_L2) ||
                bot::master.get_digital_new_press(DIGITAL_R1) ||
                bot::master.get_digital_new_press(DIGITAL_R2)) {
                bot::bigArm.reset();
                // bot::getChass()->setPose(0, 0, 90);
                break;
            }

            pros::delay(20); // Add a small delay to prevent CPU overuse

            if (!update) continue;

            // Display the selected attributes on the controller screen
            displaySelectedAuton();
        }
        printf("Auton select loop ended.\n");
    }
}