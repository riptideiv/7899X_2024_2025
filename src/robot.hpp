#include "main.h"

pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);
pros::MotorGroup left_mg({ 1, -2, 3 });    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
pros::MotorGroup right_mg({ -4, 5, -6 });  // Creates a motor group with forwards port 4 and reversed ports 4 & 6