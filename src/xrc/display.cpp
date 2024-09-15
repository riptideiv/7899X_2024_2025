#include "main.h"

void Display::init() {
    // Initialize display-related stuff
}

void Display::update() {
    displayMotorCurrent();
    // Call other display update methods as needed
}

void Display::displayMotorCurrent() {
    // Display motor current for drivetrain, goal intake, and claw
    pros::lcd::print(0, "DT L: %f", xrobot::left_mg.get_current_draw());
    pros::lcd::print(1, "DT R: %f", xrobot::right_mg.get_current_draw());
    pros::lcd::print(2, "Goal Intake: %f", xrobot::goal_intake.get_current_draw());
    pros::lcd::print(3, "Claw: %f", xrobot::claw.get_current_draw());
}