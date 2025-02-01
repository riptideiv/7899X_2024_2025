#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedBegin() {
        mv2pt(0, -18, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });
        turn2pt(-5.21, -20.7, 500, { .forwards = false });
        mv2pt(-5.21, -20.7, 1200, { .forwards = false, .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 1 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
            if (bot::mogoInRange(60)) {
                break;
            }
        }
        bot::toggleGoalClamp();
        pros::delay(50);
        bot::spin_intk(100);
        pros::delay(100);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
        }
        turn2pt(12.5, -42.1836, 1000);

        int t = pros::millis();
        mv2pt(12.5, -42.1836, 800, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 10.5 });
        std::cout << "1 " << pros::millis() - t << '\n';

        pros::delay(500);
        drWait(0.4, 0.4, -5);

        t = pros::millis();
        turn2pt(15, -40, 500);

        t = pros::millis();
        mv2pt(15, -40, 500, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 1.5 });
        std::cout << "3 " << pros::millis() - t << '\n';

        pros::delay(500);

        mv2pt(-4.61257, -26.5479, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 5 });

        turn2pt(12.0329, -27, 500);

        t = pros::millis();
        mv2pt(12.0329, -27, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "4 " << pros::millis() - t << '\n';

        pros::delay(500);
    }

    void minusRedV1() {
        printf("minusRedV1 was run\n");
        bot::bigArm.reset();
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);

        minusRedBegin();

        turn2pt(-34.8167, 2, 900);

        bot::toggleIntakeLift();

        mv2pt(-30.9457, -5.33101, 2000, { .minSpeed = 10,.earlyExitRange = 2 });

        bot::bigArm.toggleUp();
        bot::toggleIntakeLift();

        pros::Task stopIntakeTask([=]() {
            while (bot::intake.stuckFor < 50) {
                pros::delay(5);
            }
            });

        turn2pt(-33.8218, 7.41295, 1000);
        stopIntakeTask.join();
        bot::spin_intk(0);
        pros::delay(100);
        bot::bigArm.set_target(15000);
        mv2pt(-33.8218, 7.41295, 1000, { .minSpeed = 10, .earlyExitRange = 2.5 });
        pros::delay(750);
        mv2pt(-31.837, -3.8876, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });
    }
    void minusRedV2() {
        printf("minusRedV2 was run\n");
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
    }
    void minusBlueV1() {
        printf("minusBlueV1 was run\n");
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
    }
    void minusBlueV2() {
        printf("minusBlueV2 was run\n");
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
    }
}