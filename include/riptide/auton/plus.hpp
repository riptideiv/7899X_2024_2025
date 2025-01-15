#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void plusRedV1() {
        printf("plusRedV1 was run\n");
        bot::intake.set_colorsort(1, 1);
        bot::intake.antiStuck = true;
        bot::spin_intk(0);
        bot::chass[0]->setPose(0, -1, 0);
        bot::chass[1]->setPose(0, -1, 0);
        bot::bigArm.reset();
        mv2pt(0, 38.5, 3500, { .minSpeed = 1, .earlyExitRange = 19 });
        mv2pt(-3, 38.5, 600, { .maxSpeed = 60 }, true);
        pros::delay(250);
        bot::toggleFrontLeftArm();
        mv2pt(-3, 17, 1000, { .forwards = false, .maxSpeed = 60 });
        bot::toggleFrontLeftArm();
        pros::delay(50);
        turn2pt(-3, 35.2, 700, { .forwards = false });
        mv2pt(-6, 35.2, 850,
            { .forwards = false, .maxSpeed = 40,
            .minSpeed = 10, .earlyExitRange = 3 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(10);
            if (bot::mogoDist.get() < 75) {
                bot::toggleGoalClamp();
                break;
            }
        }
        if (bot::MOGO) {
            bot::getChass()->cancelAllMotions();
            pros::delay(500);
            bot::spin_intk(100);
            pros::delay(500);
        } else {
            // bot::toggleGoalClamp();
        }
        drWait(0.4, 0.4, 0.3);
        turn2pt(-15, 26, 800);
        bot::spin_intk(100);
        drWait(0.5, 0.5, 20);
        bot::bigArm.set_target(18200);
        turn2hd(-45, 2000);
        drWait(0.5, 0.5, 12);
    }
    void plusRedV2() {
        printf("plusRedV2 was run\n");
    }
    void plusBlueV1() {
        printf("plusBlueV1 was run\n");
        bot::intake.set_colorsort(1, 0);
        bot::intake.antiStuck = true;
        bot::spin_intk(0);
        bot::chass[0]->setPose(0, -1, 0);
        bot::chass[1]->setPose(0, -1, 0);
        bot::bigArm.reset();
        mv2pt(0, 38.5, 3500, { .minSpeed = 1, .earlyExitRange = 19 });
        mv2pt(3, 38.5, 600, { .maxSpeed = 60 }, true);
        pros::delay(250);
        bot::toggleFrontRightArm();
        mv2pt(3, 17, 1000, { .forwards = false, .maxSpeed = 60 });
        bot::toggleFrontRightArm();
        pros::delay(50);
        turn2pt(3, 35.2, 700, { .forwards = false });
        mv2pt(6, 35.2, 850,
            { .forwards = false, .maxSpeed = 40,
            .minSpeed = 10, .earlyExitRange = 3 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(10);
            if (bot::mogoDist.get() < 75) {
                bot::toggleGoalClamp();
                break;
            }
        }
        if (bot::MOGO) {
            bot::getChass()->cancelAllMotions();
            pros::delay(500);
            bot::spin_intk(100);
            pros::delay(500);
        } else {
            // bot::toggleGoalClamp();
        }
        drWait(0.4, 0.4, 0.3);
        turn2pt(15, 26, 800);
        bot::spin_intk(100);
        drWait(0.5, 0.5, 17);
        bot::bigArm.set_target(18200);
        turn2hd(45, 2000);
        drWait(0.5, 0.5, 12);
    }
    void plusBlueV2() {
        printf("plusBlueV2 was run\n");
    }
}