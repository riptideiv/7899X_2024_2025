#pragma once

#include "main.h"

#include "../auton.hpp"

#include "plus.hpp"
#include "minus.hpp"
#include "skills.hpp"

namespace auton {
    enum class Color { Red, Blue };
    enum class Side { Plus, Minus };
    bool Coop = true;

    Color selectedColor = Color::Red;
    Side selectedSide = Side::Plus;
    int selectedRoute = 1;

    std::string routeDisplay[] = { "SoloWP", "Elims", "2S_Pos" };

    pros::Task *autonSelectTask;

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", selectedSide == Side::Plus ? "Plus" : "Minus");
        pros::delay(100);
        bot::master.print(2, 0, "%s;; %s    ", routeDisplay[(int)selectedRoute], Coop ? "COOP" : "PRESET");
    }

    void runSelectedAuton() {
        bot::set_brake_mode(pros::MotorBrake::brake);

        if (Coop) {
            coopSlot();
        } else {
            if (selectedSide == Side::Plus) {
                if (selectedColor == Color::Red) {
                    switch (selectedRoute) {
                    case 0:
                        plusRedSoloWP();
                        break;
                    case 1:
                        plusRedElims();
                        break;
                    case 2:
                        // plusRedTwoStakePosCorner();
                        break;
                    }
                } else {
                    switch (selectedRoute) {
                    case 0:
                        plusBlueSoloWP();
                        break;
                    case 1:
                        plusBlueElims();
                        break;
                    case 2:
                        // minusBlueTwoStakePosCorner();
                        break;
                    }
                }
            } else {
                if (selectedColor == Color::Red) {
                    switch (selectedRoute) {
                    case 0:
                        minusRedSoloWP();
                        break;
                    case 1:
                        minusRedElims();
                        break;
                    case 2:
                        // minusRedTwoStakePosCorner();
                        break;
                    }
                } else {
                    switch (selectedRoute) {
                    case 0:
                        minusBlueSoloWP();
                        break;
                    case 1:
                        minusBlueElims();
                        break;
                    case 2:
                        // minusBlueTwoStakePosCorner();
                        break;
                    }
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

            if (bot::master.get_digital_new_press(DIGITAL_X)) {
                selectedColor = (selectedColor == Color::Red) ? Color::Blue : Color::Red;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_A)) {
                selectedSide = (selectedSide == Side::Plus) ? Side::Minus : Side::Plus;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_B)) {
                Coop = !Coop;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_Y)) {
                selectedRoute++;
                if (selectedRoute > 2) selectedRoute = 0;
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