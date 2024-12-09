#pragma once

#include "main.h"

namespace test {
    void runFwdBwdTest(int target, int timeout, bool mogo) {
        delete bot::chass[mogo ? 1 : 0];
        bot::chass[mogo ? 1 : 0] = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[mogo ? 1 : 0], pid::angular_controller[mogo ? 1 : 0], *bot::odomSensors[mogo ? 1 : 0]);
        bot::setPose(0, 0, 0);
        bot::moveToPose(0, target, 0, timeout, { .forwards = true }, false);
        double y = bot::getPose().y;
        std::cout << "forward: " << y << std::endl;
        bot::setPose(0, 0, 0);
        bot::moveToPose(0, -target, 0, timeout, { .forwards = false }, false);
        y = bot::getPose().y;
        std::cout << "backward: " << y << std::endl;
    }

    void runAngularPID_kPs(double kD, double begin, double end, double step, double target, int timeout, bool mogo) {
        pid::angular_controller[mogo ? 1 : 0].kD = kD;
        for (double kP = begin; kP <= end; kP += step) {
            int origangle = bot::getRotation();
            std::cout << "kP: " << kP << std::endl;
            pid::angular_controller[mogo ? 1 : 0].kP = kP;
            lemlib::Chassis *chassTest = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[mogo ? 1 : 0], pid::angular_controller[mogo ? 1 : 0], *bot::odomSensors[mogo ? 1 : 0]);
            chassTest->setPose(0, 0, 0);
            chassTest->turnToHeading(target, timeout, {}, false);
            delete chassTest;
            std::cout << "final angle: " << bot::getRotation() - origangle << std::endl;
        }
    }

    void runAngularPID_kDs(double kP, double begin, double end, double step, double target, int timeout, bool mogo) {
        pid::angular_controller[mogo ? 1 : 0].kP = kP;
        for (double kD = begin; kD <= end; kD += step) {
            int origangle = bot::getRotation();
            std::cout << "kD: " << kD << std::endl;
            pid::angular_controller[mogo ? 1 : 0].kD = kD;
            lemlib::Chassis *chassTest = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[mogo ? 1 : 0], pid::angular_controller[mogo ? 1 : 0], *bot::odomSensors[mogo ? 1 : 0]);
            chassTest->setPose(0, 0, 0);
            chassTest->turnToHeading(target, timeout, {}, false);
            delete chassTest;
            std::cout << "final angle: " << bot::getRotation() - origangle << std::endl;
        }
    }

    void runLateralBSearchkP(double kD, double l, double r, double target, int timeout, bool mogo) {
        pid::lateral_controller[mogo ? 1 : 0].kD = kD;
        while (1) {
            double m = (l + r) / 2;
            pid::lateral_controller[mogo ? 1 : 0].kP = m;
            std::cout << l << ", " << r << ", mid: " << m << std::endl;
            runFwdBwdTest(target, timeout, mogo);
            while (1) {
                pros::delay(20);
                if (bot::master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                    l = m;
                    break;
                }
                if (bot::master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                    r = m;
                    break;
                }
                if (bot::master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                    break;
                }
            }
        }
    }

    void runLateralBSearchkD(double l, double r, double target, int timeout, bool mogo) {
        while (1) {
            double m = (l + r) / 2;
            pid::lateral_controller[mogo ? 1 : 0].kD = m;
            std::cout << l << ", " << r << ", mid: " << m << std::endl;
            runFwdBwdTest(target, timeout, mogo);
            while (1) {
                pros::delay(20);
                if (bot::master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
                    l = m;
                    break;
                }
                if (bot::master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                    r = m;
                    break;
                }
                if (bot::master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                    break;
                }
            }
        }
    }

    void pidTune() {
        // runAngularPID_kPs(0, 2, 2.8, 0.1, 90, 3000, false);
        // runAngularPID_kDs(3.1, 24.4, 25.4, 0, 90, 2000, false);
        // runLateralBSearchkP(0, 0, 200, 48, 2000, true);
        runLateralBSearchkD(150, 300, 48, 2000, true);
    }

    void handleDebugInputs() {
        if (bot::master.get_digital_new_press(DIGITAL_UP)) {
            printf("Current Pose: %f, %f, %f\n", bot::chass[0]->getPose().x, bot::chass[0]->getPose().y, bot::chass[0]->getPose().theta);
            printf("Current Pose[1]: %f, %f, %f\n", bot::chass[1]->getPose().x, bot::chass[1]->getPose().y, bot::chass[1]->getPose().theta);
            printf("IMU rotation: %f\n", bot::getRotation());
        }
    }
}