#pragma once

#include "main.h"

#include<iostream>

namespace bot {
    struct Intake {
        pros::Motor *upperMtr;
        pros::Motor *frontMtr;

        pros::Task *move_task = nullptr;

        bool doColorSort = true;
        bool colorSortRed = true;
        bool doAntiStuck = false;

        int upperSpd = 0;
        int frontSpd = 0;

        bool throwAway = false;

        int stuckFor = 0;

        int upReverseTime = 0;

        int frReverseTime = 0;

        int prevSpd = 0;
        int startUpTime = 0;

        const int loopDelay = 3;

        void colorSort() {
            if (throwAway && upReverseTime <= 0) {
                if (upperMtr->get_position() < -300) {
                    throwAway = 0;
                } else if (colorSortRed && upperMtr->get_position() > 435 || !colorSortRed && upperMtr->get_position() > 435) {
                    throwAway = 0;
                    upReverseTime = 110;
                    frReverseTime = 110;
                }
            } else {
                if (!throwAway && upperSpd > 0 && colorSortSensor.get_proximity() > 200 && bigArm.move_target != bigArm.posHigh) {
                    if ((colorSortSensor.get_hue() < 30 || colorSortSensor.get_hue() > 340) && !colorSortRed ||
                        (colorSortSensor.get_hue() > 120 && colorSortSensor.get_hue() < 270) && colorSortRed) {
                        throwAway = true;
                        upperMtr->set_zero_position(0);
                    }
                    // std::cout << "Yes it's running here\n";
                }
            }
        }

        void antiStuck() {
            if (upReverseTime <= 0 && upperSpd > 0 && upperMtr->get_actual_velocity() / upperSpd < 0.05) {
                stuckFor += loopDelay;
            } else {
                stuckFor = 0;
            }

            if (bot::bigArm.move_target != bot::bigArm.posHigh && stuckFor > 50) {
                upReverseTime = 150;
                frReverseTime = 250;
            }
        }

        void initialize(int upperPort, int frontPort) {
            doColorSort = true;
            colorSortRed = true;
            doAntiStuck = false;

            upperSpd = 0;

            throwAway = false;

            stuckFor = 0;

            upReverseTime = 0;
            frReverseTime = 0;

            prevSpd = 0;
            startUpTime = 0;

            colorSortSensor.set_led_pwm(100);
            colorSortSensor.set_integration_time(5);

            upperMtr = new pros::Motor(upperPort);
            frontMtr = new pros::Motor(frontPort);

            upperMtr->set_encoder_units(pros::motor_encoder_units_e::E_MOTOR_ENCODER_COUNTS);
            upperMtr->set_zero_position(0);

            setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

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
                    if (intake->prevSpd == 0 && intake->upperSpd > 0) {
                        intake->startUpTime = 200;
                    }
                    intake->prevSpd = intake->upperSpd;
                    if (intake->upReverseTime > 0) {
                        intake->startUpTime = 300;
                        intake->upReverseTime -= intake->loopDelay;
                        intake->upperMtr->move_voltage(-12000);
                    } else {
                        intake->upperMtr->move_voltage(120 * intake->upperSpd);
                    }
                    if (intake->frReverseTime > 0) {
                        intake->frReverseTime -= intake->loopDelay;
                        intake->frontMtr->move_voltage(-12000);
                    } else {
                        intake->frontMtr->move_voltage(120 * intake->frontSpd);
                    }
                }
                }, this);
        }

        void set_colorsort(bool state, bool red) {
            doColorSort = state;
            colorSortRed = red;
        }

        void set_upspeed(double spd) {
            upperSpd = spd;
        }

        void set_frspeed(double spd) {
            frontSpd = spd;
        }

        void set_speed(double spd) {
            set_upspeed(spd);
            set_frspeed(spd);
        }

        void setBrakeMode(pros::motor_brake_mode_e_t mode) {
            upperMtr->set_brake_mode(mode);
            frontMtr->set_brake_mode(mode);
        }
    } intake;

    //! spins the front intake
    void spin_frintk(double pct) {
        intake.set_frspeed(pct * 1.27);
    }

    //! spins the upper intake
    void spin_upintk(double pct) {
        intake.set_upspeed(pct * 1.27);
    }

    //! spins the intake
    void spin_intk(double pct) {
        spin_frintk(pct);
        spin_upintk(pct);
    }
}