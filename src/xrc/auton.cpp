#include "main.h"
#include "xrc/autons/plus.hpp"
#include "xrc/autons/minus.hpp"

namespace auton {
    bool flipped;

    void initialize() {
        pid::initPID();
        autonSelectTask = new pros::Task(auton::autonSelectLoop);
    }

    void runSelectedAuton() {
        xrobot::left_mg.set_brake_mode_all(MOTOR_BRAKE_HOLD);
        xrobot::right_mg.set_brake_mode_all(MOTOR_BRAKE_HOLD);

        if (selectedColor == Color::Blue) {
            flipped = true;
        } else {
            flipped = false;
        }

        if (selectedSide == Side::Plus) {
            if (selectedMode == Mode::Rush) {
                if (AWP) {
                    plusRushAWP();
                } else {
                    plusRushNoAWP();
                }
            } else {
                if (AWP) {
                    plusSafeAWP();
                } else {
                    plusSafeNoAWP();
                }
            }
        } else {
            if (selectedMode == Mode::Rush) {
                if (AWP) {
                    minusRushAWP();
                } else {
                    minusRushNoAWP();
                }
            } else {
                if (AWP) {
                    minusSafeAWP();
                } else {
                    minusSafeNoAWP();
                }
            }
        }

        // Reset imu_flipped state after autonomous
        flipped = false;
    }
}
