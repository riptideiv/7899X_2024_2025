#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace red {
    void minusNormalEnding() {
        // get corner
        drWait(0.5, 0.5, -3);
        turn2pt(38.9573, 0.5, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(38.9573, 0.5, 1000, { .maxSpeed = 90, .minSpeed = 15, .earlyExitRange = 15 });
        mv2pt(38.9573, 0.5, 1000, { .maxSpeed = 20, .minSpeed = 19, .earlyExitRange = 3 });
        bigArm.reset();
        bigArm.raise();
        bigArm.raise();
        turn2hd(45, 700, { .minSpeed = 15, .earlyExitRange = 1 });

        mv2pt(45.0707, 7.82987, 1000, { .minSpeed = 20, .earlyExitRange = 8 });
        bigArm.set_target(16000);
        bigArm.kP = 2.5;
        spin_intk(100);
        mv2pt(45.0707, 7.82987, 1000, { .minSpeed = 90, .earlyExitRange = 1 });
        drive_chass(50, 50);
        pros::delay(500);

        pros::delay(5000);
    }

    void minusRingsReused() {
        // get contested rings
        turn2pt(27, -54.3951, 1000, { .direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(27, -54.3951, 1000, { .maxSpeed = 70, .minSpeed = 25, .earlyExitRange = 15.5 });

        swing2pt(33, -49.5, lemlib::DriveSide::LEFT, 1000, { .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(33, -49.5, 1000, { .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 4 });

        swing2pt(47, -48, lemlib::DriveSide::LEFT, 1000, { .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(47, -48, 1000, { .maxSpeed = 80, .minSpeed = 35, .earlyExitRange = 1 });

        // get norush ring
        drWait(0, 0.6, -1);
        swing2pt(17.0686, -39.4609, lemlib::DriveSide::LEFT, 1000, { .forwards = false, .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(17.0686, -39.4609, 1000, { .forwards = false, .minSpeed = 35, .earlyExitRange = 3 });

        turn2pt(36.7946, -29, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(36.7946, -29, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 8 });
        pros::delay(100);
    }

    void minus5_1() {
        leftSideAlli();
        leftSideGoal();
        minusRingsReused();
        minusNormalEnding();
    }

    void minus6() {
        leftSideGoal();
        minusRingsReused();
        minusNormalEnding();
    }

    void minus5clear() {

    }

    void minus3_2_1() {
        leftSideAlli();
        leftSideGoal();
        minusRingsReused();

        spin_intk(0);

        // get mid stack
        turn2pt(-14.6627, -7.62606, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        spin_intk(100);
        mv2pt(-14.6627, -7.62606, 1000, { .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 24 });
        toggleGoalClamp();
        toggleIntakeLift();
        pros::delay(50);

        spin_intk(80);
        pros::Task stopIntake([=] {
            while (1) {
                if (colorSortSensor.get_proximity() > 55) {
                    spin_intk(0);
                    break;
                }
                pros::Task::delay(3);
            }
            });

        mv2pt(-14.6627, -2.62606, 1000, { .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 2 });

        // get mogo
        mv2pt(-24.607, -5.72875, 1000, { .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 1 });
        toggleIntakeLift();
        turn2pt(-42.5052, -30.3413, 1000, { .forwards = false,.minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-42.5052, -30.3413, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 15 });
        mv2pt(-42.5052, -30.3413, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 5 });
        toggleGoalClamp();
        mv2pt(-42.5052, -30.3413, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 4 });
        spin_intk(100);

        // last ring
        turn2pt(-64.5066, -34.4053, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-64.5066, -34.4053, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 5 });
        /*
        mid stack
        x,y,theta: -14.6627, -2.62606, -412.204, lWall: 2147483647, rWall: 2147483647, mogoDist: 2147483647

        move to point to aim toward mogo
        x,y,theta: -24.607, -5.72875, -332.313, lWall: 2147483647, rWall: 2147483647, mogoDist: 2147483647

        get mogo
        x,y,theta: -37.5052, -30.3413, -332.701, lWall: 2147483647, rWall: 2147483647, mogoDist: 2147483647

        last ring
        x,y,theta: -64.5066, -29.4053, -439.629, lWall: 2147483647, rWall: 2147483647, mogoDist: 2147483647

        tower
        x,y,theta: -26.2878, -35.7065, -442.056, lWall: 2147483647, rWall: 2147483647, mogoDist: 2147483647
        */
    }

    void plus5begin() {
        bigArm.reset();

        // get mogo
        swing2pt(-6.29835, -27.7441, lemlib::DriveSide::RIGHT, 1000, { .forwards = false, .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 2 });
        mv2pt(-6.29835, -27.7441, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 15 });
        toggleFrontLeftArm();
        mv2pt(-6.29835, -27.7441, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 5 });
        toggleFrontLeftArm();
        toggleGoalClamp();
        mv2pt(-6.29835, -27.7441, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 4 });
        spin_intk(100);

        pros::Task stopIntake2([=] {
            intake.mtr->set_zero_position(0);
            while (1) {
                if (intake.mtr->get_position() > 510) {
                    pros::Task::delay(10);
                    spin_intk(0);
                    break;
                }
                pros::Task::delay(3);
            }
            });

        // get under tower
        mv2pt(-4.77927, -20.3855, 1000, { .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(9.65959, -51.3704, 1000, { .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 40 });
        turn2pt(9.65959, -51.3704, 1000, { .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 2 });
        spin_intk(0);
        mv2pt(9.65959, -51.3704, 1000, { .maxSpeed = 65, .minSpeed = 20, .earlyExitRange = 20 });
        mv2pt(9.65959, -51.3704, 1000, { .maxSpeed = 25, .minSpeed = 20, .earlyExitRange = 10.5 });
        // first tower blue ring
        toggleFrontLeftArm();
        pros::delay(200);
        // second tower blue ring
        turn2hd(133.675, 1000, { .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 2 });
        toggleFrontRightArm();
        pros::delay(250);

        // pull out
        mv2pt(-18.1149, -9.46125, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        bigArm.reset();
        bigArm.raise();
        pros::delay(250);
        turn2hd(162, 1000, { .maxSpeed = 50, .minSpeed = 35, .earlyExitRange = 2 });
        toggleFrontLeftArm();
        toggleFrontRightArm();
        pros::delay(250);

        // get 3 in a row
        turn2pt(-3.14406, -24.5474, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        spin_intk(100);
        mv2pt(-3.14406, -24.5474, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 5 });
        swing2hd(180, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 20, .earlyExitRange = 10 });
        spin_intk(0);
        swing2hd(180, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(-33.6566, -25.7769, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        drWait(0.4, 0.4, 2);
        spin_intk(100);
        mv2pt(-33.6566, -25.7769, 1000, { .maxSpeed = 50, .minSpeed = 25, .earlyExitRange = 3 });

        // get corner
        turn2pt(-33.4264, -3.611046, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-33.4264, -3.611046, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 5 });
        bigArm.reset();
        bigArm.raise();
        bigArm.raise();
        mv2pt(-33.4264, -3.611046, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 1 });
        turn2hd(-45, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        pros::delay(650);
        mv2pt(-45.609, 5.89776, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-46.9273, 7.29799, 750, { .maxSpeed = 60, .minSpeed = 50, .earlyExitRange = 0.5 });
        drive_chass(30, 30);
        pros::delay(250);

    }

    void plus5_cornerprep() {
        plus5begin();

        mv2pt(-41.045, 1.36698, 1000, { .forwards = false, .minSpeed = 25, .earlyExitRange = 1 });
        toggleFrontRightArm();
        pros::delay(150);
        drWait(0.5, 0.5, 2);
        turn2hd(180, 1000, { .direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .minSpeed = 127, .earlyExitRange = 50 });
        turn2hd(180, 1000, { .direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 5 });
        toggleFrontRightArm();
    }

    void plus5_rushprep() {
        plus5begin();
        // ending position
        mv2pt(-39.3694, -0.386489, 1000, { .forwards = false, .minSpeed = 25, .earlyExitRange = 2 });
        turn2hd(90, 1000, { .minSpeed = 30, .earlyExitRange = 20 });
        toggleGoalClamp();
        turn2hd(90, 250);
        drWait(0.6, 0, 2);
        turn2hd(0, 1000);
    }

    void plusRush3_1() {

    }
}