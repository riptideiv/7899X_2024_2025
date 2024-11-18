#pragma once

#include "main.h"

namespace riptide {
    void testChassisSpeedDifference() {
        bot::chass.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        bot::chass.reset_position();
        bot::chass.leftMotors->move_voltage(12000);
        bot::chass.rightMotors->move_voltage(12000);
        pros::delay(1000);
        double left = bot::chass.leftMotors->get_position(), right = bot::chass.rightMotors->get_position();
        bot::pwrChassPct(0, 0);
        std::cout << "Left: " << left << ", Right: " << right << ", left divided by light: " << left / right << ", right divided by left: " << right / left << std::endl;
    }
}