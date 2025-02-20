#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void plusRedSoloWP() {
        printf("plusRedSoloWP was run\n");
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
        mv2pose(-4.18527, 8.33226, -45.4873, 1000, { .lead = 0.1, .minSpeed = 25, .earlyExitRange = 4 });
        mv2pt(0.395338, 3.82862, 500, { .minSpeed = 20, .earlyExitRange = 1 });
        bot::bigArm.reset();

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // take mogo & first ring
        turn2pt(25.9462, -3.5, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(25.9462, -3.5, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20 });
        bot::toggleGoalClamp();
        pros::delay(200);
        turn2pt(32.8936, -29.9772, 800);
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(100);
        mv2pt(32.8936, -29.9772, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        pros::delay(250);

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // mid ring
        turn2pt(7.85229, 18.0956, 1000);
        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });
        mv2pt(7.85229, 18.0956, 2000, { .minSpeed = 10,.earlyExitRange = 5 });
        bot::toggleIntakeLift();

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // last ring
        turn2pt(7.91834, 45.8363, 600);
        mv2pt(7.91834, 45.8363, 1000, { .minSpeed = 10,.earlyExitRange = 2 });
        turn2pt(34.667, 64.6133, 650);
        mv2pt(34.667, 64.6133, 1000, { .minSpeed = 30, .earlyExitRange = 4.5 });
        turn2hd(90, 500);
        bot::toggleGoalClamp();
        bot::spin_intk(0);
        bot::bigArm.raise();
        pros::delay(500);
        turn2pt(36, 46.106853, 1000, { .forwards = false });
        mv2pt(36, 46.106853, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 1 });
        bot::toggleGoalClamp();
        bot::spin_intk(100);
        pros::delay(200);
        bot::bigArm.set_target(19425);
        mv2pt(48.2293, 31.0163, 1000, { .minSpeed = 10, .earlyExitRange = 7 });
        bot::drive_chass(5, 5);
    }

    void plusRedElims() {
        printf("plusRedV2 was run\n");

    }

    void plusBlueSoloWP() {
        printf("plusBlueSoloWP was run\n");
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);

        std::cout << "(begin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // alliance stake
        pros::Task alliStakeBigArmTask([=]() {
            pros::Task::delay(250);
            bot::bigArm.set_target(14300);
            bot::bigArm.kP = 5;
            });
        mv2pose(3.57159, 7.65158, 42.7809, 1000, { .lead = 0.1, .minSpeed = 25, .earlyExitRange = 4 });
        mv2pt(0.217278, 3.39952, 500, { .minSpeed = 20, .earlyExitRange = 1 });
        bot::bigArm.reset();

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // take mogo & first ring
        turn2pt(-26.5, -3.5, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(-26.5, -3.5, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20 });
        bot::toggleGoalClamp();
        pros::delay(200);
        turn2pt(-31.9366, -30.1298, 800);
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
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
        turn2pt(-7.90262, 43.9741, 600);
        mv2pt(-7.90262, 43.9741, 1000, { .minSpeed = 10,.earlyExitRange = 2 });
        turn2pt(-31.6032, 70.0627, 650);
        mv2pt(-31.6032, 70.0627, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        turn2hd(-90, 500);
        bot::toggleGoalClamp();
        bot::spin_intk(0);
        bot::bigArm.raise();
        pros::delay(500);
        turn2pt(-32.6359, 45.3611, 1000, { .forwards = false });
        mv2pt(-32.6359, 45.3611, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 1 });
        bot::toggleGoalClamp();
        bot::spin_intk(100);
        pros::delay(200);
        bot::bigArm.set_target(19425);
        mv2pt(-41.506, 37.7836, 1000, { .minSpeed = 10, .earlyExitRange = 1 });
    }

    void plusBlueElims() {
        printf("plusBlueV2 was run\n");
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::bigArm.reset();
        bot::spin_intk(0);

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

        // first ring
        turn2pt(17.8367, -28.2999, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        mv2pt(17.8367, -28.2999, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 3 });
        pros::delay(300);

        // turn to mid
        mv2pt(-3.63438, -27.1817, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(-23, -4.3595, 1000, { .minSpeed = 10, .earlyExitRange = 5 });

        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });

        mv2pt(-32.4508, -4.3595, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        bot::toggleIntakeLift();
        mv2pt(-32.4508, -4.3595, 250);

        turn2pt(14, -0.981113, 1000);
        mv2pt(14, -0.981113, 2000, { .minSpeed = 5, .earlyExitRange = 1 });
        turn2pt(22.4797, 8.9119, 1000);

        mv2pt(22.4797, 8.9119, 1000, { .minSpeed = 127, .earlyExitRange = 0.5 });
        bot::drive_chass(100, 100);
        pros::delay(750);
        bot::getChass()->setPose(0, 0, 0);
        mv2pt(0, -7, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });

        bot::drive_chass(100, 100);
        pros::delay(1000);
        bot::getChass()->setPose(0, 0, 0);
        mv2pt(0, -7, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });

        bot::drive_chass(100, 100);
        pros::delay(1000);
        bot::getChass()->setPose(0, 0, 0);
        mv2pt(0, -7, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });
    }
}