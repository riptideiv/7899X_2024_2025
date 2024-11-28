#pragma once

#include "main.h"
#include "robot_globals.hpp"
#include "sensors.hpp"
#include "bigArm.hpp"
#include "pneumatics.hpp"

namespace bot {
    pros::Controller master(pros::E_CONTROLLER_MASTER);

    pros::Motor intake(-1);

    lemlib::Drivetrain *drivetrain;

    lemlib::Chassis *chass[2]; // 0 = no mogo, 1 = mogo

    void initialize() {
        init_sensors();

        drivetrain = new lemlib::Drivetrain(
            new pros::MotorGroup({ -6, 4, -3 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            new pros::MotorGroup({ 19, -10, 9 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            12.344, // 12.344 inch track width
            lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
            600, // drivetrain rpm is 360
            2 // horizontal drift is 2
        );

        chass[0] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[0], pid::angular_controller[0], *odomSensors[0]);
        chass[1] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[1], pid::angular_controller[1], *odomSensors[1]);

        int bigArmHi = 22000,
            bigArmMid = 0,
            bigArmLow = 0,
            bigArmScore = 0;

        bigArm.initialize(-15, 21, bigArmLow, bigArmMid, bigArmHi, bigArmScore);

        while (imu->is_calibrating()) {
            pros::delay(20);
        }
        imu->set_rotation(0);
    }

    lemlib::Chassis *getChass() {
        return chass[MOGO];
    }

    double getRotation() {
        return imu->get_rotation() * imuConstant;
    }

    double getChassPos() {
        std::vector<double> v1 = drivetrain->leftMotors->get_position_all(),
            v2 = drivetrain->rightMotors->get_position_all();
        double avg = 0;
        for (double i : v1) {
            avg += i;
        }
        for (double i : v2) {
            avg += i;
        }
        return avg / 6;
    }

    double getLeftPos() {
        std::vector<double> v = drivetrain->leftMotors->get_position_all();
        double avg = 0;
        for (double i : v) {
            avg += i;
        }
        return avg / 3;
    }

    double getRightPos() {
        std::vector<double> v = drivetrain->rightMotors->get_position_all();
        double avg = 0;
        for (double i : v) {
            avg += i;
        }
        return avg / 3;
    }

    double getHorizPos() {
        return horizTrackRotSensor->get_position();
    }

    double getVertPos() {
        return vertTrackRotSensor->get_position();
    }

    void reset_imu() {
        imu->set_rotation(0);
    }

    void reset_chass() {
        drivetrain->leftMotors->tare_position_all();
        drivetrain->rightMotors->tare_position_all();
    }

    void reset() {
        reset_imu();
        reset_chass();
    }

    void set_brake_mode(pros::MotorBrake mode) {
        drivetrain->leftMotors->set_brake_mode_all(mode);
        drivetrain->rightMotors->set_brake_mode_all(mode);
    }

    void drive_chass(double lPct, double rPct) {
        drivetrain->leftMotors->move_voltage(lPct * 120);
        drivetrain->rightMotors->move_voltage(rPct * 120);
    }

    void spin_intk(double pct) {
        intake.move_voltage(pct * 120);
    }

    void deactivate_all_pistons() {
        if (frontLeftArmDown) toggleFrontLeftArm();
        if (frontRightArmDown) toggleFrontRightArm();
        if (goalClampClosed) toggleGoalClamp();
    }
}