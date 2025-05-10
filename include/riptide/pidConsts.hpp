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

    // angular PID controllers (0 = no mogo, 1 = mogo)
    lemlib::ControllerSettings standard_angular_controller[2] = {
        lemlib::ControllerSettings(
            4, // proportional gain (kP)
            0, // integral gain (kI)
            22.5, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings( // UNTUNED
            7, // proportional gain (kP)
            0, // integral gain (kI)
            65.625, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        )
    };

    // angular PID controllers for connecting to straight motions
    lemlib::ControllerSettings connecting_angular_controller[2] = {
        lemlib::ControllerSettings(
            1.5625, // proportional gain (kP)
            0, // integral gain (kI)
            0, // derivative gain (kD)
            0, // anti windup
            0, // small error range, in degrees
            0, // small error range timeout, in milliseconds
            0, // large error range, in degrees
            0, // large error range timeout, in milliseconds
            0 // maximum acceleration (slew)
        ),
        lemlib::ControllerSettings(
            1.1875, // proportional gain (kP)
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

    // straight-only angular PID controller
    lemlib::ControllerSettings straight_angular_controller = lemlib::ControllerSettings(
        0, // proportional gain (kP)
        0, // integral gain (kI)
        0, // derivative gain (kD)
        0, // anti windup
        0, // small error range, in degrees
        0, // small error range timeout, in milliseconds
        0, // large error range, in degrees
        0, // large error range timeout, in milliseconds
        0 // maximum acceleration (slew)
    );
}