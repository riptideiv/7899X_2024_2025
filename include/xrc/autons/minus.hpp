#include "main.h"
#include "xrc/pid.hpp"
#include "xrc/autons/general.hpp"

namespace auton {
    void minusRushAWP() {
        printf("minusRushAWP was run\n");
    }
    void minusRushNoAWP() {
        printf("minusRushNoAWP was run\n");
    }
    void minusSafeAWP() { // gyro reset with bot's back aligned with the driver zone wall, bot starts with back facing the mogo (-145.5 or 214.5 degrees)
        printf("minusSafeAWP was run\n");
        if (!flipped && xrobot::get_rotation() > 0) {
            xrobot::sinertial.set_rotation(xrobot::sinertial.get_rotation() - 360);
        }
        if (flipped && xrobot::get_rotation() < 0) {
            xrobot::sinertial.set_rotation(xrobot::sinertial.get_rotation() + 360);
        }
        pros::Task deployArmTask(deployArm);
        pid::driveWait(-50, 0.3, 0.3, true);
        pid::drive(-400, 900, false);
        pid::driveWait(-75, 0.2, 0.2, true);
        xrobot::goalToggle.set_value(true);
        pid::driveWait(-75, 0.2, 0.2, true);
        pid::turn(-40, 1050, false, mogo);
        xrobot::mintake.move(127);
        xrobot::mhooks.move(127);
        pid::drive(275, 1500, true);
        pid::driveWait(225, 0.6, 0.8, false);
        pid::turn(-55, 650, false, mogo);
        pid::drive(175, 1250, true);
        pid::driveWait(75, 0.8, 0.1, false);
        pid::turn(-125, 1000, false, mogo);
        pid::drive(200, 1000, true);
        pid::turn(-290, 1750, false, mogo);
        xrobot::mbigarm.move(127);
        pid::driveWait(200, 0.6, 0.6, true);
        xrobot::mbigarm.move(0);
        pid::drive(400, 1000, false);
        xrobot::mbigarm.move(-127);
    }
    void minusSafeNoAWP() {
        printf("minusSafeNoAWP was run\n");
    }
}