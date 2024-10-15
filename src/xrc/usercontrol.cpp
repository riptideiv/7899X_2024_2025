#include "main.h"

void xrobot::handle_controller_input() {
    // Arcade control scheme
    int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
    int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
    left_mg.move(dir - turn);                      // Sets left motor voltage
    right_mg.move(dir + turn);                     // Sets right motor voltage
    
    // Control hooks motor with R1 button
    if (master.get_digital(DIGITAL_R1)) {
        mhooks.move(127);  // Run hooks motor at full speed when R1 is pressed
    } else {
        mhooks.move(0);    // Stop hooks motor when R1 is not pressed
    }
    
    // Control intake motor with R2 button
    if (master.get_digital(DIGITAL_R2)) {
        mintake.move(127); // Run intake motor at full speed when R2 is pressed
    } else {
        mintake.move(0);   // Stop intake motor when R2 is not pressed
    }

    // Control big arm motor with L1 and L2 buttons
    if (master.get_digital(DIGITAL_L1)) {
        mbigarm.move(127);  // Move big arm up when L1 is pressed
    } else if (master.get_digital(DIGITAL_L2)) {
        mbigarm.move(-127); // Move big arm down when L2 is pressed
    } else {
        mbigarm.move(0);    // Stop big arm motor when neither L1 nor L2 is pressed
    }
}