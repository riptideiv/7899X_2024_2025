#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedV1() {
        printf("minusRedV1 was run\n");
        bot::bigArm.reset();
        drWait(0.5, 0.5, -2);
        drWait(0.7, 0.7, -4);
        mv2pt(-3.8, -28.1001, 1000, { .forwards = false, .maxSpeed = 40 }, true);
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
        }
        mv2pose(10.5, -43.5313, 130.112, 3500, { .minSpeed = 40 }, true);
        pros::delay(750);
        bot::intake.set_colorsort(true, true);
        bot::intake.antiStuck = true;
        bot::spin_intk(100);
        bot::chass[0]->waitUntilDone();
        bot::getChass()->swingToHeading(90, lemlib::DriveSide::LEFT, 1000, {}, false);
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