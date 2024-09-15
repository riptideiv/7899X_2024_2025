#pragma once
#include "main.h"

namespace xrobot {
    extern bool goal_out;
    extern bool GOAL_TOGGLING;
    extern bool goal_locked;
    extern bool imu_flipped;

    double get_rotation();

    extern pros::Controller master;
    extern pros::MotorGroup left_mg;
    extern pros::MotorGroup right_mg;
    extern pros::Imu sinertial;
    extern pros::Motor goal_intake;
    extern pros::Motor lift;
    extern pros::Rotation srotation;
    extern pros::ADIDigitalOut glock;

    void toggle_goal();
    void toggle_glock();

    // New initialization function
    void initialize();
    extern bool claw_inward;
    extern bool CLAW_TOGGLING;
    extern pros::Motor claw;

    void toggle_claw();

    extern bool lifting;

    void lower_lift_task();
}