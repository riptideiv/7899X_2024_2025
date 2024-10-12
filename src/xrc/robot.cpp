#include "xrc/robot.hpp"

namespace xrobot {
    bool imu_flipped = false;

    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::MotorGroup left_mg({ -1, 2, 7 });
    pros::MotorGroup right_mg({ 11, -12, -17 });
    pros::Imu sinertial(19);
    pros::Rotation horizTracker(9);

    void initialize() {
        horizTracker.reset_position();
        sinertial.reset();
        left_mg.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
        right_mg.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
        // Wait for IMU calibration
        while (sinertial.is_calibrating()) {
            pros::delay(20);
        }
        initTracking();
    }

    double get_rotation() {
        double rotation = sinertial.get_rotation();
        return imu_flipped ? -rotation : rotation;
    }

    double get_avg_pos(const pros::MotorGroup &mg){
        double sum=0;
        for(double i:mg.get_position_all()){
            sum+=i;
        }
        return sum/mg.get_position_all().size();
    }
}