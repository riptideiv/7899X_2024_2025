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
    int selectedRoute = 0;
    int selectedKeybinds = 1;

    std::vector<std::string> routeDisplay = { "Skills", "Coop", "Neg2+1+2", "Neg5+1", "Neg6" };
    std::string keybindsDisplay[] = { "xr_c", "altf4" };

    inline void displaySelectedAuton() {
        bot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", keybindsDisplay[selectedKeybinds]);
        pros::delay(100);
        bot::master.print(2, 0, "%s            ", routeDisplay[(int)selectedRoute]);
    }

    void runSelectedAuton() {
        auton_running = true;
        bot::set_brake_mode(pros::MotorBrake::brake);
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
                red::minus2_1_2();
                break;
            case 3:
                red::minus5_1();
                break;
            case 4:
                red::minus6();
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
                blue::minus2_1_2();
                break;
            case 3:
                blue::minus5_1();
                break;
            case 4:
                blue::minus6();
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

            bigArm.reset();
            switch (selectedRoute) {
            case 0: // Skills
                // bigArm.raise(); // debug
                // bigArm.toggleUp(); // debug
                break;
            case 2: // Neg2+1+2
            case 3: // Neg5+1
                bigArm.toggleUp();
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

            // Display the selected attributes on the controller screen
            displaySelectedAuton();
        }
        printf("Auton select loop ended.\n");
    }
}