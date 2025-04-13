#pragma once

#include "main.h"
#include "robot_globals.hpp"
#include "sensors.hpp"
#include "bigArm.hpp"
#include "intake.hpp"
#include "pneumatics.hpp"

namespace bot {
    lemlib::ExpoDriveCurve driveSteerCurve(10, 15, 1.01);
    lemlib::ExpoDriveCurve driveThrottleCurve(10, 15, 1);

    pros::Controller master(pros::E_CONTROLLER_MASTER);

    lemlib::Drivetrain *drivetrain;

    lemlib::Chassis *chass[2]; // 0 = no mogo, 1 = mogo

    void initialize() {
        init_sensors();

        drivetrain = new lemlib::Drivetrain(
            new pros::MotorGroup({ -1,8,9 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            new pros::MotorGroup({ 2,-3,-4 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            12.344, // 12.344 inch track width
            lemlib::Omniwheel::NEW_275, // using new 2.75" omnis
            600, // drivetrain rpm is 360
            2 // horizontal drift is 2
        );

        chass[0] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[0], pid::angular_controller[0], *odomSensors[0], &driveThrottleCurve, &driveSteerCurve);
        chass[1] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[1], pid::angular_controller[1], *odomSensors[1], &driveThrottleCurve, &driveSteerCurve);

        intake.initialize(20, 19);

        bigArm.initialize(7, 6);

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

    //! gets average positions of the left and right drivetrain sides
    double getChassPos() {
        return (getLeftPos() + getRightPos()) / 2;
    }

    double getLeftVelo() {
        std::vector<double> v = drivetrain->leftMotors->get_actual_velocity_all();
        double avg = 0;
        for (double i : v) {
            avg += i;
        }
        return avg / v.size();
    }

    double getRightVelo() {
        std::vector<double> v = drivetrain->rightMotors->get_actual_velocity_all();
        double avg = 0;
        for (double i : v) {
            avg += i;
        }
        return avg / v.size();
    }

    //! gets average velocities of the left and right drivetrain sides
    double getChassVelo() {
        return (getLeftVelo() + getRightVelo()) / 2;
    }

    void reset_imu() {
        imu->set_rotation(0);
    }

    void reset_drivetrain() {
        drivetrain->leftMotors->tare_position_all();
        drivetrain->rightMotors->tare_position_all();
    }

    //! resets imu and drivetrain positions
    void _reset() {
        reset_imu();
        reset_drivetrain();
    }

    //! sets the brake mode (brake, coast, or hold)
    void set_brake_mode(pros::MotorBrake mode) {
        drivetrain->leftMotors->set_brake_mode_all(mode);
        drivetrain->rightMotors->set_brake_mode_all(mode);
    }

    //! drives the chassis
    void drive_chass(double lPct, double rPct) {
        drivetrain->leftMotors->move_voltage(lPct * 120);
        drivetrain->rightMotors->move_voltage(rPct * 120);
    }

    //! toggle the mogo clamp and transfer chassis pose
    void toggleGoalClamp() {
        goalClampClosed = !goalClampClosed;
        goalClamp.set_value(goalClampClosed);
        MOGO = goalClampClosed;
        chass[MOGO]->setPose(chass[!MOGO]->getPose());
    }

    //! wrapper for lemlib's moveToPoint function that is aware of the MOGO state.
    void deactivate_all_pistons() {
        if (frontLeftArmDown) toggleFrontLeftArm();
        if (frontRightArmDown) toggleFrontRightArm();
        if (goalClampClosed) toggleGoalClamp();
        if (intakeLiftUp) toggleIntakeLift();
    }

    //! wrapper for lemlib's moveToPoint function that is aware of the MOGO state.
    void moveToPoint(double x, double y, double timeout, lemlib::MoveToPointParams params = {}, bool async = false) {
        chass[MOGO]->moveToPoint(x, y, timeout, params, async);
    }

    //! wrapper for lemlib's moveToPose function that is aware of the MOGO state.
    void moveToPose(double x, double y, double theta, double timeout, lemlib::MoveToPoseParams params = {}, bool async = false) {
        chass[MOGO]->moveToPose(x, y, theta, timeout, params, async);
    }

    //! wrapper for lemlib's turnToHeading function that is aware of the MOGO state.
    void turnToHeading(double theta, double timeout, lemlib::TurnToHeadingParams params = {}, bool async = false) {
        chass[MOGO]->turnToHeading(theta, timeout, params, async);
    }

    //! wrapper for lemlib's turnToPoint function that is aware of the MOGO state.
    void turnToPoint(double x, double y, double timeout, lemlib::TurnToPointParams params = {}, bool async = false) {
        chass[MOGO]->turnToPoint(x, y, timeout, params, async);
    }

    //! wrapper for lemlib's setPose function that is aware of the MOGO state.
    void setPose(double x, double y, double theta) {
        chass[MOGO]->setPose(x, y, theta);
    }

    lemlib::Pose getPose() {
        return chass[MOGO]->getPose();
    }

    /**
     * drives for a certain distance, and then exits without stopping.
     * @param lMult multiplier for left side of drivetrain (range -1 to 1)
     * @param rMult multiplier for right side of drivetrain (range -1 to 1)
     * @param dist distance to drive for in inches
     */
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