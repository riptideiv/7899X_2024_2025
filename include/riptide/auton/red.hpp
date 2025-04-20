#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace red {
    void neg_rrush() {
        // rush rings
        toggleFrontLeftArm();
        spin_intk(100);
        intake.stopNextRing = true;
        mv2pt(-6.01485, 25.1478, 1000, { .minSpeed = 1, .earlyExitRange = 10 });
        mv2pt(-6.01485, 25.1478, 1000, { .minSpeed = 110, .earlyExitRange = 3 });
        mv2pt(-14.7999, 47.2078, 1000, { .minSpeed = 1, .earlyExitRange = 1 });

        // get mogo
        mv2pt(-10.8741, 39.0592, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 4 });
        mv2pt(-10.8741, 39.0592, 1000, { .forwards = false, .minSpeed = 50, .earlyExitRange = 1 });
        swing2pt(3.52909, 31.6104, lemlib::DriveSide::RIGHT, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(3.52909, 31.6104, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 3 });
        toggleGoalClamp();
        drWait(0.5, 0.5, -6);

        // line up rings
        swing2pt(-17.999, 26.3019, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 30, .minSpeed = 1, .earlyExitRange = 15 });
        toggleFrontLeftArm();
        pros::delay(200);

        // pick up rings
        turn2pt(-17.999, 20.7019, 1000, { .minSpeed = 30, .earlyExitRange = 4 });
        spin_intk(100);
        mv2pt(-17.999, 20.7019, 1000, { .maxSpeed = 70 });

        // approach corner
        turn2pt(-26.5479, -4.46945, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(-26.5479, -4.46945, 1000, { .minSpeed = 10, .earlyExitRange = 2 });
        swing2hd(-133.372, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 10, .earlyExitRange = 3 });

        // get corner ring #1 & back out
        mv2pt(-32.2205, -10.4361, 1000);
        mv2pt(-27.4005, -5.41137, 1000, { .forwards = false });
    }

    void neg6_1() {
        // alliance stake
        bigArm.set_target(28800);
        mv2pt(-9.29513, 3.75558, 1000, {}, true);
        while (getChass()->isInMotion() && bigArm.rotation->get_position() < 26750) pros::delay(3);

        // get mogo
        getChass()->cancelAllMotions();
        pros::delay(10);
        mv2pt(-3.5092, -10.0422, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 3 });
        bigArm.reset();
        toggleFrontRightArm();
        mv2pt(5.12367, -25.2758, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 10, .earlyExitRange = 3 });
        toggleGoalClamp();
        toggleFrontRightArm();
        drWait(0.3, 0.3, -2);

        // contested rings
        turn2hd(139.396, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 10, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(16.3397, -40.7683, 1000, { .maxSpeed = 70, .minSpeed = 10, .earlyExitRange = 8 });
        swing2hd(108.094, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        drWait(0.3, 0.3, 1.5);
        drWait(0.4, 0.4, 2);
        swing2pt(36.7799, -38.5, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(36.7799, -38.5, 1000, { .maxSpeed = 60 });

        // safe ring
        drWait(0, 0.3, -1);
        turn2pt(29.056, -15.8972, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        mv2pt(29.056, -15.8972, 1000, { .minSpeed = 10, .earlyExitRange = 7 });
        mv2pt(29.056, -15.8972, 1000, { .minSpeed = 90, .earlyExitRange = 2 });
        mv2pt(29.056, -15.8972, 500);

        // corner
        turn2hd(46.2563, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        drWait(0.3, 0.3, 1);
        drWait(0.5, 0.5, 1);
        mv2pt(39.7483, 0.526427, 1000, { .minSpeed = 10, .earlyExitRange = 9 });
        mv2pt(39.7483, 0.526427, 1000, { .minSpeed = 70, .earlyExitRange = 2 });
        mv2pt(42.0759, 19.063, 1000, { .maxSpeed = 70 });
    }

    void pos_trush() { // tower rush
        mv2pt(-6.43687, 33.1175, 1000, { .minSpeed = 1, .earlyExitRange = 10 });
        mv2pt(-6.43687, 33.1175, 1000, { .minSpeed = 80, .earlyExitRange = 2 });
        swing2pt(-2.72077, 41.1318, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(-2.02077, 42.6318, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 2 });
        turn2hd(-35, 450, { .maxSpeed = 70, .minSpeed = 1 });
        drWait(0.42, 0.42, 2);
        swing2hd(-75, lemlib::DriveSide::LEFT, 1000, { .maxSpeed = 60 });
        toggleFrontRightArm();
        pros::delay(150);
        turn2pt(7.81314, 27.9262, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 3 });
        mv2pt(7.81314, 27.9262, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 50, .earlyExitRange = 3 });
        toggleGoalClamp();
        pros::delay(250);
        swing2hd(58, lemlib::DriveSide::LEFT, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 70 });
        toggleFrontRightArm();
        pros::delay(250);
        turn2pt(31.0939, 31.5826, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(31.0939, 31.5826, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 1 });
    }
}