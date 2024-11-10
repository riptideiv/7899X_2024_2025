#pragma once

#include "main.h"

namespace bot {
    struct Chassis {
        pros::MotorGroup *leftMotors;
        pros::MotorGroup *rightMotors;
        double rL, rR, rS;
        void config(double rL, double rR, double rS) {
            this->rL = rL;
            this->rR = rR;
            this->rS = rS;
        }
        Chassis(pros::MotorGroup *leftMotors, pros::MotorGroup *rightMotors) :leftMotors(leftMotors), rightMotors(rightMotors) {}
        Chassis() {
            Chassis(nullptr, nullptr);
        }
    }chass;
}