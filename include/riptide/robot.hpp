#pragma once

#include "main.h"
#include "chassis.hpp"

namespace bot {
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Motor intake(-1);

    pros::Motor bigArmLeft(-11), bigArmRight(15);

    pros::ADIDigitalOut frontLeftArm('A'), frontRightArm('C');
    bool frontLeftArmDown = false, frontRightArmDown = false;

    pros::Rotation bigArmRotation(17);

    pros::ADIDigitalOut goalClamp('H');
    bool goalClampClosed = false;

    void initialize() {
        chass = Chassis(
            new pros::MotorGroup({ -2, 4, -3 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            new pros::MotorGroup({ 19, -20, 9 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees)
        );
        chass.config(12.5, 12.5, 12.5);
        bigArmLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        bigArmRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    }

    void pwrChassPct(double left, double right) {
        chass.leftMotors->move_voltage(left * 120);
        chass.rightMotors->move_voltage(right * 120);
    }

    void pwrIntakePct(double power) {
        intake.move_voltage(power * 120);
    }

    void pwrBigArmPct(double power) {
        bigArmLeft.move_voltage(power * 120);
        bigArmRight.move_voltage(power * 120);
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
}