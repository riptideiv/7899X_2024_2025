#include "main.h"

bool goalToggleState = false;
bool armlockState = false;
bool lilarmState = false;
bool intakeToggleState = false;
void xrobot::handle_controller_input() {
    // Arcade control scheme
    int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
    int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
#ifdef ENABLE_DRIVING
    left_mg.move(dir + turn);                      // Sets left motor voltage
    right_mg.move(dir - turn);                     // Sets right motor voltage
#endif

    if (master.get_digital_new_press(DIGITAL_Y)) {
        goalToggle.set_value(!goalToggleState);
        goalToggleState = !goalToggleState;
    }

    if (master.get_digital_new_press(DIGITAL_LEFT)) {
        ringLock.set_value(!armlockState);
        armlockState = !armlockState;
    }

    // if (master.get_digital_new_press(DIGITAL_UP)) {
    //     intakeToggle.set_value(!intakeToggleState);
    //     intakeToggleState = !intakeToggleState;
    // }

    if (master.get_digital_new_press(DIGITAL_RIGHT)) {
        lilArm.set_value(!lilarmState);
        lilarmState = !lilarmState;
    }

    if (master.get_digital(DIGITAL_A)) {
        mbigarm.move(127);
    } else if (master.get_digital(DIGITAL_B)) {
        mbigarm.move(-127);
    } else {
        mbigarm.move(0);
    }

    // Control hooks motor with R1 and R2 buttons
    if (master.get_digital(DIGITAL_L1)) {
        mhooks.move(127);  // Run hooks motor forward at full speed when R1 is pressed
    } else if (master.get_digital(DIGITAL_L2)) {
        mhooks.move(-127); // Run hooks motor backward at full speed when R2 is pressed
    } else {
        mhooks.move(0);    // Stop hooks motor when neither R1 nor R2 is pressed
    }

    // Control intake motor with L1 and L2 buttons
    if (master.get_digital(DIGITAL_R1)) {
        mintake.move(127); // Run intake motor forward at full speed when L1 is pressed
    } else if (master.get_digital(DIGITAL_R2)) {
        mintake.move(-127); // Run intake motor backward at full speed when L2 is pressed
    } else {
        mintake.move(0);   // Stop intake motor when neither L1 nor L2 is pressed
    }
}