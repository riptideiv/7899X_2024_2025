#include "main.h"
namespace auton {
    Color selectedColor = Color::Red;
    Side selectedSide = Side::Plus;
    Mode selectedMode = Mode::Rush;
    bool AWP = true;

    pros::Task *autonSelectTask;

    inline void displaySelectedAuton() {
        xrobot::master.print(0, 0, "%s;; %s    ", selectedColor == Color::Red ? "Red" : "Blue", selectedSide == Side::Plus ? "Plus" : "Minus");
        pros::delay(100);
        xrobot::master.print(2, 0, "%s;; %s    ", AWP ? "AWP" : "Elims", selectedMode == Mode::Rush ? "Rush" : "Safe");
    }

    void autonSelectLoop() {
        printf("Auton select loop started\n");
        xrobot::master.clear();
        pros::delay(100);
        displaySelectedAuton();
        while (!pros::competition::is_disabled()) {
            bool update = 0;

            if (xrobot::master.get_digital_new_press(DIGITAL_X)) {
                selectedColor = (selectedColor == Color::Red) ? Color::Blue : Color::Red;
                update = 1;
            }

            if (xrobot::master.get_digital_new_press(DIGITAL_A)) {
                selectedSide = (selectedSide == Side::Plus) ? Side::Minus : Side::Plus;
                update = 1;
            }

            if (xrobot::master.get_digital_new_press(DIGITAL_B)) {
                selectedMode = (selectedMode == Mode::Rush) ? Mode::Safe : Mode::Rush;
                update = 1;
            }

            if (xrobot::master.get_digital_new_press(DIGITAL_Y)) {
                AWP = !AWP;
                update = 1;
            }

            if (xrobot::master.get_digital_new_press(DIGITAL_LEFT) ||
                xrobot::master.get_digital_new_press(DIGITAL_RIGHT) ||
                xrobot::master.get_digital_new_press(DIGITAL_UP) ||
                xrobot::master.get_digital_new_press(DIGITAL_DOWN)) {
                runSelectedAuton();
            }

            if (xrobot::master.get_digital_new_press(DIGITAL_L1) ||
                xrobot::master.get_digital_new_press(DIGITAL_L2) ||
                xrobot::master.get_digital_new_press(DIGITAL_R1) ||
                xrobot::master.get_digital_new_press(DIGITAL_R2)) {
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