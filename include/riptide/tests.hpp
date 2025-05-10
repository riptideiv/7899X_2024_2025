#pragma once

#include "main.h"

namespace test {
    void runFwdBwdTest(int target, int timeout) {
        delete bot::chass[0];
        bot::chass[0] = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[0], pid::standard_angular_controller[0], *bot::odomSensors[0]);
        bot::setPose(0, 0, 0);
        bot::moveToPoint(0, target, timeout, { .forwards = true }, false);
        double y = bot::getPose().y;
        std::cout << "forward: " << y << std::endl;
        bot::setPose(0, 0, 0);
        bot::moveToPoint(0, -target, timeout, { .forwards = false }, false);
        y = bot::getPose().y;
        std::cout << "backward: " << y << std::endl;
    }

    void runTurnTest(double target, int timeout) {
        delete bot::chass[0];
        bot::chass[0] = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[0], pid::standard_angular_controller[0], *bot::odomSensors[0]);
        bot::setPose(0, 0, 0);
        double angle = bot::getRotation();
        bot::turnToHeading(target, timeout, {}, false);
        std::cout << "turn: " << (bot::getRotation() - angle) << std::endl;
        bot::setPose(0, 0, 0);
        angle = bot::getRotation();
        bot::turnToHeading(-target, timeout, {}, false);
        std::cout << "turn back: " << (bot::getRotation() - angle) << std::endl;
    }

    void runAngularPID_kPs(double kD, double begin, double end, double step, double target, int timeout) {
        pid::standard_angular_controller[0].kD = kD;
        for (double kP = begin; kP <= end; kP += step) {
            int origangle = bot::getRotation();
            std::cout << "kP: " << kP << std::endl;
            pid::standard_angular_controller[0].kP = kP;
            lemlib::Chassis *chassTest = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[0], pid::standard_angular_controller[0], *bot::odomSensors[0]);
            chassTest->setPose(0, 0, 0);
            chassTest->turnToHeading(target, timeout, {}, false);
            delete chassTest;
            std::cout << "final angle: " << bot::getRotation() - origangle << std::endl;
        }
    }

    void runAngularPID_kDs(double kP, double begin, double end, double step, double target, int timeout) {
        pid::standard_angular_controller[0].kP = kP;
        for (double kD = begin; kD <= end; kD += step) {
            int origangle = bot::getRotation();
            std::cout << "kD: " << kD << std::endl;
            pid::standard_angular_controller[0].kD = kD;
            lemlib::Chassis *chassTest = new lemlib::Chassis(*bot::drivetrain, pid::lateral_controller[0], pid::standard_angular_controller[0], *bot::odomSensors[0]);
            chassTest->setPose(0, 0, 0);
            chassTest->turnToHeading(target, timeout, {}, false);
            delete chassTest;
            std::cout << "final angle: " << bot::getRotation() - origangle << std::endl;
        }
    }

    void runLateralBSearchkP(double kD, double l, double r, double target, int timeout) {
        pid::lateral_controller[0].kD = kD;
        while (1) {
            double m = (l + r) / 2;
            pid::lateral_controller[0].kP = m;
            std::cout << l << ", " << r << ", mid: " << m << std::endl;
            runFwdBwdTest(target, timeout);
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

    void runLateralBSearchkD(double kP, double l, double r, double target, int timeout) {
        pid::lateral_controller[0].kP = kP;
        while (1) {
            double m = (l + r) / 2;
            pid::lateral_controller[0].kD = m;
            std::cout << l << ", " << r << ", mid: " << m << std::endl;
            runFwdBwdTest(target, timeout);
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

    void runAngularBSearchkP(double kD, double l, double r, double target, int timeout) {
        pid::standard_angular_controller[0].kD = kD;
        while (1) {
            double m = (l + r) / 2;
            pid::standard_angular_controller[0].kP = m;
            std::cout << l << ", " << r << ", mid: " << m << std::endl;
            runTurnTest(target, timeout);
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

    void runAngularBSearchkD(double kP, double l, double r, double target, int timeout) {
        pid::standard_angular_controller[0].kP = kP;
        while (1) {
            double m = (l + r) / 2;
            pid::standard_angular_controller[0].kD = m;
            std::cout << l << ", " << r << ", mid: " << m << std::endl;
            runTurnTest(target, timeout);
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
        goalClamp.set_value(true);
        pros::delay(500);

        // runAngularPID_kPs(0, 2, 2.8, 0.1, 90, 3000);
        // runAngularPID_kDs(3.1, 24.4, 25.4, 0, 90, 2000);
        // runLateralBSearchkP(0, 10, 50, 24, 2000);
        // runLateralBSearchkD(25, 0, 300, 48, 2000);
        // runAngularBSearchkP(0, 1.1875, 1.1875, 135, 1500);
        runAngularBSearchkD(7, 0, 150, 90, 1500);
        // kP: 4-6
    }

    void findTrackingRadius(bool clamp = false) {
        if (clamp) {
            bot::toggleGoalClamp();
            pros::delay(500);
        }
        double avg = 0;
        double avgL = 0;
        double avrR = 0;
        for (int i = 0; i < 5; i++) {
            int t = clock();
            int speed = 30 + (i * 10);
            std::cout << "Run " << (i + 1) << " with speed: " << speed << '\n';
            bot::drive_chass(speed, -speed);
            pros::delay(1000);
            bot::horizTrackRotSensor->reset();
            double initL = getLeftPos();
            double initR = getRightPos();
            double initAngle = bot::imu->get_rotation();
            pros::delay(3000);
            double pos = bot::horizTrackRotSensor->get_position() / 36000.0 * 2.75 * M_PI;
            double posL = getLeftPos() - initL;
            double posR = getRightPos() - initR;
            double angle = (bot::imu->get_rotation() - initAngle) / 180.0 * M_PI;
            std::cout << "horizRadius: " << (pos / angle) << '\n' << "leftRadius: " << (posL / angle) << '\n' << "rightRadius: " << (posR / angle) << '\n';
            avg += (pos / angle);
            avgL += (posL / angle);
            avrR += (posR / angle);
        }
        std::cout << "average radius: " << (avg / 5) << '\n' << "avgL: " << (avgL / 5) << '\n' << "avgR: " << (avrR / 5) << '\n';
    }

    void testMotorAccels() {
        // run each drivetrain motor individually 5 times and calculate the average time to reach 50% speed
        int ports[] = { -1, 2, 8, -3, 9, -4 };
        double times[6] = { 0 };
        for (int j = 0; j < 5; j++) {
            std::cout << "Run " << (j + 1) << ":\n";
            for (int i = 0; i < 6; i++) {
                pros::Motor m(ports[i]);
                m.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                m.move_voltage(12000);
                int t = pros::millis();
                int rpm = 500;
                while (m.get_actual_velocity() < rpm) {
                    pros::delay(3);
                }
                double timeTaken = (pros::millis() - t) / 1000.0;
                std::cout << "motor " << ports[i] << " time: " << timeTaken << " seconds to reach 500 rpm\n";
                times[i] += timeTaken;
                m.move_velocity(0);
                pros::delay(500);
            }
        }
        for (int i = 0; i < 6; i++) {
            std::cout << "motor " << ports[i] << " average time: " << (times[i] / 5) << " seconds to reach 500 rpm\n";
        }
    }
}