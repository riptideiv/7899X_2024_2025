#pragma once

#include "riptide.hpp"

#include<iostream>

namespace bot {
    struct BigArm {
        const double kP = 2.5, kI = 0, kD = 3;

        pros::Motor *left_mtr, *right_mtr;
        pros::Rotation *rotation;
        int posLow, posMid, posHigh;

        int move_target;
        pros::Task *move_task = nullptr;

        bool manual = false;

        void set_target(int target) {
            manual = false;
            move_target = target;
        }

        void toggleUp() {
            set_target(posHigh);
        }

        void reset() {
            set_target(posLow);
        }

        void manual_move(int spdPercent) {
            manual = true;
            left_mtr->move_voltage(spdPercent * 120);
            right_mtr->move_voltage(spdPercent * 120);
        }

        void initialize(int leftPort, int rightPort, int rotationPort, int posLow, int posMid, int posHigh) {
            left_mtr = new pros::Motor(leftPort);
            right_mtr = new pros::Motor(rightPort);

            rotation = new pros::Rotation(rotationPort);
            rotation->reset();

            this->posLow = posLow;
            this->posMid = posMid;
            this->posHigh = posHigh;

            move_target = posHigh;

            setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

            move_task = new pros::Task([](void *bigArm) {
                int error, prevError = 0, derivative, integral = 0;
                BigArm *arm = (BigArm *)bigArm;
                arm->rotation->get_position();
                while (true) {
                    if (arm->manual) {
                        pros::delay(50);
                        continue;
                    }

                    int armPos = arm->rotation->get_position();
                    if (armPos > 20000) armPos -= 36000;

                    error = arm->move_target - armPos;

                    if (abs(error) < 1000) integral += error;
                    else integral = 0;

                    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
                        integral = 0;
                    }

                    derivative = error - prevError;
                    prevError = error;

                    double power = error * arm->kP + integral * arm->kI + derivative * arm->kD;

                    arm->left_mtr->move_voltage(power);
                    arm->right_mtr->move_voltage(power);

                    // std::cout << "BigArm Error: " << error << std::endl;
                    pros::delay(50);
                }
                }, this);
        }

        void setBrakeMode(pros::motor_brake_mode_e_t mode) {
            left_mtr->set_brake_mode(mode);
            right_mtr->set_brake_mode(mode);
        }
    } bigArm;
}