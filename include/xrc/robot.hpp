#pragma once
#include "main.h"

namespace xrobot {
    extern bool imu_flipped;

    double get_rotation();

    extern pros::Controller master;
    extern pros::MotorGroup left_mg;
    extern pros::MotorGroup right_mg;
    extern pros::Imu sinertial;
    extern pros::Rotation horizTracker;
    
    extern pros::Motor mhooks;
    extern pros::Motor mintake;
    extern pros::Motor mbigarm;  // New motor declaration

    void toggle_goal();

    // New initialization function
    void initialize();

    double get_avg_pos(const pros::MotorGroup &mg);
}