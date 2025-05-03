#pragma once

#include "main.h"

namespace pid {
    // lateral PID controllers (0 = no mogo, 1 = mogo)
    lemlib::ControllerSettings lateral_controller[2] = {
        lemlib::ControllerSettings(
            15, // proportional gain (kP)
            0, // integral gain (kI)
            112.5, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in inches
            0, // small error range timeout, in milliseconds
            0, // large error range, in inches
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings(
            25, // proportional gain (kP)
            0, // integral gain (kI)
            187.5, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in inches
            0, // small error range timeout, in milliseconds
            0, // large error range, in inches
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        )
    };

    // angular PID controllers (0 = no mogo, 1 = mogo, 2 = straight-only)
    lemlib::ControllerSettings angular_controller[3] = {
        lemlib::ControllerSettings(
            5, // proportional gain (kP)
            0, // integral gain (kI)
            38.75, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings(
            8, // proportional gain (kP)
            0, // integral gain (kI)
            73.4375, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings(
            0, // proportional gain (kP)
            0, // integral gain (kI)
            0, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        )
    };
}