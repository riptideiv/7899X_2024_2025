#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct Intake {
        pros::Motor *mtr;

        pros::Task *move_task = nullptr;

        double speedOverride = -127;
        int speedOverrideCnt = 0;
        int almostOverriding = 0;
        const int delayCycles = 6;
        const int speedOverrideCycles = 5;

        bool waitingOverride = 0;

        double speed = 0;
        double prevSpeed = 0;

        bool colorSort = false;
        bool colorSortRed = true;
        int colorCnt = 0;

        bool antiStuck = false;
        int stuckCnt = 0;

        void initialize(int port) {
            mtr = new pros::Motor(port);

            setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

            move_task = new pros::Task([](void *intk) {
                Intake *intake = (Intake *)intk;
                while (1) {
                    if (intake->almostOverriding > 0) std::cout << intake->almostOverriding << '\n';
                    pros::delay(15);

                    if (intake->almostOverriding > 0) {
                        intake->almostOverriding--;
                        intake->waitingOverride = 1;
                    } else if (intake->waitingOverride) {
                        intake->waitingOverride = 0;
                        intake->speedOverrideCnt = intake->speedOverrideCycles;
                    }

                    if (intake->stuckCnt >= 10) {
                        intake->speedOverrideCnt = 10;
                    }

                    if (intake->colorCnt >= 2) {
                        intake->almostOverriding = intake->delayCycles;
                    }

                    if (intake->speedOverrideCnt > 0) {
                        intake->speedOverrideCnt--;
                        intake->mtr->move(intake->speedOverride);
                        intake->stuckCnt = 0;
                        intake->colorCnt = 0;
                    } else {
                        intake->mtr->move(intake->speed);
                    }

                    if (intake->waitingOverride == 0 && intake->speedOverrideCnt == 0 && intake->colorSort && colorSortSensor.get_proximity() > 70) {
                        std::cout << colorSortSensor.get_hue() << std::endl;
                        if (
                            colorSortSensor.get_hue() < 20 &&
                            !intake->colorSortRed ||
                            colorSortSensor.get_hue() > 150 &&
                            intake->colorSortRed) {
                            intake->colorCnt++;
                            std::cout << "yes " << (intake->colorCnt) << std::endl;
                        } else {
                            intake->colorCnt = 0;
                        }
                    } else {
                        intake->colorCnt = 0;
                    }

                    if (intake->speedOverrideCnt == 0 && intake->antiStuck && intake->speed > 0 && intake->mtr->get_actual_velocity() / intake->speed < 0.1) {
                        intake->stuckCnt++;
                    }
                }
                }, this);
        }

        void set_colorsort(bool state, bool red) {
            colorSort = state;
            colorSortRed = red;
        }

        void set_speed(double spd) {
            speed = spd;
        }

        void setBrakeMode(pros::motor_brake_mode_e_t mode) {
            mtr->set_brake_mode(mode);
        }
    }   intake;
}