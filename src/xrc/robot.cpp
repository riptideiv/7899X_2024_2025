#include "xrc/robot.hpp"

namespace xrobot {
    bool auton_selecting;

    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::MotorGroup left_mg({ 14, -19, -15 });
    pros::Motor *left_mtrs[3] = { new pros::Motor(14), new pros::Motor(-19), new pros::Motor(-15) };
    pros::MotorGroup right_mg({ -6, 5, 7 });
    pros::Motor *right_mtrs[3] = { new pros::Motor(-6), new pros::Motor(5), new pros::Motor(7) };
    pros::Imu sinertial(1);
    pros::Rotation horizTracker(11);

    pros::Motor mhooks(20);
    pros::Motor mintake(2);
    pros::Motor mbigarm(-21);

    pros::adi::DigitalOut goalToggle('F');
    pros::adi::DigitalOut ringLock('D');
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
        mbigarm.set_brake_mode(MOTOR_BRAKE_BRAKE);
        mbigarm.set_encoder_units(MOTOR_ENCODER_DEGREES);
        initTracking();
        auton::initialize();
        // Wait for IMU calibration
        while (sinertial.is_calibrating()) {
            pros::delay(20);
        }
        printf("[RiptideIV] Initialization Complete.\n");
    }

    double get_rotation() {
        return sinertial.get_rotation();
    }

    double get_avg_pos(const pros::MotorGroup &mg) {
        double sum = 0, asum = 0;
        for (double i : mg.get_position_all()) {
            sum += i;
            asum += fabs(i);
        }
        if (sum > 0) {
            return asum;
        } else {
            return -asum;
        }
    }

    void driveV(int lV, int rV) { // lV and rV are voltage between -127 and 127
        left_mg.move(lV);
        right_mg.move(rV);
    }

    void drivePct(double lPct, double rPct) { // lPct and rPct are percentages between -100 and 100
        left_mg.move_velocity(lPct * 127 / 100);
        right_mg.move_velocity(rPct * 127 / 100);
    }
}
