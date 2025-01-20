#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedV1() {
        printf("minusRedV1 was run\n");
        bot::chass[0]->setPose(1, 0, 0);
        bot::bigArm.reset();
        drWait(0.5, 0.5, -2);
        drWait(0.7, 0.7, -4);
        mv2pt(-6, -27.1001, 1000, { .forwards = false, .maxSpeed = 40 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(10);
            if (bot::mogoDist.get() < 60) {
                bot::toggleGoalClamp();
                break;
            }
        }
        if (bot::MOGO) {
            pros::delay(200);
            bot::getChass()->cancelAllMotions();
        } else {
            bot::toggleGoalClamp();
        }
        turn2pt(10.5, -40, 850);
        bot::intake.set_colorsort(true, true);
        bot::intake.antiStuck = true;
        bot::spin_intk(100);
        mv2pose(10.5, -42.0313, 130.112, 4000,
            { .minSpeed = 40, .earlyExitRange = 1 });
        bot::getChass()->swingToHeading(90, lemlib::DriveSide::LEFT, 450, { .maxSpeed = 90 }, false);
        mv2pt(23, -36.86, 1400, { .maxSpeed = 30 });
        drWait(0.3, 0.3, -2);
        bot::getChass()->swingToPoint(0, -22, lemlib::DriveSide::LEFT, 2000, { .maxSpeed = 60 }, false);
        mv2pt(3, -22, 1000, { .maxSpeed = 35 });
        bot::getChass()->swingToHeading(-45, lemlib::DriveSide::RIGHT, 1000, {}, false);
        mv2pt(-60, 4, 4000);
    }
    void minusRedV2() {
        printf("minusRedV2 was run\n");
    }
    void minusBlueV1() {
        printf("minusBlueV1 was run\n");
    }
    void minusBlueV2() {
        printf("minusBlueV2 was run\n");
    }
}