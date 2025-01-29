#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct Intake {
        pros::Motor *mtr;

        pros::Task *move_task = nullptr;

        bool doColorSort = false;
        bool colorSortRed = true;
        bool doAntiStuck = false;

        int speed = 0;

        bool throwAway = false;

        int reverseTime = 0;

        const int loopDelay = 3;

        void colorSort() {
            if (throwAway) {
                if (mtr->get_position() < 0) {
                    throwAway = 0;
                } else if (mtr->get_position() > 265) {
                    throwAway = 0;
                    reverseTime = 50;
                }
            } else {
                if (speed > 0 && colorSortSensor.get_proximity() > 70) {
                    // if (colorSortSensor.get_hue() < 30 && !colorSortRed ||
                        // colorSortSensor.get_hue() > 90 && colorSortRed) {
                    throwAway = true;
                    mtr->set_zero_position(0);
                    // }
                }
            }
        }

        void initialize(int port) {
            mtr = new pros::Motor(port);

            mtr->set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_COUNTS);
            setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

            mtr->set_zero_position(0);

            move_task = new pros::Task([](void *intk) {
                Intake *intake = (Intake *)intk;
                while (1) {
                    pros::delay(intake->loopDelay);
                    if (intake->doColorSort) {
                        intake->colorSort();
                    }
                    if (intake->reverseTime > 0) {
                        intake->reverseTime -= intake->loopDelay;
                        intake->mtr->move_voltage(-12000);
                    } else {
                        intake->mtr->move_voltage(120 * intake->speed);
                    }
                }
                }, this);
        }

        void set_colorsort(bool state, bool red) {
            doColorSort = state;
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