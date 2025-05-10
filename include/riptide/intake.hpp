#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct Intake {
        pros::Motor *mtr = nullptr;
        // pros::Motor *frontMtr = nullptr;

        pros::Task *move_task = nullptr;

        bool doColorSort;
        bool colorSortRed;
        bool doAntiStuck;
        bool confirmThrow;

        bool stopNextRing;

        int speed;
        // int frontSpd;

        bool throwAway;

        int stuckFor;

        int revTime;

        // int frReverseTime;

        int prevSpd;
        int startUpTime;

        const int loopDelay = 3;

        void colorSort() {
            if (throwAway && revTime <= 0) { // 69
                if (colorSortRed && mtr->get_position() > 72 || !colorSortRed && mtr->get_position() > 72) {
                    throwAway = false;
                    confirmThrow = false;
                    revTime = 200;
                    // frReverseTime = 100;
                } else if (mtr->get_position() < -300) {
                    throwAway = false;
                    confirmThrow = false;
                }
            } else {
                if (speed >= 0) {
                    if (!confirmThrow && revTime <= 0 && colorSortSensor.get_proximity() > 200) {
                        if ((colorSortSensor.get_hue() < 30 || colorSortSensor.get_hue() > 340) && !colorSortRed ||
                            (colorSortSensor.get_hue() > 120 && colorSortSensor.get_hue() < 270) && colorSortRed) {
                            confirmThrow = true;
                            mtr->set_zero_position(0);
                        }
                    }
                }

                if (mtr->get_position() < -300) {
                    confirmThrow = false;
                }

                if (mtr->get_position() > 5 && !throwAway && speed > 0 && intakeDist.get() < 65 && bigArm.move_target != posHigh) {
                    if (confirmThrow) {
                        confirmThrow = false;
                        throwAway = true;
                        mtr->set_zero_position(0);
                    }
                    // std::cout << "Yes it's running here\n";
                }
            }
        }

        void antiStuck() {
            if (revTime <= 0 && speed > 0 && mtr->get_actual_velocity() / speed < 0.1) {
                stuckFor += loopDelay;
            } else {
                stuckFor = 0;
            }

            if (bot::bigArm.move_target == posHigh) {
                if (!bot::bigArm.intakeSawRing && intakeDist.get() < 65) {
                    bot::bigArm.intakeSawRing = true;
                    stuckFor = 0;
                }
                if (!bot::bigArm.intakeSawRing && stuckFor > 50) {
                    revTime = 100;
                }
            } else if (stuckFor > 50) {
                revTime = 100;
                // frReverseTime = 100;
            }
        }

        void initialize(int upperPort, int frontPort) {
            doColorSort = true;
            colorSortRed = true;
            doAntiStuck = false;
            confirmThrow = false;

            stopNextRing = false;

            speed = 0;
            // frontSpd = 0;

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

                    // give startup time when intake starts
                    if (intake->prevSpd == 0 && intake->speed > 0) {
                        intake->startUpTime = 200;
                    }

                    // record previous speed to check for changes
                    intake->prevSpd = intake->speed;

                    // give startup time if the intake is auto-reversing
                    if (intake->revTime > 0) {
                        intake->startUpTime = 300;
                        intake->revTime -= intake->loopDelay;
                        intake->mtr->move_voltage(-12000);
                    } else {
                        // hold ring
                        if (intake->stopNextRing) {
                            if (intake->revTime <= 0 && intake->speed > 0 && colorSortSensor.get_proximity() > 200) {
                                intake->set_speed(0);
                                intake->stopNextRing = false;
                                intake->stuckFor = 0;
                            } else {
                                intake->mtr->move_voltage(70 * intake->speed);
                            }
                        } else // normal operation
                            intake->mtr->move_voltage(120 * intake->speed);
                    }
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