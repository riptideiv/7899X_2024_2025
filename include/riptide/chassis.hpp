#pragma once

#include "main.h"

namespace bot {
    struct Chassis {
        pros::MotorGroup *leftMotors;
        pros::MotorGroup *rightMotors;
        double rL, rR, rS;
        double lMult;
        void config(double rL, double rR, double rS, double lMult) {
            this->rL = rL;
            this->rR = rR;
            this->rS = rS;
            this->lMult = lMult;
        }
        Chassis(pros::MotorGroup *leftMotors, pros::MotorGroup *rightMotors) :leftMotors(leftMotors), rightMotors(rightMotors) {}
        Chassis() {
            Chassis(nullptr, nullptr);
        }

        double get_avg_position() {
            return (leftMotors->get_position() + rightMotors->get_position()) / 2;
        }

        void reset_position() {
            leftMotors->tare_position();
            rightMotors->tare_position();
        }

        void set_brake_mode(pros::motor_brake_mode_e_t mode) {
            leftMotors->set_brake_mode(mode);
            rightMotors->set_brake_mode(mode);
        }
    }chass;
}