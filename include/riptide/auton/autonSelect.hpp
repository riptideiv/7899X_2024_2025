#pragma once

#include "main.h"

#include "../auton.hpp"

#include "plus.hpp"
#include "minus.hpp"
#include "skills.hpp"

namespace auton {
    enum class Color { Red, Blue };
    enum class Side { Plus, Minus };
    enum class Mode { Risk, Safe };
    bool Skills = false;

    Color selectedColor = Color::Red;
    Side selectedSide = Side::Minus;
    // Mode selectedMode = Mode::Risk;
    bool selectedVersion = true;

    pros::Task *autonSelectTask;

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", selectedSide == Side::Plus ? "Plus" : "Minus");
        pros::delay(100);
        bot::master.print(2, 0, "%s;; %s    ", selectedVersion ? "V1" : "V2", Skills ? "SKILLS" : "MATCH");
        if(Skills){
            bot::bigArm.set_target(bot::bigArm.posLow);
        }else{
            bot::bigArm.set_target(bot::bigArm.posHigh);
        }
    }

    void runSelectedAuton() {
        bot::set_brake_mode(pros::MotorBrake::brake);

        if(Skills){
            autonSkills();
        }else{
            if (selectedSide == Side::Plus) {
                if (selectedColor == Color::Red) {
                    if (selectedVersion) {
                        plusRedV1();
                    } else {
                        plusRedV2();
                    }
                } else {
                    if (selectedVersion) {
                        plusBlueV1();
                    } else {
                        plusBlueV2();
                    }
                }
            } else {
                if (selectedColor == Color::Red) {
                    if (selectedVersion) {
                        minusRedV1();
                    } else {
                        minusRedV2();
                    }
                } else {
                    if (selectedVersion) {
                        minusBlueV1();
                    } else {
                        minusBlueV2();
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
                Skills = !Skills;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_Y)) {
                selectedVersion = !selectedVersion;
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