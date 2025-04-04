#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace blue {

    void minusNormalEnding() {
        // get corner
        drWait(0.5, 0.5, -3);
        turn2pt(-35.4355, 5.62254, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(-35.4355, 5.62254, 1000, { .maxSpeed = 90, .minSpeed = 15, .earlyExitRange = 15 });
        mv2pt(-35.4355, 5.62254, 1000, { .maxSpeed = 20, .minSpeed = 19, .earlyExitRange = 3 });
        bigArm.reset();
        bigArm.raise();
        bigArm.raise();
        turn2hd(-45, 700, { .minSpeed = 15, .earlyExitRange = 1 });

        // // bigArm.raise();
        // // spin_intk(100);
        // // toggleGoalClamp();
        // // pros::delay(500);

        intake.doAntiStuck = false;

        drive_chass(60, 60);
        pros::delay(500);
        bigArm.set_target(16000);
        bigArm.kP = 2.5;
        drive_chass(60, 60);
        pros::delay(500);

        bigArm.reset();
        bigArm.raise();
        drWait(0.4, 0.4, -3);
        // drive_chass(0, 0); //debug stop

        // get mid stack
        mv2pt(-31.4445, -0.617452, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 15, .earlyExitRange = 2 });
        intake.stuckFor = 0;
        intake.doAntiStuck = true;
        turn2pt(23, 0.5, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-6, 0.5, 1000, { .maxSpeed = 80, .minSpeed = 20, .earlyExitRange = 3 });
        toggleIntakeLift();
        turn2pt(23, 0.5, 500, { .minSpeed = 15, .earlyExitRange = 1.5 });
        mv2pt(23, 0.5, 1000, { .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 13 });
        toggleIntakeLift();
        mv2pt(23, 0.5, 1000, { .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 8 });

        // touch bar
        drWait(0.2, 0.2, -0.1);
        turn2pt(16.8601, -30.1958, 1000, { .minSpeed = 20, .earlyExitRange = 1.5 });
        mv2pt(16.8601, -30.1958, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 15 });
    }

    void minusRingsReused() {
        // get contested rings
        turn2pt(-18.4265, -50.5378, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(-18.4265, -50.5378, 1000, { .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 24 });

        swing2pt(-29.8293, -44.2, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(-29.8293, -44.2, 1000, { .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 13 });

        swing2pt(-38.4916, -42.9691, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-38.4916, -42.9691, 1000, { .maxSpeed = 80, .minSpeed = 35, .earlyExitRange = 6 });

        // get norush ring
        drWait(0.6, 0, -1);
        swing2pt(-6.91345, -32, lemlib::DriveSide::RIGHT, 1000, { .forwards = false, .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1.5 });
        mv2pt(-6.91345, -32, 1000, { .forwards = false, .minSpeed = 35, .earlyExitRange = 3 });

        turn2pt(-30.5642, -25.821, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(-30.5642, -25.821, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 8 });
        pros::delay(100);
    }

    void minus5_1() {
        // alli stake & mogo
        rightSideAlli();
        rightSideGoal();
        minusRingsReused();
        minusNormalEnding();
    }

    void minus6() {
        // get mogo
        rightSideGoal();
        minusRingsReused();
        minusNormalEnding();
    }

    void minus3_2_1() {

    }

    void minus5clear() {

    }

    void plus5begin() {
        bigArm.reset();

        // get mogo
        swing2pt(6.7195, -29.1135, lemlib::DriveSide::LEFT, 1000, { .forwards = false, .maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 2 });
        mv2pt(6.7195, -29.1135, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 15 });
        toggleFrontLeftArm();
        mv2pt(6.7195, -29.1135, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 5 });
        toggleFrontLeftArm();
        toggleGoalClamp();
        mv2pt(6.7195, -29.1135, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 4 });
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
        mv2pt(3.42381, -20.8111, 1000, { .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(-11.16107, -55.789, 1000, { .maxSpeed = 70, .minSpeed = 20, .earlyExitRange = 40 });
        turn2pt(-11.16107, -55.789, 1000, { .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 2 });
        spin_intk(0);
        mv2pt(-11.16107, -55.789, 1000, { .maxSpeed = 65, .minSpeed = 20, .earlyExitRange = 20 });
        mv2pt(-11.16107, -55.789, 1000, { .maxSpeed = 25, .minSpeed = 20, .earlyExitRange = 11 });
        // first tower blue ring
        toggleFrontRightArm();
        pros::delay(150);
        // second tower blue ring
        drWait(0.3, 0.3, -1);
        turn2hd(-130.043, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 2 });
        toggleFrontLeftArm();
        pros::delay(200);
        drWait(0.3, 0.3, -1);

        // pull out
        mv2pt(11.9671, -15.247, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        bigArm.reset();
        bigArm.raise();
        pros::delay(250);
        turn2hd(178, 1000, { .maxSpeed = 50, .minSpeed = 23, .earlyExitRange = 2 });
        toggleFrontLeftArm();
        toggleFrontRightArm();
        pros::delay(250);

        // get 3 in a row
        turn2pt(8.5, -30.9074, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        spin_intk(100);
        mv2pt(9.5, -30.9074, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 2 });
        swing2pt(18.8061, -28.6465, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 25, .earlyExitRange = 2 });
        mv2pt(18.8061, -28.6465, 1000, { .minSpeed = 20, .earlyExitRange = 6 });
        swing2pt(37.3155, -26.35, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 25, .earlyExitRange = 2 });
        mv2pt(37.3155, -26.35, 1000, { .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 2 });

        // get corner
        drWait(0.3, 0.3, -1);
        turn2pt(35.2786, -2.414121, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        mv2pt(35.2786, -2.414121, 1000, { .maxSpeed = 80, .minSpeed = 20, .earlyExitRange = 5 });
        bigArm.reset();
        bigArm.raise();
        bigArm.raise();
        mv2pt(35.2786, -2.414121, 1000, { .maxSpeed = 80, .minSpeed = 20, .earlyExitRange = 2 });
        turn2hd(45, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        pros::delay(500);
        mv2pt(46.2442, 11.1635, 1000, { .minSpeed = 20, .earlyExitRange = 4 });
        bigArm.set_target(16000);
        bigArm.kP = 2.5;
        spin_intk(100);
        mv2pt(46.2442, 11.1635, 750, { .maxSpeed = 60, .minSpeed = 50, .earlyExitRange = 0.5 });
        drive_chass(30, 30);
        pros::delay(150);
    }

    void plus5_cornerprep() {
        plus5begin();
        drWait(0.3, 0.3, -8.33);
        toggleFrontLeftArm();
        pros::delay(150);
        drWait(0.5, 0.5, 2);
        turn2hd(180, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 127, .earlyExitRange = 50 });
        turn2hd(180, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 5 });
        toggleFrontLeftArm();
    }

    void plus5_rushprep() {
        plus5begin();
        // ending position
        mv2pt(38.098, -3.43366, 1000, { .forwards = false, .minSpeed = 25, .earlyExitRange = 2 });
        turn2hd(-90, 1000, { .minSpeed = 30, .earlyExitRange = 20 });
        toggleGoalClamp();
        turn2hd(-90, 250);
        bigArm.reset();
        drWait(0, 0.6, 2);
        turn2hd(0, 1000);
    }

    void plusRush2_1_1() {

    }
}