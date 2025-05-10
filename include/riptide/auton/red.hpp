#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

using std::cout, std::endl;

namespace red {
    void neg_rrush() {
        toggleFrontLeftArm();
        spin_intk(100);
        mv2pt(-8.5, 30.7458, 1000, { .minSpeed = 1, .earlyExitRange = 7 });
        cout << "chassVelo: " << bot::getChassVelo() << endl;

        mv2pt(-11.3, 42.8146, 470);
        intake.stopNextRing = true;

        mv2pt(-4.5, 11.893, 1000, { .forwards = false, .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontLeftArm();
        pros::delay(250);

        turn2pt(4.57842, 22.25, 670, { .forwards = false });
        mv2pt(4.57842, 22.25, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 5 });
        mv2pt(4.57842, 22.25, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2 });
        toggleGoalClamp();
        pros::delay(250);

        intake.stopNextRing = false;
        spin_intk(-15);
        turn2pt(-22, 23, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        spin_intk(100);
        mv2pt(-22, 23, 1400, { .maxSpeed = 50 });

        // corner
        turn2pt(-23.1772, -6, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        mv2pt(-23.1772, -6, 1000, { .minSpeed = 10, .earlyExitRange = 1.5 });
        turn2pt(-33.1636, -15.5, 370);
        mv2pt(-33.1636, -15.5, 700, { .maxSpeed = 45 });

        mv2pt(-22.1772, -8, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        mv2pt(-33.1636, -15.5, 700, { .maxSpeed = 45 });

        mv2pt(-22.1772, -8, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        mv2pt(-33.1636, -15.5, 700, { .maxSpeed = 45 });

        // alliance stake
        mv2pt(-12.9397, -2.69194, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        turn2pt(14.7008, -12.2876, 1000);
        bigArm.set_load();
        mv2pt(14.7008, -12.2876, 1000);
    }

    void neg6_1() {
        leftAlli_Mogo();
        toggleFrontRightArm();
        pros::delay(250);
        toggleFrontRightArm();

        // get 3 rings
        turn2pt(17, -37.0892, 600);
        spin_intk(100);
        mv2pt(17, -37.0892, 1000, { .minSpeed = 1, .earlyExitRange = 1 });
        swing2pt(36.0941, -38, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        mv2pt(36.0941, -38, 1000, { .maxSpeed = 90, .minSpeed = 1, .earlyExitRange = 3.5 });
        conn2hd(15, 1000, { .minSpeed = 20, .earlyExitRange = 4 });
        mv2pt(28, -17.2199, 1000, { .minSpeed = 1, .earlyExitRange = 2 });

        // get corner
        turn2pt(39, 11.9988, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        mv2pt(39, 11.9988, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        swing2hd(45, lemlib::DriveSide::RIGHT, 500, { .minSpeed = 40, .earlyExitRange = 3 });
        drive_chass(40, 40);
        pros::delay(200);
        cornerMacro();

        // get mid ring
        conn2pt(-9.88808, 6.41539, 1000);
        toggleIntakeLift();
        mv2pt(-9.88808, 6.41539, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        turn2pt(-16.2991, 6.41539, 250);
        mv2pt(-16.2991, 6.41539, 1000, { .maxSpeed = 16, .minSpeed = 13, .earlyExitRange = 1 });
        drWait(0.3, 0.3, -2);
        toggleIntakeLift();

        // touch bar
        turn2pt(-20.1899, -7.64277, 500);
        mv2pt(-20.1899, -7.64277, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
    }

    void pos_grush() { // LB goal rush
        // goal rush & tip goal
        bigArm.raise();
        ms2pt(17.7307 - 18.25 * sin(17.0 / 180 * M_PI), 51.0079 - 14.5 * cos(15.0 * 180 * M_PI), 1000, { .minSpeed = 1,.earlyExitRange = 13 });
        bigArm.setMaxSpeed(60);
        bigArm.set_target(31000);
        ms2pt(17.7307 - 18.25 * sin(17.0 / 180 * M_PI), 51.0079 - 14.5 * cos(15.0 * 180 * M_PI), 1000, {}, true);
        while (bigArm.rotation->get_position() < 26300) {
            pros::delay(3);
        }
        straight_chass[MOGO]->cancelMotion();
        pros::delay(50);
        drWait(0.4, 0.4, -1);
        swing2hd(-90, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 1, .earlyExitRange = 60 });
        bigArm.setMaxSpeed(100);
        bigArm.reset();
        swing2hd(-90, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 1, .earlyExitRange = 3 });

        // grab mogo
        turn2pt(-7.85859, 26.6474, 1000, { .forwards = false });
        mv2pt(-7.85859, 26.6474, 1000, { .forwards = false, .maxSpeed = 60,.minSpeed = 1, .earlyExitRange = 2 });
        toggleGoalClamp();
        mv2pt(-7.85859, 26.6474, 200, { .forwards = false });

        // corner
        turn2pt(29.7921, 9.25353, 1000, { .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(29.7921, 9.25353, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        swconn2pt(36.3146, -6.5, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 30, .earlyExitRange = 4 });
        spin_intk(100);
        ms2pt(36.3146, -6.5, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        swing2hd(135, lemlib::DriveSide::LEFT, 500, { .minSpeed = 10, .earlyExitRange = 2 });
        cornerMacro();
    }

    void posRingsReused() {
        turn2pt(7.0298, -33.0149, 1000, { .minSpeed = 1, .earlyExitRange = 70 });
        conn2pt(7.0298, -33.0149, 1000, { .maxSpeed = 40, .minSpeed = 1, .earlyExitRange = 3 });

        mv2pt(7.0298, -38.0149, 1000, { .minSpeed = 1, .earlyExitRange = 11 });
        toggleFrontRightArm();
        mv2pt(7.0298, -38.0149, 1000, { .minSpeed = 1, .earlyExitRange = 9 });
        pros::delay(250);

        drWait(0, 0.4, -1);
        swing2hd(149, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 40, .earlyExitRange = 5 });
        toggleFrontLeftArm();
        drWait(0.35, 0.35, 1.5);
        drive_chass(0, 0);

        // back up to align 3 in a row
        mv2pt(-14.9879, -2.60653, 1000, { .forwards = false, .minSpeed = 1,.earlyExitRange = 20 });
        mv2pt(-14.9879, -2.60653, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontRightArm();
        toggleFrontLeftArm();
        mv2pt(-14.9879, -2.60653, 250, { .forwards = false, .maxSpeed = 60 });

        // get 3 in a row
        conn2pt(-5.6822, -8.22241, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(-5.6822, -8.22241, 1000, { .minSpeed = 1, .earlyExitRange = 1.5 });
        swing2pt(-33.6738, -22.8087, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 80,.minSpeed = 1,.earlyExitRange = 2 });
        mv2pt(-33.6738, -22.8087, 1000, { .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });

        // get corner
        toggleFrontRightArm();
        swing2pt(-44.0299, 5.71201, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        toggleFrontRightArm();
        mv2pt(-44.0299, 5.71201, 1000, { .minSpeed = 1, .earlyExitRange = 7.5 });
        bigArm.set_target(posToScore);
        swing2hd(-45, lemlib::DriveSide::LEFT, 500, { .minSpeed = 30, .earlyExitRange = 4 });
        cornerMacro();

        // touch bar
        drWait(0.4, 0.4, -2);
        swconn2hd(180, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 40, .earlyExitRange = 30 });
        spin_intk(0);
        toggleGoalClamp();
        swconn2hd(180, lemlib::DriveSide::RIGHT, 250, { .minSpeed = 40 });
        bigArm.set_target(25100);
        mv2pt(-6.21138, -31.9386, 1000, { .maxSpeed = 80, .minSpeed = 50, .earlyExitRange = 5 });
        getChass()->setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
        getChass()->arcade(0, 0);
    }

    void pos5_1() {
        rightAlli_Mogo();

        posRingsReused();
        pros::delay(500);
    }

    void pos6() {
        rightMogo();

        // first ring
        turn2pt(6.74108, -36.1909, 500);
        mv2pt(6.74108, -36.1909, 1000, { .minSpeed = 1, .earlyExitRange = 8 });
        toggleFrontRightArm();
        mv2pt(6.74108, -36.1909, 250);

        // second ring
        swing2hd(153.494, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        toggleFrontLeftArm();
        drWait(0.3, 0.3, 1);
        drive_chass(0, 0);

        // back up to align 3 in a row
        mv2pt(-14.9879, -2.60653, 1000, { .forwards = false, .minSpeed = 1,.earlyExitRange = 10 });
        mv2pt(-14.9879, -2.60653, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontRightArm();
        toggleFrontLeftArm();
        mv2pt(-14.9879, -2.60653, 250, { .forwards = false, .maxSpeed = 60 });

        // get 3 in a row
        turn2pt(-5.6822, -8.22241, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(-5.6822, -8.22241, 1000, { .minSpeed = 1, .earlyExitRange = 1.5 });
        swing2pt(-33.6738, -22.8087, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 80,.minSpeed = 1,.earlyExitRange = 2 });
        mv2pt(-33.6738, -22.8087, 1000, { .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });

        // get corner
        swing2pt(-43.0299, 2.5, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        toggleIntakeLift();
        mv2pt(-43.0299, 2.5, 1000, { .minSpeed = 1, .earlyExitRange = 1 });
        bigArm.set_target(posToScore);
        swing2hd(-48, lemlib::DriveSide::LEFT, 500, { .minSpeed = 30, .earlyExitRange = 4 });
        cornerMacro();

        // clear corner
        toggleFrontRightArm();
        ms2pt(-42.733, 1.98133, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });
        drWait(0.4, 0.4, 1);
        turn2hd(-80, 500, { .direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .minSpeed = 126, .earlyExitRange = 10 });
        toggleFrontRightArm();
        drWait(0.4, 0.4, -1);
        turn2hd(135, 1000, { .minSpeed = 1, .earlyExitRange = 20 });
        toggleGoalClamp();
        turn2hd(135, 250);
        drWait(0.3, 0.3, -2);
        drWait(0.6, 0.6, -4);
        drWait(0.8, 0.8, -3);
        drive_chass(0, 0);
        pros::delay(100);
        mv2pt(-35.733, -5.98133, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        turn2hd(0, 1000);
    }
}