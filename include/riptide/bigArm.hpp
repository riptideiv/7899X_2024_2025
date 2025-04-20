#pragma once

#include "main.h"

#include<iostream>

#define posHigh 10600
#define posMid 10600
#define posLow 7690
#define posToScore 15720
#define posScore 23774
#define posUntip 30800

namespace bot {
    struct BigArm {
        bool intakeSawRing = true; // intake saw ring after bigarm going to posHigh

        pros::Motor *mtr;
        pros::Rotation *rotation;

        const double nkP = 1.4, nkI = 0, nkD = 0; // "normal" kP, kI, kD for resetting after some custom action
        double kP = nkP, kI = nkI, kD = nkD;

        int maxSpeed = 100;

        int move_target;
        pros::Task *move_task = nullptr;

        bool manual = false;

        void set_target(int target) {
            manual = false;
            move_target = target;
            kP = nkP, kI = nkI, kD = nkD;
            switch (target) {
            case posHigh:
                intakeSawRing = false;
                kP = 1.4;
                break;
            case posLow:
                kP = 4;
                break;
            }
        }

        void toggleUp() {
            if (rotation->get_position() > posToScore - 500) {
                set_target(posHigh);
            } else if (move_target == posHigh) {
                set_target(posLow);
            } else {
                set_target(posHigh);
            }
        }

        void set_load() {
            set_target(posHigh);
        }

        void reset() {
            set_target(posLow);
        }

        void manual_move(int spdPercent) {
            if (!manual && move_target == posUntip && spdPercent > 0) {
                return;
            }
            manual = true;
            mtr->move_voltage(spdPercent * 120);
        }

        void raise() {
            if (move_target == posToScore || move_target > posScore) {
                set_target(posScore);
            } else {
                set_target(posToScore);
            }
            // set_target(posScore);
        }

        void cycle() {
            if (move_target == posLow) {
                set_target(posHigh);
            } else if (move_target == posHigh) {
                set_target(posToScore);
            } else if (move_target == posToScore) {
                set_target(posScore);
            } else if (move_target == posScore) {
                set_target(posScore + 9000);
            }
        }

        void initialize(int port, int rotationPort) {
            mtr = new pros::Motor(port);

            rotation = new pros::Rotation(rotationPort);
            rotation->reset();

            move_target = posLow;

            setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

            move_task = new pros::Task([](void *bigArm) {
                int error, prevError = 0, derivative, integral = 0;
                BigArm *arm = (BigArm *)bigArm;
                arm->rotation->get_position();
                while (true) {
                    if (arm->rotation->get_position() > 30000 && arm->manual) {
                        arm->set_target(posUntip);
                    } else if (arm->manual) {
                        pros::delay(50);
                        continue;
                    }

                    int armPos = arm->rotation->get_position();

                    double gravityTheta = (armPos - 18193) / 18000.0 * M_PI;
                    double kGravity = 700 * std::sin(gravityTheta);

                    error = arm->move_target - armPos;

                    if ((error > 0 && prevError < 0) || (error < 0 && prevError > 0)) {
                        integral = 0;
                    }

                    derivative = error - prevError;
                    prevError = error;

                    double power = error * arm->kP + integral * arm->kI + derivative * arm->kD - kGravity;

                    if (power > arm->maxSpeed / 100.0 * 12000) power = arm->maxSpeed / 100.0 * 12000;
                    if (power < -arm->maxSpeed / 100.0 * 12000) power = -arm->maxSpeed / 100.0 * 12000;
                    if (armPos >= posScore) {
                        if (power < -arm->maxSpeed / 100.0 * 9000) power = -arm->maxSpeed / 100.0 * 9000;
                    }

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