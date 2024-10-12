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

    void toggle_goal();

    // New initialization function
    void initialize();

    double get_avg_pos(const pros::MotorGroup &mg);
}