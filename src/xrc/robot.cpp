#include "xrc/robot.hpp"

namespace xrobot {
    bool imu_flipped = false;

    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::MotorGroup left_mg({ 14, -19, -15 });
    pros::MotorGroup right_mg({ -6, 5, 7 });
    pros::Imu sinertial(19);
    pros::Rotation horizTracker(11);

    pros::Motor mhooks(20);
    pros::Motor mintake(8);
    pros::Motor mbigarm(9);

    void initialize() {
        horizTracker.reset_position();
        sinertial.reset();
        left_mg.set_brake_mode_all(MOTOR_BRAKE_COAST);
        right_mg.set_brake_mode_all(MOTOR_BRAKE_COAST);
        left_mg.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
        right_mg.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
        mhooks.set_encoder_units(MOTOR_ENCODER_DEGREES);
        mintake.set_encoder_units(MOTOR_ENCODER_DEGREES);
        mbigarm.set_encoder_units(MOTOR_ENCODER_DEGREES);
        mbigarm.set_brake_mode(MOTOR_BRAKE_BRAKE);
        initTracking();
        // Wait for IMU calibration
        while (sinertial.is_calibrating()) {
            pros::delay(20);
        }
    }

    double get_rotation() {
        double rotation = sinertial.get_rotation();
        return imu_flipped ? -rotation : rotation;
    }

    double get_avg_pos(const pros::MotorGroup &mg) {
        double sum = 0;
        for (double i : mg.get_position_all()) {
            sum += i;
        }
        return sum / mg.get_position_all().size();
    }
}
