#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct BigArm {
        bool intakeSawRing = true; // intake saw ring after bigarm going to posHigh

        pros::Motor *mtr;
        pros::Rotation *rotation;
        int posLow, posMid, posHigh, posToScore, posScore;

        const double nkP = 1.65, nkI = 0, nkD = 0; // "normal" kP, kI, kD for resetting after some custom action
        double kP = nkP, kI = nkI, kD = nkD;

        int maxSpeed = 100;

        int move_target;
        pros::Task *move_task = nullptr;

        bool manual = false;

        void set_target(int target) {
            if (target == posHigh) {
                intakeSawRing = false;
            }
            manual = false;
            move_target = target;
            kP = nkP, kI = nkI, kD = nkD;
        }

        void toggleUp() {
            if (move_target == posScore || move_target == posToScore || manual) {
                set_target(posHigh);
                kP = 2.75;
            } else if (move_target == posHigh) {
                set_target(posLow);
                kP = 3;
            } else {
                set_target(posHigh);
                kP = 2.75;
            }
        }

        void set_load() {
            set_target(posHigh);
            kP = 2.75;
        }

        void reset() {
            set_target(posLow);
        }

        void manual_move(int spdPercent) {
            manual = true;
            mtr->move_voltage(spdPercent * 120);
        }

        void raise() {
            if (move_target == posToScore) {
                set_target(posScore);
                kP = 2.5;
            } else {
                set_target(posToScore);
                kP = 1.5;
            }
            // set_target(posScore);
            // kP = 2;
        }

        void cycle() {
            if (move_target == posLow) {
                set_target(posHigh);
            } else if (move_target == posHigh) {
                set_target(posToScore);
                kP = 1;
            } else if (move_target == posToScore) {
                set_target(posScore);
            } else if (move_target == posScore) {
                set_target(9333);
            } else {
                set_target(900);
            }
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

            move_target = posLow;

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

                    // if (abs(error) < 1000 && arm->mtr->get_actual_velocity() < 20) {
                    //     arm->manual = true;
                    //     arm->mtr->move_velocity(0);
                    // }

                    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
                        integral = 0;
                    }

                    derivative = error - prevError;
                    prevError = error;

                    double gravityTheta = (armPos - 15530) / 18000.0 * M_PI;
                    double kGravity = 700 * std::sin(gravityTheta);

                    double power = error * arm->kP + integral * arm->kI + derivative * arm->kD - kGravity;

                    if (power > arm->maxSpeed / 100.0 * 12000) power = arm->maxSpeed / 100.0 * 12000;
                    if (power < -arm->maxSpeed / 100.0 * 12000) power = -arm->maxSpeed / 100.0 * 12000;

                    arm->mtr->move_voltage(power);

                    // std::cout << "BigArm Error: " << error << std::endl;
                    pros::delay(20);
                }
                }, this);
        }

        void setMaxSpeed(int pct) {
            maxSpeed = pct;
        }

        void setBrakeMode(pros::motor_brake_mode_e_t mode) {
            mtr->set_brake_mode(mode);
        }
    } bigArm;
}