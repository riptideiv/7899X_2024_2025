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
        mv2pt(-8, -27.1001, 1000, { .forwards = false, .maxSpeed = 40 }, true);
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