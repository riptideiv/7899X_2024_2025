#pragma once

#include "main.h"

#include "red.hpp"
#include "blue.hpp"
#include "coop.hpp"
#include "skills.hpp"

namespace auton {
    pros::Task *autonSelectTask;
    bool auton_running = false;

    enum class Color { Red, Blue };

    Color selectedColor = Color::Red;
    int selectedRoute = 1;
    int selectedKeybinds = 0;

    std::vector<std::string> routeDisplay = { "Skills", "Coop", "Pos5Stay", "Neg5+1", "Neg6", "Pos5Rush" };
    std::string keybindsDisplay[] = { "ryan", "altf4" };

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", keybindsDisplay[selectedKeybinds]);
        pros::delay(100);
        bot::master.print(2, 0, "%s            ", routeDisplay[(int)selectedRoute]);
    }

    void runSelectedAuton() {
        auton_running = true;
        bot::set_brake_mode(pros::MotorBrake::brake);

        bigArm.manual = false;
        bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

        if (selectedColor == Color::Red) {
            bot::intake.doAntiStuck = true;
            bot::intake.set_colorsort(1, 1);
            bot::spin_intk(0);
            switch (selectedRoute) {
            case 0:
                autonSkills();
                selectedRoute++;
                displaySelectedAuton();
                break;
            case 1:
                coopSlot();
                break;
            case 2:
                red::plus5_cornerprep();
                break;
            case 3:
                red::minus5_1();
                break;
            case 4:
                red::minus6();
                break;
            case 5:
                red::plus5_rushprep();
                break;
            }
        } else {
            bot::intake.doAntiStuck = true;
            bot::intake.set_colorsort(1, 0);
            bot::spin_intk(0);
            switch (selectedRoute) {
            case 0:
                autonSkills();
                selectedRoute++;
                displaySelectedAuton();
                break;
            case 1:
                coopSlot();
                break;
            case 2:
                blue::plus5_cornerprep();
                break;
            case 3:
                blue::minus5_1();
                break;
            case 4:
                blue::minus6();
                break;
            case 5:
                blue::plus5_rushprep();
                break;
            }
        }
        drive_chass(0, 0);
    }

    void autonSelectLoop() {
        printf("Auton select loop started\n");
        pros::delay(500);
        bot::master.clear();
        pros::delay(100);
        displaySelectedAuton();
        while (!pros::competition::is_disabled()) {
            if (auton_running) {
                pros::delay(20);
                continue;
            }

            bool update = 0;

            if (bot::master.get_digital_new_press(DIGITAL_Y)) {
                selectedColor = (selectedColor == Color::Red) ? Color::Blue : Color::Red;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_A)) {
                selectedKeybinds++;
                if (selectedKeybinds >= 2) selectedKeybinds = 0;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_X)) {
                selectedRoute++;
                if (selectedRoute >= routeDisplay.size()) selectedRoute = 0;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_B)) {
                selectedRoute--;
                if (selectedRoute < 0) selectedRoute = routeDisplay.size() - 1;
                update = 1;
            }

            if (bot::master.get_digital_new_press(DIGITAL_LEFT) ||
                bot::master.get_digital_new_press(DIGITAL_RIGHT) ||
                bot::master.get_digital_new_press(DIGITAL_UP) ||
                bot::master.get_digital_new_press(DIGITAL_DOWN)) {
                runSelectedAuton();
                auton_running = false;
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

            // update stuff when selected auton is changed

            // Display the selected attributes on the controller screen
            displaySelectedAuton();

            // set the big arm settings
            bigArm.reset();
            switch (selectedRoute) {
            case 1: // Coop
            case 2: // Pos4+1
            case 3: // Neg5+1
            case 5: // Neg3+2+1
                bigArm.manual_move(0);
                bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
                break;
            default:
                bigArm.manual = false;
                bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
                break;
            }
        }
        printf("Auton select loop ended.\n");
    }
}