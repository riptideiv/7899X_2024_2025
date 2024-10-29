#pragma once

#include "main.h"
#include<map>

namespace pid {
    struct Constants {
        double kP;
        double kI;
        double kD;
        double integral_thres;
        Constants(double kP, double kI, double kD, double integral_thres) : kP(kP), kI(kI), kD(kD), integral_thres(integral_thres) {}
        Constants() : kP(0), kI(0), kD(0), integral_thres(0) {}
    };

    std::map<int, Constants> kTurn[2];

    enum PID_CONSTS_MODE {
        PID_MOGO,
        PID_EMPTY
    };

    Constants kDrive = Constants(0.3, 0.001, 0.43, 50);

    void initPID() {
        kTurn[PID_EMPTY][15] = Constants(2.5, 0, 1.6, 5);
        kTurn[PID_MOGO][15] = Constants(2.5, 0, 1.9, 5);
        kTurn[PID_EMPTY][45] = Constants(1.4, 0, 1.3, 10);
        kTurn[PID_MOGO][45] = Constants(1.4, 0, 1.6, 10);
        kTurn[PID_EMPTY][135] = Constants(0.7, 0.05, 1.3, 10);
        kTurn[PID_MOGO][135] = Constants(0.7, 0.05, 1.6, 10);
    }

    void driveWait(const double &dist, double lmult, double rmult, bool reset) {
        if (reset) {
            xrobot::left_mg.set_zero_position_all(0);
            xrobot::right_mg.set_zero_position_all(0);
        }
        if (auton::flipped) {
            double t = lmult;
            lmult = rmult;
            rmult = t;
        }
        double curr;
        if (lmult > rmult) curr = xrobot::left_mg.get_position();
        else curr = xrobot::right_mg.get_position();
        double error, prev_error;
        error = prev_error = dist - curr;
        printf("driveWait running... target is %f units, error is %f\n", dist, error);
        while (true) {
            pros::delay(10);
            if (lmult > rmult) curr = xrobot::left_mg.get_position();
            else curr = xrobot::right_mg.get_position();
            error = dist - curr;
            if (error == 0 || error / prev_error <= 0) break;
            prev_error = error;
            if (error > 0) xrobot::drivePct(100 * lmult, 100 * rmult);
            else xrobot::drivePct(-100 * lmult, -100 * rmult);
        }
        printf("driveWait finished... target was %f units, error is %f\n", dist, error);
    }

    void driveWait(const double &dist) {
        driveWait(dist, 1, 1, true);
    }

    bool arcWait(double angle, int lspct, int rspct, bool reset, int maxtime) {
        if (reset) xrobot::sinertial.set_rotation(0);
        if (auton::flipped) {
            angle = -angle;
            int t = lspct;
            lspct = rspct;
            rspct = t;
        }
        double curr;
        double error, prev_error;
        error = prev_error = angle - xrobot::get_rotation();

        if (error > 0) {
            if (lspct < rspct) {
                std::cout << "bruh wtf\n";
                return false;
            }
        } else if (lspct > rspct) {
            std::cout << "bruh wtf\n";
            return false;
        }

        double startTime = pros::millis();
        while (pros::millis() - startTime < maxtime) {
            pros::delay(10);
            curr = xrobot::get_rotation();
            error = angle - curr;
            std::cout << "arcwait: " << error << "\n\n";
            if (error == 0 || error / prev_error <= 0) return true;
            prev_error = error;
            xrobot::driveV(lspct, rspct);
        }
        return false;
    }

    bool arcWait(const double &angle, const int &lspct, const int &rspct, bool reset) {
        return arcWait(angle, lspct, rspct, reset, 1000000);
    }

    void drive(double target, int wait, bool reset, pid::Constants k = pid::kDrive) {
        if (reset) {
            xrobot::left_mg.set_zero_position_all(0);
            xrobot::right_mg.set_zero_position_all(0);
        }
        double leftError = target;
        double rightError = target;
        double leftIntegral = 0;
        double rightIntegral = 0;
        double leftDerivative = 0;
        double rightDerivative = 0;
        double leftPrevError = 0;
        double rightPrevError = 0;
        double leftOutput = 0;
        double rightOutput = 0;
        double startTime = pros::millis();
        while (pros::millis() - startTime < wait) {
            if (abs(leftError) < k.integral_thres) {
                leftIntegral += leftError;
            } else {
                leftIntegral = 0;
            }
            if (abs(rightError) < k.integral_thres) {
                rightIntegral += rightError;
            } else {
                rightIntegral = 0;
            }
            leftDerivative = leftError - leftPrevError;
            rightDerivative = rightError - rightPrevError;
            leftOutput = k.kP * leftError + k.kI * leftIntegral + k.kD * leftDerivative;
            rightOutput = k.kP * rightError + k.kI * rightIntegral + k.kD * rightDerivative;
            leftPrevError = leftError;
            rightPrevError = rightError;
            leftError = target - xrobot::get_avg_pos(xrobot::left_mg);
            rightError = target - xrobot::get_avg_pos(xrobot::right_mg);
            xrobot::driveV(leftOutput, rightOutput);
            printf("lError: %f, rError: %f\n", leftError, rightError);
            pros::delay(20);
        }
        xrobot::driveV(0, 0);
    }

    void turn(double target, int wait, bool reset, pid::Constants k) {
        if (reset) {
            xrobot::sinertial.set_rotation(0);
        }
        if (auton::flipped) target = -target;
        double error = target - xrobot::get_rotation();
        double integral = 0;
        double derivative = 0;
        double prevError = 0;
        double output = 0;
        double startTime = pros::millis();
        while (pros::millis() - startTime < wait) {
            if (abs(error) < k.integral_thres) {
                integral += error;
            } else {
                integral = 0;
            }
            if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
                integral = 0;
            }
            derivative = error - prevError;
            output = k.kP * error + k.kI * integral + k.kD * derivative;
            xrobot::driveV(output, -output);
            prevError = error;
            error = target - xrobot::get_rotation();
            pros::delay(20);
        }
        printf("Error: %f, output: %f\n", error, output);
        xrobot::driveV(0, 0);
    }

    void turn(double target, int wait, bool reset, PID_CONSTS_MODE mode) {
        auto closest = kTurn[mode].begin();
        double error = target - xrobot::get_rotation();
        for (auto it = kTurn[mode].begin(); it != kTurn[mode].end(); ++it) {
            if (abs(it->first - error) < abs(closest->first - error)) {
                closest = it;
            }
        }
        printf("Using %d with kP %.2f\n", closest->first, closest->second.kP);
        turn(target, wait, reset, closest->second);
    }
}