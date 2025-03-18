#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct Intake {
        pros::Motor *mtr;
        // pros::Motor *frontMtr;

        pros::Task *move_task = nullptr;

        bool doColorSort = true;
        bool colorSortRed = true;
        bool doAntiStuck = false;

        int speed = 0;
        // int frontSpd = 0;

        bool throwAway = false;

        int stuckFor = 0;

        int revTime = 0;

        // int frReverseTime = 0;

        int prevSpd = 0;
        int startUpTime = 0;

        const int loopDelay = 5;

        void colorSort() {
            if (throwAway && revTime <= 0) {
                if (mtr->get_position() < -300) {
                    throwAway = 0;
                } else if (colorSortRed && mtr->get_position() > 287 || !colorSortRed && mtr->get_position() > 287) {
                    throwAway = 0;
                    revTime = 100;
                    // frReverseTime = 100;
                }
            } else {
                if (!throwAway && speed > 0 && colorSortSensor.get_proximity() > 200 && bigArm.move_target != bigArm.posHigh) {
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
            if (revTime <= 0 && speed > 0 && mtr->get_actual_velocity() / speed < 0.05) {
                stuckFor += loopDelay;
            } else {
                stuckFor = 0;
            }

            if (bot::bigArm.move_target != bot::bigArm.posHigh && stuckFor > 50) {
                revTime = 100;
                // frReverseTime = 100;
            }
        }

        void initialize(int upperPort, int frontPort) {
            doColorSort = true;
            colorSortRed = true;
            doAntiStuck = false;

            speed = 0;

            throwAway = false;

            stuckFor = 0;

            revTime = 0;
            // frReverseTime = 0;

            prevSpd = 0;
            startUpTime = 0;

            colorSortSensor.set_led_pwm(100);
            colorSortSensor.set_integration_time(5);

            mtr = new pros::Motor(upperPort, pros::MotorGear::blue, pros::MotorUnits::counts);
            // frontMtr = new pros::Motor(frontPort);

            mtr->set_zero_position(0);

            mtr->set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            // frontMtr->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

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
                    if (intake->revTime > 0) {
                        intake->startUpTime = 300;
                        intake->revTime -= intake->loopDelay;
                        intake->mtr->move_voltage(-12000);
                    } else {
                        if (bigArm.move_target != bigArm.posHigh)
                            intake->mtr->move_voltage(110 * intake->speed);
                        else
                            intake->mtr->move_voltage(120 * intake->speed);
                    }
                    // if (intake->frReverseTime > 0) {
                    //     intake->frReverseTime -= intake->loopDelay;
                    //     intake->frontMtr->move_voltage(-12000);
                    // } else {
                    //     if (bigArm.move_target != bigArm.posHigh)
                    //         intake->frontMtr->move_voltage(110 * intake->frontSpd);
                    //     else
                    //         intake->frontMtr->move_voltage(120 * intake->frontSpd);
                    // }
                }
                }, this);
        }

        void set_colorsort(bool state, bool red) {
            doColorSort = state;
            colorSortRed = red;
        }

        // void set_upspeed(double spd) {
        //     upperSpd = spd;
        // }

        // void set_frspeed(double spd) {
        //     frontSpd = spd;
        // }

        void set_speed(double spd) {
            // set_upspeed(spd);
            // set_frspeed(spd);
            speed = spd;
        }

        void setBrakeMode(pros::motor_brake_mode_e_t mode) {
            mtr->set_brake_mode(mode);
            // frontMtr->set_brake_mode(mode);
        }
    } intake;

    // //! spins the front intake
    // void spin_frintk(double pct) {
    //     intake.set_frspeed(pct * 1.27);
    // }

    // //! spins the upper intake
    // void spin_upintk(double pct) {
    //     intake.set_upspeed(pct * 1.27);
    // }

    //! spins the intake
    void spin_intk(double pct) {
        intake.set_speed(pct * 1.27);
    }
}