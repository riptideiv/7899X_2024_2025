#pragma once

#include "main.h"
#include "autonUtils.hpp"

using pid::drive, pid::driveWait, pid::arcWait, pid::turn, pros::delay;

namespace auton {
    void plusRushAWP() { // line up with back on driver's wall, line up backwheel screw tip to field tile cross, then -162 deg for red or 162 deg for blue
        printf("plusRushAWP\n");
        if (!pid::PID_FLIPPED) {
            if (bot::get_rotation() > 0) {
                bot::imu.set_rotation(bot::imu.get_rotation() - 360 / bot::imuConstant);
            }
            turn(0, 0, 1);
            bot::bigArm.reset();
            driveWait(300, 0.5, 0.5, true);
            driveWait(800, 0.6, 0.8, false);
            driveWait(1250, 0.7, 1.0, false);
            driveWait(1350, 0.5, 0.6, false);
            driveWait(1450, 0.3, 0.3, false);
            turn(-20, 200, false);
            FLAToggleFlipAware();
            delay(200);
            driveWait(-150, 0.25, 0.5, true);
            drive(-1000, 800, false);
            FLAToggleFlipAware();
            delay(200);
            arcWait(70, 0.7, -0.7, false);
            turn(165, 400, false);
            driveWait(-400, 0.3, 0.3, true);
            bot::toggleGoalClamp();
            pid::set_mogo(true);
            pros::Task t1([=] {
                pros::Task::delay(200);
                bot::pwrIntakePct(100);
                });
            drive(-400, 1000, false);
            driveWait(-100, 0.8, 0.8, true);
            arcWait(190, 0.6, -0.6, false);
            turn(220, 500, false);
            driveWait(100, 0.4, 0.4, true);
            driveWait(200, 0.8, 0.8, false);
            driveWait(400, 0.6, 0.6, false);
            drive(500, 300, false);
            bot::pwrIntakePct(0);
            turn(210, 500, false);
            bot::pwrIntakePct(100);
            bot::toggleGoalClamp();
            pid::set_mogo(false);
            driveWait(700, 0.6, 0.6, true);
            bot::pwrIntakePct(0);
            drive(1400, 900, false);
            turn(167, 700, false);
            driveWait(-1000, 0.4, 0.4, true);
            bot::toggleGoalClamp();
            pid::set_mogo(true);
            pros::Task t2([=] {
                pros::Task::delay(200);
                bot::pwrIntakePct(100);
                });
            drive(-1000, 1000, false);
        } else {
            if (bot::get_rotation() < 0) {
                bot::imu.set_rotation(bot::imu.get_rotation() + 360 / bot::imuConstant);
            }turn(0, 0, 1);
            bot::bigArm.reset();
            driveWait(300, 0.5, 0.5, true);
            driveWait(700, 0.6, 0.7, false);
            driveWait(1150, 0.75, 0.9, false);
            driveWait(1250, 0.6, 0.6, false);
            driveWait(1350, 0.3, 0.3, false);
            turn(-20, 200, false);
            FLAToggleFlipAware();
            delay(200);
            driveWait(-150, 0.25, 0.5, true);
            drive(-1000, 800, false);
            FLAToggleFlipAware();
            delay(200);
            arcWait(70, 0.7, -0.7, false);
            turn(165, 400, false);
            driveWait(-400, 0.3, 0.3, true);
            bot::toggleGoalClamp();
            pid::set_mogo(true);
            pros::Task t1([=] {
                pros::Task::delay(200);
                bot::pwrIntakePct(100);
                });
            drive(-400, 1000, false);
            driveWait(-100, 0.8, 0.8, true);
            arcWait(190, 0.6, -0.6, false);
            turn(225, 500, false);
            driveWait(100, 0.4, 0.4, true);
            driveWait(200, 0.8, 0.8, false);
            driveWait(400, 0.6, 0.6, false);
            drive(500, 300, false);
            bot::pwrIntakePct(0);
            turn(210, 500, false);
            bot::pwrIntakePct(100);
            bot::toggleGoalClamp();
            pid::set_mogo(false);
            driveWait(700, 0.6, 0.6, true);
            bot::pwrIntakePct(0);
            drive(1400, 900, false);
            turn(170, 700, false);
            driveWait(-900, 0.6, 0.6, true);
            driveWait(-1250, 0.3, 0.3, false);
            bot::toggleGoalClamp();
            pid::set_mogo(true);
            pros::Task t2([=] {
                pros::Task::delay(200);
                bot::pwrIntakePct(100);
                });
            drive(-1300, 1000, false);
        }
    }
    void plusRushNoAWP() {
        turn(-25, 200, false);
        printf("plusRushNoAWP was run\n");
    }
    void plusSafeAWP() {
        printf("plusSafeAWP was run\n");
    }
    void plusSafeNoAWP() {
        printf("plusSafeNoAWP was run\n");
    }
}