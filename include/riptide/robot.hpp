#pragma once

#include "main.h"
#include "chassis.hpp"
#include "bigArm.hpp"

namespace bot {
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Motor intake(-1);

    pros::adi::DigitalOut frontLeftArm('F'), frontRightArm('A');
    bool frontLeftArmDown = false, frontRightArmDown = false;

    pros::adi::DigitalOut goalClamp('H');
    bool goalClampClosed = false;

    pros::IMU imu(5);
    const double imuConstant = 360.0 / 359.3;
    double get_rotation() {
        return imu.get_rotation() * imuConstant;
    }

    void initialize() {
        imu.reset();
        chass = Chassis(
            new pros::MotorGroup({ -2, 4, -3 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            new pros::MotorGroup({ 19, -10, 9 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees)
        );
        chass.config(12.5, 12.5, 12.5, 1);
        bigArm.initialize(11, -15, 21, 17500, 16690, 15100);
        while (imu.is_calibrating()) {
            pros::delay(20);
        }
        imu.set_rotation(0);
    }

    void pwrChassPct(double left, double right) {
        chass.leftMotors->move_voltage(left * chass.lMult * 120);
        chass.rightMotors->move_voltage(right * 120);
    }

    void pwrIntakePct(double power) {
        intake.move_voltage(power * 120);
    }

    void toggleFrontLeftArm() {
        frontLeftArmDown = !frontLeftArmDown;
        frontLeftArm.set_value(frontLeftArmDown);
    }

    void toggleFrontRightArm() {
        frontRightArmDown = !frontRightArmDown;
        frontRightArm.set_value(frontRightArmDown);
    }

    void toggleGoalClamp() {
        goalClampClosed = !goalClampClosed;
        goalClamp.set_value(goalClampClosed);
    }

    void deactivate_all_pistons() {
        if (frontLeftArmDown) toggleFrontLeftArm();
        if (frontRightArmDown) toggleFrontRightArm();
        if (goalClampClosed) toggleGoalClamp();
    }
}