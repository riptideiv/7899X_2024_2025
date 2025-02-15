#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct Intake {
        pros::Motor *mtr;

        pros::Task *move_task = nullptr;

        bool doColorSort = true;
        bool colorSortRed = true;
        bool doAntiStuck = false;

        int speed = 0;

        bool throwAway = false;

        int stuckFor = 0;

        int reverseTime = 0;

        int prevSpd = 0;
        int startUpTime = 0;

        const int loopDelay = 3;

        void colorSort() {
            if (throwAway && reverseTime <= 0) {
                if (mtr->get_position() < 0) {
                    throwAway = 0;
                } else if (colorSortRed && mtr->get_position() > 427 || !colorSortRed && mtr->get_position() > 427) {
                    throwAway = 0;
                    reverseTime = 75;
                }
            } else {
                if (!throwAway && speed > 0 && colorSortSensor.get_proximity() > 200) {
                    if ((colorSortSensor.get_hue() < 30 || colorSortSensor.get_hue() > 340) && !colorSortRed ||
                        (colorSortSensor.get_hue() > 120 && colorSortSensor.get_hue() < 270) && colorSortRed) {
                        throwAway = true;
                        mtr->set_zero_position(0);
                    }
                    // std::cout << "Yes it's running here\n";
                }
            }
        }

        void antiStuck() {
            if (reverseTime <= 0 && speed > 0 && mtr->get_actual_velocity() / speed < 0.10) {
                stuckFor += loopDelay;
            } else {
                stuckFor = 0;
            }

            if (bot::bigArm.move_target != bot::bigArm.posHigh && stuckFor > 50) {
                reverseTime = 100;
            }
        }

        void initialize(int port) {
            doColorSort = true;
            colorSortRed = true;
            doAntiStuck = false;

            speed = 0;

            throwAway = false;

            stuckFor = 0;

            reverseTime = 0;

            prevSpd = 0;
            startUpTime = 0;

            colorSortSensor.set_led_pwm(100);
            colorSortSensor.set_integration_time(5);

            mtr = new pros::Motor(port);

            mtr->set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_COUNTS);
            setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

            mtr->set_zero_position(0);

            move_task = new pros::Task([](void *intk) {
                Intake *intake = (Intake *)intk;
                while (1) {
                    pros::delay(intake->loopDelay);
                    if (intake->startUpTime <= 0) {
                        if (intake->doColorSort) {
                            intake->colorSort();
                        }
                        if (intake->doAntiStuck) {
                            intake->antiStuck();
                        }
                    } else {
                        intake->startUpTime -= intake->loopDelay;
                    }
                    if (intake->prevSpd == 0 && intake->speed > 0) {
                        intake->startUpTime = 200;
                    }
                    intake->prevSpd = intake->speed;
                    if (intake->reverseTime > 0) {
                        intake->startUpTime = 200;
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