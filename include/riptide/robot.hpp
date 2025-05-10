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

    lemlib::Chassis *chass[2], *straight_chass[2], *connecting_chass[2]; // 0 = no mogo, 1 = mogo

    void initialize() {
        init_sensors();

        drivetrain = new lemlib::Drivetrain(
            new pros::MotorGroup({ -1,8,9 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            new pros::MotorGroup({ 2,-3,-4 }, pros::v5::MotorGears::rpm_600, pros::v5::MotorEncoderUnits::degrees),
            13, // this go up -> 180 turn x value go down
            // 12.25: 0, 700
            lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
            450, // drivetrain rpm is 450
            1.5 // horizontal drift is 2
        );

        chass[0] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[0], pid::standard_angular_controller[0], *odomSensors[0], &driveThrottleCurve, &driveSteerCurve);
        chass[1] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[1], pid::standard_angular_controller[1], *odomSensors[1], &driveThrottleCurve, &driveSteerCurve);

        // straight-only chassis
        straight_chass[0] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[0], pid::straight_angular_controller, *odomSensors[0], &driveThrottleCurve, &driveSteerCurve);
        straight_chass[1] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[1], pid::straight_angular_controller, *odomSensors[1], &driveThrottleCurve, &driveSteerCurve);

        // connecting chassis
        connecting_chass[0] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[0], pid::connecting_angular_controller[0], *odomSensors[0], &driveThrottleCurve, &driveSteerCurve);
        connecting_chass[1] = new lemlib::Chassis(*drivetrain, pid::lateral_controller[1], pid::connecting_angular_controller[1], *odomSensors[1], &driveThrottleCurve, &driveSteerCurve);

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

    double getLeftCurrent() {
        std::vector<long> v = drivetrain->leftMotors->get_current_draw_all();
        double avg = 0;
        for (double i : v) {
            avg += i * 3.25 * M_PI;
            // avg += i;
        }
        return avg / 3;
    }

    double getRightCurrent() {
        std::vector<long> v = drivetrain->rightMotors->get_current_draw_all();
        double avg = 0;
        for (double i : v) {
            avg += i * 3.25 * M_PI;
            // avg += i;
        }
        return avg / 3;
    }

    double getChassCurrent() {
        return (getLeftCurrent() + getRightCurrent()) / 2;
    }

    double getLeftPos() {
        std::vector<double> v = drivetrain->leftMotors->get_position_all();
        double avg = 0;
        for (double i : v) {
            avg += i * 3.25 * M_PI;
            // avg += i;
        }
        return avg / 3;
    }

    double getRightPos() {
        std::vector<double> v = drivetrain->rightMotors->get_position_all();
        double avg = 0;
        for (double i : v) {
            avg += i * 3.25 * M_PI;
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
        getChass()->setPose(chass[!MOGO]->getPose());
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
        getChass()->moveToPoint(x, y, timeout, params, async);
    }

    //! wrapper for lemlib's moveToPose function that is aware of the MOGO state.
    void moveToPose(double x, double y, double theta, double timeout, lemlib::MoveToPoseParams params = {}, bool async = false) {
        getChass()->moveToPose(x, y, theta, timeout, params, async);
    }

    //! wrapper for lemlib's turnToHeading function that is aware of the MOGO state.
    void turnToHeading(double theta, double timeout, lemlib::TurnToHeadingParams params = {}, bool async = false) {
        getChass()->turnToHeading(theta, timeout, params, async);
    }

    //! wrapper for lemlib's turnToPoint function that is aware of the MOGO state.
    void turnToPoint(double x, double y, double timeout, lemlib::TurnToPointParams params = {}, bool async = false) {
        getChass()->turnToPoint(x, y, timeout, params, async);
    }

    //! wrapper for lemlib's setPose function that is aware of the MOGO state.
    void setPose(double x, double y, double theta) {
        getChass()->setPose(x, y, theta);
    }

    lemlib::Pose getPose() {
        return getChass()->getPose();
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

    void alliStakeMacro() {
        bool immed = bigArm.move_target < posHigh + 1000;
        double theta = getChass()->getPose().theta * M_PI / 180;
        double x = -9 * std::sin(theta);
        double y = -9 * std::cos(theta) + 0.5;
        double targx = -15.5 * std::sin(theta);
        double targy = -15.5 * std::cos(theta) + 0.5;
        getChass()->setPose(x, y, getChass()->getPose().theta);
        if (immed) {
            bigArm.setMaxSpeed(70);
            bigArm.set_target(28800);
            bigArm.kP = 2;
        }
        moveToPoint(targx, targy, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 4 });
        if (!immed) {
            bigArm.setMaxSpeed(60);
            bigArm.set_target(28800);
            bigArm.kP = 2;
        }
        moveToPoint(targx, targy, 800, {}, true);
        while (getChass()->isInMotion() && bigArm.rotation->get_position() < 26750) pros::delay(3);
        getChass()->cancelAllMotions();
        pros::delay(100);
        driveWait(1, 1, -4);
        bigArm.reset();
        bigArm.setMaxSpeed(100);
        getChass()->arcade(0, 0);
    }
}