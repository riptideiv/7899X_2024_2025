#include "xrc/robot.hpp"

namespace xrobot {
    bool imu_flipped = false;

    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::MotorGroup left_mg({ 14, -19, -15 });
    pros::Motor *left_mtrs[3] = { new pros::Motor(14), new pros::Motor(-19), new pros::Motor(-15) };
    pros::MotorGroup right_mg({ -6, 5, 7 });
    pros::Motor *right_mtrs[3] = { new pros::Motor(-6), new pros::Motor(5), new pros::Motor(7) };
    pros::Imu sinertial(1);
    pros::Rotation horizTracker(11);

    pros::Motor mhooks(20);
    pros::Motor mintake(2);
    pros::Motor mbigarm(21);

    pros::adi::DigitalOut goalToggle('B');
    pros::adi::DigitalOut ringLock('F');
    pros::adi::DigitalOut lilArm('H');
    pros::adi::DigitalOut intakeToggle('G');

    void initialize() {
        horizTracker.reset();
        sinertial.reset();
        left_mg.set_brake_mode_all(MOTOR_BRAKE_COAST);
        right_mg.set_brake_mode_all(MOTOR_BRAKE_COAST);
        left_mg.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
        right_mg.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
        left_mg.set_zero_position_all(0);
        right_mg.set_zero_position_all(0);
        mhooks.set_brake_mode(MOTOR_BRAKE_BRAKE);
        mhooks.set_encoder_units(MOTOR_ENCODER_DEGREES);
        mintake.set_brake_mode(MOTOR_BRAKE_BRAKE);
        mintake.set_encoder_units(MOTOR_ENCODER_DEGREES);
        mbigarm.set_brake_mode(MOTOR_BRAKE_HOLD);
        mbigarm.set_encoder_units(MOTOR_ENCODER_DEGREES);
        initTracking();
        // Wait for IMU calibration
        while (sinertial.is_calibrating()) {
            pros::delay(20);
        }
        printf("[RiptideIV] Initialization Complete.\n");
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
        return sum / 3.0;
    }
}
