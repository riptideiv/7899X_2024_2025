#pragma once

#include "main.h"

namespace pid {
    // lateral PID controllers (0 = no mogo, 1 = mogo)
    lemlib::ControllerSettings lateral_controller[2] = {
        lemlib::ControllerSettings(
            7.5, // proportional gain (kP)
            0, // integral gain (kI)
            68.75, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in inches
            0, // small error range timeout, in milliseconds
            0, // large error range, in inches
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings(
            7.5, // proportional gain (kP)
            0, // integral gain (kI)
            75, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in inches
            0, // small error range timeout, in milliseconds
            0, // large error range, in inches
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        )
    };

    // angular PID controllers (0 = no mogo, 1 = mogo)
    lemlib::ControllerSettings angular_controller[2] = {
        lemlib::ControllerSettings(
            2, // proportional gain (kP)
            0, // integral gain (kI)
            14, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings(
            3.1, // proportional gain (kP)
            0, // integral gain (kI)
            24.4, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        )
    };
}