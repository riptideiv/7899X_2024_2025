#pragma once

#include<map>
#include<iostream>

#define PID_DEBUG_ON false

namespace pid {
    struct constants {
        double kP, kI, kD, kIthres;
        constants(double kP, double kI, double kD, double kIthres) : kP(kP), kI(kI), kD(kD), kIthres(kIthres) {}
        constants() {
            kP = 0;
            kI = 0;
            kD = 0;
            kIthres = 0;
        }
    };

    std::map<int, constants> PID_TURN[2];
    constants PID_DRIVE[2];

    bool PID_WITH_GOAL;
    bool PID_FLIPPED;

    void set_mogo(bool value) {
        PID_WITH_GOAL = value;
    }

    void set_flipped(bool value) {
        PID_FLIPPED = value;
    }

    void initialize() {
        PID_TURN[0][15] = constants(2.1, 0.075, 1.5, 3);
        PID_TURN[0][45] = constants(0.9, 0.075, 1.1, 3);
        PID_TURN[0][90] = constants(0.7, 0.075, 1.1, 3);
        PID_TURN[0][135] = constants(0.5, 0.075, 0.4, 6);
        PID_TURN[0][180] = constants(0.41, 0.075, 0.55, 6);

        for (const auto &pair : PID_TURN[0]) {
            PID_TURN[1][pair.first] = constants(pair.second.kP + 0.025, pair.second.kI, pair.second.kD + 0.4, pair.second.kIthres);
        }

        PID_DRIVE[0] = constants(0.12, 0.1, 0.2, 20);
        PID_DRIVE[1] = constants(0.12, 0.1, 0.3, 20);

        set_flipped(false);
        set_mogo(false);
    }

    void drive(double target, int timeout, bool reset = true) {
        if (reset) {
            bot::chass.reset_position();
        }
        constants &c = (PID_DRIVE[PID_WITH_GOAL]);
        double error, integral = 0, derivative, prevError = 0;
        double power;
        int t = pros::millis();
        while (pros::millis() - t < timeout) {
            error = target - bot::chass.get_avg_position();
            if (fabs(error) < c.kIthres) integral += error;
            else integral = 0;
            if (error > 0 && prevError < 0 || error < 0 && prevError>0) integral = -integral / 4;
            derivative = error - prevError;
            prevError = error;
            power = c.kP * error + c.kI * integral + c.kD * derivative;
            bot::pwrChassPct(power, power);
            pros::delay(20);
            if (PID_DEBUG_ON) {
                std::cout << "PID Drive Error: " << error << std::endl;
            }
        }
        bot::pwrChassPct(0, 0);
    }

    void driveWait(const double &dist, double lmult, double rmult, bool reset) {
        if (reset) {
            bot::chass.reset_position();
        }
        if (PID_FLIPPED) {
            double t = lmult;
            lmult = rmult;
            rmult = t;
        }
        double curr;
        if (lmult > rmult) curr = bot::chass.leftMotors->get_position();
        else curr = bot::chass.rightMotors->get_position();
        double error, prev_error;
        error = prev_error = dist - curr;
        printf("driveWait running... target is %f units, error is %f\n", dist, error);
        while (true) {
            pros::delay(10);
            if (lmult > rmult) curr = bot::chass.leftMotors->get_position();
            else curr = bot::chass.rightMotors->get_position();
            error = dist - curr;
            if (error == 0 || error / prev_error <= 0) break;
            prev_error = error;
            if (error > 0) bot::pwrChassPct(100 * lmult, 100 * rmult);
            else bot::pwrChassPct(-100 * lmult, -100 * rmult);
        }
        printf("driveWait finished... target was %f units, error is %f\n", dist, error);
    }

    void arcWait(const double &angle, double lmult, double rmult, bool reset) {
        if (reset) {
            bot::imu.set_rotation(0);
        }
        double target_angle = angle;
        if (PID_FLIPPED) {
            double t = lmult;
            lmult = rmult;
            rmult = t;
            target_angle = -angle;
        }
        double curr = bot::get_rotation();
        double error, prev_error;
        error = prev_error = target_angle - curr;
        printf("arcWait running... target is %f degrees, error is %f\n", target_angle, error);
        while (true) {
            pros::delay(10);
            curr = bot::get_rotation();
            error = target_angle - curr;
            if (error == 0 || error / prev_error <= 0) break;
            prev_error = error;
            bot::pwrChassPct(100 * lmult, 100 * rmult);
        }
        printf("arcWait finished... target was %f degrees, error is %f\n", target_angle, error);
    }

    constants *constants_used = &(PID_TURN[0][135]);
    double debugerror;

    void turn(double target, int timeout, bool reset) {
        debugerror = 100;

        if (reset) {
            bot::imu.set_rotation(0);
        }
        if (PID_FLIPPED) target = -target;

        double error = target - bot::get_rotation();

        std::cout << target << ' ' << error << std::endl;

        constants *c;
        int closest_angle = -1000;
        for (const auto &pair : PID_TURN[PID_FLIPPED]) {
            if (abs(pair.first - fabs(error)) < abs(closest_angle - fabs(error))) {
                closest_angle = pair.first;
            }
        }
        c = &PID_TURN[PID_WITH_GOAL][closest_angle];

        constants_used = c;

        // std::cout << "Closest angle: " << closest_angle << std::endl;
        double integral = 0, derivative, prevError = error;
        double power;
        int t = pros::millis();
        while (pros::millis() - t < timeout) {
            error = target - bot::get_rotation();
            if (fabs(error) < c->kIthres) integral += error; // CHANGE THIS THRESHOLD
            else integral = 0;
            if (error > 0 && prevError < 0 || error < 0 && prevError>0) integral = -integral / 4;
            derivative = error - prevError;
            prevError = error;
            power = c->kP * error + c->kI * integral + c->kD * derivative;
            bot::pwrChassPct(power, -power);
            pros::delay(20);
            if (PID_DEBUG_ON) {
                std::cout << "PID Turn Error: " << error << std::endl;
            }
            // debugerror = error;
        }
        bot::pwrChassPct(0, 0);
    }
}