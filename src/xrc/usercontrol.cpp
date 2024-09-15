#include "main.h"

using namespace xrobot;

void handle_controller_input() {
    // Arcade control scheme
    int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
    int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
    left_mg.move(dir - turn);                      // Sets left motor voltage
    right_mg.move(dir + turn);                     // Sets right motor voltage

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) && !GOAL_TOGGLING) {
        GOAL_TOGGLING = true;
        pros::Task toggle_task(toggle_goal);
    }

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        pros::Task toggle_task(toggle_glock);
    }

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2) && !CLAW_TOGGLING) {
        CLAW_TOGGLING = true;
        pros::Task toggle_task(toggle_claw);
    }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        xrobot::lifting = true;
        lift.move(127);
    } else {
        xrobot::lifting = false;
        lift.move(0);
    }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        lift.move(-127);
    }
}