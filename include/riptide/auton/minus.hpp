#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedV1() {
        printf("minusRedV1 was run\n");
        bot::bigArm.reset();
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
        mv2pt(0, -24, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 16 });
        turn2pt(-9.64065, -25.5599, 500, { .forwards = false });
        mv2pt(-9.64065, -25.5599, 1200, { .forwards = false, .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 1 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
            if (bot::mogoInRange(60)) {
                break;
            }
        }
        bot::spin_intk(100);
        bot::toggleGoalClamp();
        pros::delay(100);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
        }
        turn2pt(10.0354, -43.1836, 1000);

        int t = pros::millis();
        mv2pt(10.0354, -43.1836, 800, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 11.5 });
        std::cout << "1 " << pros::millis() - t << '\n';

        pros::delay(500);
        drWait(0.4, 0.4, -5);

        t = pros::millis();
        turn2pt(9, -38, 500);

        t = pros::millis();
        mv2pt(9, -38, 700, { .maxSpeed = 50, .minSpeed = 10, .earlyExitRange = 2.5 });
        std::cout << "2 " << pros::millis() - t << '\n';

        t = pros::millis();
        mv2pt(14.1656, -47.1844, 500, { .maxSpeed = 80, .minSpeed = 50, .earlyExitRange = 9 });
        std::cout << "3 " << pros::millis() - t << '\n';

        pros::delay(750);

        turn2pt(-4.48388, -28, 500, { .forwards = false });

        t = pros::millis();
        mv2pt(-4.48388, -28, 1000, { .forwards = false });

        t = pros::millis();
        turn2pt(12, -27, 1000);

        t = pros::millis();
        mv2pt(12, -27, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "4 " << pros::millis() - t << '\n';

        pros::delay(500);

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