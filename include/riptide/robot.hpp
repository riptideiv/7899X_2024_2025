#pragma once

#include "main.h"
#include "robot_globals.hpp"
#include "sensors.hpp"
#include "bigArm.hpp"
#include "intake.hpp"
#include "pneumatics.hpp"

namespace bot {
    lemlib::ExpoDriveCurve driveSteerCurve(20, 15, 1.02);

    pros::Controller master(pros::E_CONTROLLER_MASTER);

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

        chass[0] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[0], pid::angular_controller[0], *odomSensors[0], &(lemlib::defaultDriveCurve), &driveSteerCurve);
        chass[1] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[1], pid::angular_controller[1], *odomSensors[1], &(lemlib::defaultDriveCurve), &driveSteerCurve);

        int bigArmHi = 33400,
            bigArmMid = 33400,
            bigArmLow = 35191,
            bigArmToScore = 23853,
            bigArmScore = 19800;

        bigArm.initialize(-15, 21, bigArmLow, bigArmMid, bigArmHi, bigArmToScore, bigArmScore);
        intake.initialize(-1);

        chass[0]->calibrate();
    }

    lemlib::Chassis *getChass() {
        return chass[MOGO];
    }

    double getRotation() {
        return imu->get_rotation();
    }

    double getLeftPos() {
        std::vector<double> v = drivetrain->leftMotors->get_position_all();
        double avg = 0;
        for (double i : v) {
            avg += i * 2.75 * M_PI;
            // avg += i;
        }
        return avg / 3;
    }

    double getRightPos() {
        std::vector<double> v = drivetrain->rightMotors->get_position_all();
        double avg = 0;
        for (double i : v) {
            avg += i * 2.75 * M_PI;
            // avg += i;
        }
        return avg / 3;
    }

    double getChassPos() {
        return (getLeftPos() + getRightPos()) / 2;
    }

    void reset_imu() {
        imu->set_rotation(0);
    }

    void reset_drivetrain() {
        drivetrain->leftMotors->tare_position_all();
        drivetrain->rightMotors->tare_position_all();
    }

    void _reset() {
        reset_imu();
        reset_drivetrain();
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
        intake.set_speed(pct * 1.27);
    }

    void deactivate_all_pistons() {
        if (frontLeftArmDown) toggleFrontLeftArm();
        if (frontRightArmDown) toggleFrontRightArm();
        if (goalClampClosed) toggleGoalClamp();
    }

    void moveToPoint(double x, double y, double timeout, lemlib::MoveToPointParams params = {}, bool async = false) {
        chass[MOGO]->moveToPoint(x, y, timeout, params, async);
    }

    void moveToPose(double x, double y, double theta, double timeout, lemlib::MoveToPoseParams params = {}, bool async = false) {
        chass[MOGO]->moveToPose(x, y, theta, timeout, params, async);
    }

    void turnToHeading(double theta, double timeout, lemlib::TurnToHeadingParams params = {}, bool async = false) {
        chass[MOGO]->turnToHeading(theta, timeout, params, async);
    }

    void turnToPoint(double x, double y, double timeout, lemlib::TurnToPointParams params = {}, bool async = false) {
        chass[MOGO]->turnToPoint(x, y, timeout, params, async);
    }

    void setPose(double x, double y, double theta) {
        chass[MOGO]->setPose(x, y, theta);
    }

    lemlib::Pose getPose() {
        return chass[MOGO]->getPose();
    }

    void driveWait(double lMult, double rMult, double dist) {
        double curr;
        curr = lMult > rMult ? getLeftPos() : getRightPos();
        double error, prev_error;
        error = prev_error = dist;
        double target = dist + curr;
        while (true) {
            pros::delay(10);
            curr = lMult > rMult ? getLeftPos() : getRightPos();
            error = target - curr;
            if (prev_error == 0 || error / prev_error <= 0) break;
            prev_error = error;
            if (error > 0) {
                getChass()->tank(127 * lMult, 127 * rMult);
            } else {
                getChass()->tank(-127 * lMult, -127 * rMult);
            }
        }
    }
}