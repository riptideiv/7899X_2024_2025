#pragma once

#include "main.h"

#include "../auton.hpp"

#include "plus.hpp"
#include "minus.hpp"

namespace auton {
    enum class Color { Red, Blue };
    enum class Side { Plus, Minus };
    enum class Mode { Rush, Safe };

    Color selectedColor = Color::Red;
    Side selectedSide = Side::Plus;
    Mode selectedMode = Mode::Rush;
    bool AWP = true;

    pros::Task *autonSelectTask;

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", selectedSide == Side::Plus ? "Plus" : "Minus");
        pros::delay(100);
        bot::master.print(2, 0, "%s;; %s    ", AWP ? "AWP" : "Elims", selectedMode == Mode::Rush ? "Rush" : "Safe");
    }

    void runSelectedAuton() {
        bot::set_brake_mode(pros::MotorBrake::brake);

        if (selectedColor == Color::Blue) {

        } else {

        }

        if (selectedSide == Side::Plus) {
            if (selectedMode == Mode::Rush) {
                if (AWP) {
                    plusRushAWP();
                } else {
                    plusRushNoAWP();
                }
            } else {
                if (AWP) {
                    plusSafeAWP();
                } else {
                    plusSafeNoAWP();
                }
            }
        } else {
            if (selectedMode == Mode::Rush) {
                if (AWP) {
                    minusRushAWP();
                } else {
                    minusRushNoAWP();
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
        bot::master.clear();
        pros::delay(100);
        displaySelectedAuton();
        while (!pros::competition::is_disabled()) {
            bool update = 0;

            if (bot::master.get_digital_new_press(DIGITAL_X)) {
                selectedColor = (selectedColor == Color::Red) ? Color::Blue : Color::Red;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_A)) {
                selectedSide = (selectedSide == Side::Plus) ? Side::Minus : Side::Plus;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_B)) {
                selectedMode = (selectedMode == Mode::Rush) ? Mode::Safe : Mode::Rush;
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