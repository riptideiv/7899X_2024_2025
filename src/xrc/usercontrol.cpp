#include "main.h"

void xrobot::handle_controller_input() {
    // Arcade control scheme
    int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
    int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
    left_mg.move(dir - turn);                      // Sets left motor voltage
    right_mg.move(dir + turn); 
}