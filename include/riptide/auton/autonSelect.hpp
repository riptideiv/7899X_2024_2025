#pragma once

#include "main.h"

#include "red.hpp"
#include "blue.hpp"
#include "coop.hpp"
#include "skills.hpp"

namespace auton {
    pros::Task *autonSelectTask;
    bool auton_running = false;
    bool auton_ran = false;

    enum class Color { Red, Blue };

    Color selectedColor = Color::Red;
    int selectedRoute = 1;
    int selectedKeybinds = 1;

    std::vector<std::string> routeDisplay = { "Skills", "Coop", "NegRRush", "Neg6+1", "Neg5+1", "PosGRush", "Pos5+1", "Pos6+0" };
    std::vector<std::vector<double>> routeSetupAngle =
    {
        { // Red
            0, // Skills
            0, // Coop
            -16, // NegRRush
            -27, // Neg6+1
            -27, // Neg5+1
            15.5, // PosGRush
            29.5, // Pos5+1
            0 // Pos6+0
        },
        { // Blue
            0, // Skills
            0, // Coop
            17, // NegRRush
            29.5, // Neg6+1
            29.5, // Neg5+1
            0, // PosGRush
            -27, // Pos5+1
            0 // Pos6+0
        }
    };
    std::string keybindsDisplay[] = { "ryan", "altf4" };

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", keybindsDisplay[selectedKeybinds]);
        pros::delay(50);
        bot::master.print(1, 0, "setup: %.1f deg    ", routeSetupAngle[(int)selectedColor][(int)selectedRoute]);
        pros::delay(50);
        bot::master.print(2, 0, "%s            ", routeDisplay[(int)selectedRoute]);
    }

    void updateSelectedAuton() {
        // Display the selected attributes on the controller screen
        displaySelectedAuton();

        // setup settings
        bigArm.reset();
        switch (selectedRoute) {
        case 1: // Coop
        case 3: // Neg6+1
        case 4: // Neg5+1
        case 5: // PosGRush
        case 6: // Pos5+1
            bigArm.manual_move(0);
            bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
            break;
        default:
            bigArm.manual = false;
            bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
            break;
        }

        getChass()->cancelAllMotions();
        pros::delay(50);
        if (selectedColor == Color::Red)
            turn2hd(routeSetupAngle[0][selectedRoute], 700, {}, 1);
        else
            turn2hd(routeSetupAngle[1][selectedRoute], 700, {}, 1);
    }

    void runSelectedAuton() {
        auton_running = true;
        auton_ran = true;
        bot::set_brake_mode(pros::MotorBrake::brake);

        bigArm.manual = false;
        bigArm.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
        bigArm.reset();

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
                red::neg_rrush();
                break;
            case 3:
                red::neg6_1();
                break;
            case 4:
                blue::pos5_1();
                break;
            case 5:
                red::pos_grush();
                break;
            case 6:
                red::pos5_1();
                break;
            case 7:
                red::pos6();
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
                blue::neg_rrush();
                break;
            case 3:
                blue::neg6_1();
                break;
            case 4:
                red::pos5_1();
                break;
            case 5:
                blue::pos_grush();
                break;
            case 6:
                blue::pos5_1();
                break;
            case 7:
                blue::pos6();
            }
        }
        auton_running = false;
        getChass()->arcade(0, 0);
    }

    void autonSelectLoop() {
        printf("Auton select loop started\n");
        pros::delay(500);
        bot::master.clear();
        pros::delay(100);
        displaySelectedAuton();
        updateSelectedAuton();
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
                auton_ran = false;
            }

            if (bot::master.get_digital_new_press(DIGITAL_L1) ||
                bot::master.get_digital_new_press(DIGITAL_L2) ||
                bot::master.get_digital_new_press(DIGITAL_R1) ||
                bot::master.get_digital_new_press(DIGITAL_R2)) {
                bot::bigArm.reset();
                auton_ran = true;
                break;
            }

            pros::delay(20); // Add a small delay to prevent CPU overuse

            if (!update) continue;

            // update stuff when selected auton is changed

            updateSelectedAuton();
        }
        printf("Auton select loop ended.\n");
    }
}