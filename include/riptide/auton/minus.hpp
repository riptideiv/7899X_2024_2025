#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedV1() {
        printf("minusRedV1 was run\n");
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);

        std::cout << "(begin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // alliance stake
        pros::Task alliStakeBigArmTask([=]() {
            pros::Task::delay(250);
            bot::bigArm.set_target(14300);
            bot::bigArm.kP = 5;
            });
        mv2pose(6.10945, 8.82005, 40.6512, 1000, { .lead = 0.2, .minSpeed = 25, .earlyExitRange = 7 });
        mv2pt(0.217278, 3.39952, 500, { .minSpeed = 20, .earlyExitRange = 1 });
        bot::bigArm.reset();

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // take mogo & first ring
        turn2pt(-27.5024, -4.44832, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-27.5024, -4.44832, 1500, { .forwards = false, .maxSpeed = 40, .minSpeed = 20 });
        bot::toggleGoalClamp();
        pros::delay(200);
        turn2pt(-31.9366, -30.1298, 1000);
        bot::spin_intk(100);
        mv2pt(-31.9366, -30.1298, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        pros::delay(250);

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // mid ring
        turn2pt(-6, 21.4656, 1000);
        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });
        mv2pt(-6, 21.4656, 2000, { .minSpeed = 10,.earlyExitRange = 5 });
        bot::toggleIntakeLift();

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // last ring
        turn2pt(-7.90262, 43.9741, 650);
        mv2pt(-7.90262, 43.9741, 1000, { .minSpeed = 10,.earlyExitRange = 2 });
        turn2pt(-31.6032, 70.0627, 650);
        mv2pt(-31.6032, 70.0627, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        turn2hd(-90, 1000);
        bot::toggleGoalClamp();
        bot::spin_intk(0);
    }

    void minusRedV2() {
        printf("minusRedV2 was run\n");
        bot::intake.doAntiStuck = true;
        bot::intake.set_colorsort(1, 1);
        bot::spin_intk(0);

        bot::bigArm.reset();

        std::cout << "(begin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        mv2pt(0, -18, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 7 });
        turn2pt(-6, -24.5, 600, { .forwards = false });
        mv2pt(-6, -24.5, 1500, { .forwards = false, .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 2 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
            if (bot::mogoInRange(63)) {
                break;
            }
        }
        bot::toggleGoalClamp();
        pros::delay(50);
        bot::spin_intk(100);
        pros::delay(150);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
        }
        turn2pt(11, -44, 800);

        int t = pros::millis();
        mv2pt(11, -44, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5.5 });
        std::cout << "1 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(0.475137, -30.0357, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(18.5, -45.0706, 400);

        t = pros::millis();
        mv2pt(18.5, -45.0706, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "3 " << pros::millis() - t << '\n';
        pros::delay(300);

        mv2pt(-4.61257, -26.5479, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(18.1098, -26.5, 500);

        t = pros::millis();
        mv2pt(18.1098, -26.5, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "4 " << pros::millis() - t << '\n';

        pros::delay(500);

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        bot::spin_intk(0);

        turn2pt(-34.0755, -2.19481, 900);

        bot::spin_intk(100);

        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });

        mv2pt(-34.0755, -2.19481, 2000, { .minSpeed = 10,.earlyExitRange = 2 });
        mv2pt(-34.0755, -2.19481, 250);
        bot::toggleIntakeLift();

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        mv2pt(-91.7966, 18, 1500, { .minSpeed = 10,.earlyExitRange = 30 });
        bot::toggleFrontRightArm();
        mv2pt(-91.7966, 18, 500, { .minSpeed = 10,.earlyExitRange = 10 });
        mv2pt(-91.7966, 18, 500);
        turn2hd(-150, 1000, { .minSpeed = 127, .earlyExitRange = 20 });

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        bot::toggleFrontRightArm();
        bot::toggleGoalClamp();
        drWait(0.5, 0.5, 1);
        turn2hd(0, 1000);
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

        bot::bigArm.reset();

        mv2pt(0, -18, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 7 });
        turn2pt(6, -26, 500, { .forwards = false });
        mv2pt(6, -26, 1500, { .forwards = false, .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 2 }, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
            if (bot::mogoInRange(63)) {
                break;
            }
        }
        bot::toggleGoalClamp();
        pros::delay(50);
        bot::spin_intk(100);
        pros::delay(150);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
        }
        turn2pt(-10, -49, 800);

        int t = pros::millis();
        mv2pt(-10, -49, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "1 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(2.97034, -32.5705, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 6 });

        turn2pt(-19.1308, -50.2083, 400);

        t = pros::millis();
        mv2pt(-19.1308, -50.2083, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 6.5 });
        std::cout << "3 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(-1.40067, -34.134, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(-16.6362, -32.5, 500);

        t = pros::millis();
        mv2pt(-16.6362, -32.5, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "4 " << pros::millis() - t << '\n';

        pros::delay(500);

        bot::spin_intk(0);

        turn2pt(30.9817, -9.90862, 900);

        bot::spin_intk(100);

        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });

        mv2pt(30.9817, -9.90862, 2000, { .minSpeed = 10,.earlyExitRange = 5 });
        mv2pt(30.9817, -9.90862, 250);
        bot::toggleIntakeLift();
        mv2pt(86.4988, 10, 1500, { .minSpeed = 10,.earlyExitRange = 30 });
        bot::toggleFrontLeftArm();
        mv2pt(86.4988, 10, 500, { .minSpeed = 10,.earlyExitRange = 10 });
        mv2pt(86.4988, 10, 500);
        turn2hd(150, 1000, { .minSpeed = 127, .earlyExitRange = 20 });
        bot::toggleFrontLeftArm();
        bot::toggleGoalClamp();
        drWait(0.5, 0.5, 1);
        turn2hd(0, 1000);
    }
}