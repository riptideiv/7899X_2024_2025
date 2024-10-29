#pragma once
#include "main.h"

namespace xrobot {
    struct Constants {
        static constexpr double wheelDia = 2.75; // diameter of drivetrain wheel
        static constexpr double trackDia = 2.75; // diameter of tracking wheel
        static constexpr double hWheelOffset = 0; // vertical offset of horizontal tracking wheel from the center (forward is +)
        static constexpr double vWheelOffset = 0; // horizontal offset of vertical tracking wheel from the center (rightward is +), we don't have one
        static constexpr double lWheelOffset = -6.4; // horizontal offset of left drivetrain side from the center (rightward is +)
        static constexpr double rWheelOffset = 6.4; // horizontal offset of right drivetrain side from the center (rightward is +)
    };
    extern struct Constants constants;

    double get_rotation();

    extern pros::Controller master;
    extern pros::MotorGroup left_mg;
    extern pros::Motor *left_mtrs[3];
    extern pros::MotorGroup right_mg;
    extern pros::Motor *right_mtrs[3];
    extern pros::Imu sinertial;
    extern pros::Rotation horizTracker;

    extern pros::Motor mhooks;
    extern pros::Motor mintake;
    extern pros::Motor mbigarm;  // New motor declaration

    extern pros::adi::DigitalOut goalToggle;
    extern pros::adi::DigitalOut ringLock;
    extern pros::adi::DigitalOut lilArm;
    extern pros::adi::DigitalOut intakeToggle;

    void drivePct(double lPct, double rPct); // lPct and rPct are percentages between -100 and 100
    void driveV(int lV, int rV); // lV and rV are voltage between -127 and 127

    // New initialization function
    void initialize();

    double get_avg_pos(const pros::MotorGroup &mg);
}