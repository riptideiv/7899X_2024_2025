#include "main.h"
#include "xrc/pid.hpp"
#include "xrc/autons/general.hpp"

auto mogo = pid::PID_MOGO;
auto nomogo = pid::PID_EMPTY;

namespace auton {
    void plusRushAWP() {
        printf("plusRushAWP was run\n");
        pid::turn(60, 1000, true, nomogo);
    }
    void plusRushNoAWP() {
        printf("plusRushNoAWP was run\n");
    }
    void plusSafeAWP() { // gyro reset with bot's back aligned with the driver zone wall, bot starts with back facing the mogo (165 or -195 degrees)
        printf("plusSafeAWP was run\n");
        if (!flipped && xrobot::get_rotation() < 0) {
            xrobot::sinertial.set_rotation(xrobot::sinertial.get_rotation() + 360);
        }
        if (flipped && xrobot::get_rotation() > 0) {
            xrobot::sinertial.set_rotation(xrobot::sinertial.get_rotation() - 360);
        }
        pros::Task deployArmTask(deployArm);
        pid::driveWait(-350, 0.4, 0.4, true);
        xrobot::goalToggle.set_value(true);
        pid::drive(-400, 500, false);
        pid::turn(80, 1500, false, mogo);
        xrobot::mintake.move(127);
        xrobot::mhooks.move(127);
        pid::drive(225, 1250, true);
        xrobot::mbigarm.move(127);
        pid::driveWait(-50, 0.8, 0.8, true);
        pid::turn(-45, 1500, false, mogo);
        xrobot::mbigarm.move(0);
        pid::drive(200, 1000, true);
        xrobot::mbigarm.move(-127);
        pros::delay(500);
        xrobot::mbigarm.move(-12);
    }
    void plusSafeNoAWP() {
        printf("plusSafeNoAWP was run\n");
    }
}