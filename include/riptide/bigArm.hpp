#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct BigArm {
        pros::Motor *mtr;
        pros::Rotation *rotation;
        int posLow, posMid, posHigh, posToScore, posScore;

        const double nkP = 2, nkI = 0, nkD = 0; // "normal" kP, kI, kD for resetting after some custom action
        double kP = nkP, kI = nkI, kD = nkD;

        int move_target;
        pros::Task *move_task = nullptr;

        bool manual = false;

        void set_target(int target) {
            manual = false;
            move_target = target;
            kP = nkP, kI = nkI, kD = nkD;
        }

        void toggleUp() {
            if (move_target != posHigh || manual) {
                set_target(posHigh);
            } else {
                set_target(posLow);
            }
        }

        void reset() {
            set_target(posLow);
        }

        void manual_move(int spdPercent) {
            manual = true;
            mtr->move_voltage(spdPercent * 120);
        }

        void raise() {
            // if (move_target == posToScore) {
            //     set_target(posScore);
            //     kP = 2.5;
            // } else {
            //     set_target(posToScore);
            // }
            set_target(posScore);
        }

        void initialize(int port, int rotationPort, int posLow, int posMid, int posHigh, int posToScore, int posScore) {
            mtr = new pros::Motor(port);

            rotation = new pros::Rotation(rotationPort);
            rotation->reset();

            this->posLow = posLow;
            this->posMid = posMid;
            this->posHigh = posHigh;
            this->posToScore = posToScore;
            this->posScore = posScore;

            move_target = posMid;

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

                    error = arm->move_target - armPos;

                    if (abs(error) < 1000) integral += error;
                    else integral = 0;

                    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
                        integral = 0;
                    }

                    derivative = error - prevError;
                    prevError = error;

                    double power = error * arm->kP + integral * arm->kI + derivative * arm->kD;

                    arm->mtr->move_voltage(power);

                    // std::cout << "BigArm Error: " << error << std::endl;
                    pros::delay(50);
                }
                }, this);
        }

        void setBrakeMode(pros::motor_brake_mode_e_t mode) {
            mtr->set_brake_mode(mode);
        }
    } bigArm;
}