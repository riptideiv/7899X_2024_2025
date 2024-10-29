#pragma once
#include "main.h"
#include "pid.hpp"

void deployArm() {
    // xrobot::ringLock.set_value(true);
    xrobot::mbigarm.move(127);
    pros::delay(500);
    xrobot::mbigarm.move(-127);
    pros::delay(750);
    xrobot::mbigarm.move(127);
    pros::delay(250);
    xrobot::mbigarm.move(0);
}

void scorePreload() {
    xrobot::mbigarm.move(127);
    pid::drive(300, 750, true);
    xrobot::mbigarm.move(-127);
    pros::delay(500);
    xrobot::mbigarm.move(0);
    pid::drive(-300, 750, true);
}