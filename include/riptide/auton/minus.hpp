#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedSoloWP() {
        printf("minusRedSoloWP was run\n");
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
        mv2pose(3.57159, 7.65158, 42.7809, 1000, { .lead = 0.1, .minSpeed = 25, .earlyExitRange = 4 });
        mv2pt(0.217278, 3.39952, 500, { .minSpeed = 20, .earlyExitRange = 1 });
        bot::bigArm.reset();

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // take mogo & first ring
        turn2pt(-26.5, -2, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 1 });
        mv2pt(-26.5, -2, 1500, { .forwards = false, .maxSpeed = 40, .minSpeed = 20 });
        bot::toggleGoalClamp();
        pros::delay(200);
        turn2pt(-31.9366, -30.1298, 500);
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(100);
        mv2pt(-31.9366, -30.1298, 1000, { .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 3 });
        pros::delay(250);

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // mid ring
        turn2pt(-6, 21.4656, 800);
        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });
        mv2pt(-6, 21.4656, 2000, { .minSpeed = 10,.earlyExitRange = 5 });
        bot::toggleIntakeLift();

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // last ring
        turn2pt(-7.90262, 43.9741, 400);
        mv2pt(-7.90262, 43.9741, 1000, { .minSpeed = 10,.earlyExitRange = 2 });
        turn2pt(-31.6032, 70.0627, 500);
        bot::toggleGoalClamp();
        bot::bigArm.raise();
        mv2pt(-31.6032, 70.0627, 1500, { .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 3 });
        pros::delay(500);
        bot::spin_intk(0);
        pros::delay(500);
        turn2pt(-32.6359, 45.3611, 800, { .forwards = false });
        mv2pt(-32.6359, 45.3611, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 2 });
        bot::toggleGoalClamp();
        bot::spin_intk(100);
        pros::delay(1000);
        bot::bigArm.set_target(19425);
        mv2pt(-51.119, 33.644, 1000, { .minSpeed = 10, .earlyExitRange = 1 });
    }

    // recommended
    void minusRedElims() {
        printf("minusRedElims was run\n");
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
        turn2pt(13, -44, 1000, { .minSpeed = 20, .earlyExitRange = 5 });

        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;

        // ring #1
        int t = pros::millis();
        mv2pt(11, -44, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "1 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(0.475137, -30.0357, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(20, -45.0706, 1000, { .minSpeed = 20, .earlyExitRange = 5 });

        t = pros::millis();
        mv2pt(18, -45.0706, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "3 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(-4.61257, -26.5479, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(18.1098, -26.5, 1000, { .minSpeed = 10, .earlyExitRange = 5 });

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
        pros::delay(250);

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        mv2pt(-91.7966, 18, 1500, { .minSpeed = 10,.earlyExitRange = 30 });
        bot::spin_intk(-100);
        bot::toggleFrontRightArm();
        mv2pt(-91.7966, 18, 500, { .minSpeed = 10,.earlyExitRange = 10 });
        mv2pt(-91.7966, 18, 500);
        turn2hd(-215, 1000, { .direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .minSpeed = 127, .earlyExitRange = 90 });
        bot::toggleFrontRightArm();
        turn2hd(-215, 1000);

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';
    }

    void minusRedTwoStakePosCorner() {
        std::cout << "minusRedTwoStakePosCorner\n";
    }

    void minusBlueSoloWP() {
        printf("minusBlueSoloWP was run\n");
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
        mv2pose(-4.18527, 8.33226, -45.4873, 1000, { .lead = 0.1, .minSpeed = 25, .earlyExitRange = 4 });
        mv2pt(0.395338, 3.82862, 500, { .minSpeed = 20, .earlyExitRange = 1 });
        bot::bigArm.reset();

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // take mogo & first ring
        turn2pt(25.9462, -3.5, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(25.9462, -3.5, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20 });
        bot::toggleGoalClamp();
        pros::delay(200);
        turn2pt(32.8936, -29.9772, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(100);
        mv2pt(32.8936, -29.9772, 1000, { .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 3 });
        pros::delay(250);

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // mid ring
        bot::spin_intk(0);
        turn2pt(7.85229, 18.0956, 750);
        bot::spin_intk(100);
        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });
        mv2pt(7.85229, 18.0956, 2000, { .minSpeed = 10,.earlyExitRange = 30 });
        mv2pt(7.85229, 18.0956, 2000, { .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 2 });

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // // last ring
        // turn2pt(15, 45.8363, 600);
        mv2pt(5.99197, 22.055, 1000, { .minSpeed = 10,.earlyExitRange = 2 });
        bot::toggleIntakeLift();

        // turn2pt(37, 66, 600);
        // mv2pt(37, 66, 2000, { .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 2 });
        // bot::bigArm.raise();
        // pros::delay(50);
        // bot::spin_intk(0);
        bot::toggleGoalClamp();
        pros::delay(250);
        bot::spin_intk(0);

        bot::bigArm.raise();
        turn2pt(29.7679, 34.2021, 1000, { .forwards = false });
        mv2pt(29.7679, 34.2021, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 1 });
        bot::toggleGoalClamp();
        pros::delay(250);
        turn2pt(34, 58.6718, 1500, { .minSpeed = 10, .earlyExitRange = 2 });
        bot::spin_intk(100);
        mv2pt(34, 58.6718, 1000);
        turn2pt(47.2218, 27.7648, 1000, { .earlyExitRange = 10 });
        bot::bigArm.set_target(19000);
        mv2pt(47.2218, 27.7648, 1000);
    }

    // recommended
    void minusBlueElims() {
        printf("minusBlueElims was run\n");
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);

        bot::bigArm.reset();

        std::cout << "(begin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

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

        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        int t = pros::millis();
        mv2pt(-10, -49, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 6 });
        std::cout << "1 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(2.97034, -32.5705, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 6 });

        turn2pt(-19.1308, -50.2083, 400);

        t = pros::millis();
        mv2pt(-19.1308, -50.2083, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 7.5 });
        std::cout << "3 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(-1.40067, -34.134, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 6 });

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

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        mv2pt(30.9817, -9.90862, 2000, { .minSpeed = 10,.earlyExitRange = 5 });
        mv2pt(30.9817, -9.90862, 250);
        bot::toggleIntakeLift();
        pros::delay(250);
        mv2pt(86.4988, 10, 1500, { .minSpeed = 10,.earlyExitRange = 30 });
        bot::spin_intk(-100);
        bot::toggleFrontLeftArm();
        mv2pt(86.4988, 10, 500, { .minSpeed = 10,.earlyExitRange = 10 });
        mv2pt(86.4988, 10, 500);
        turn2hd(215, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 127, .earlyExitRange = 90 });
        bot::toggleFrontLeftArm();
        turn2hd(215, 1000);

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';
    }

    void minusBlueTwoStakePosCorner() {
        printf("minusBlueTwoStakePosCorner was run\n");
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
        bot::intake.set_colorsort(1, 0);
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
    }

    void coopSlot() {
        std::cout << "Running Coop \n";
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
        mv2pose(-4.18527, 8.33226, -45.4873, 1000, { .lead = 0.1, .minSpeed = 25, .earlyExitRange = 4 });
        mv2pt(0.395338, 3.82862, 500, { .minSpeed = 20, .earlyExitRange = 1 });
        bot::bigArm.reset();

        std::cout << "(afterBegin) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // take mogo & first ring
        turn2pt(25.9462, -3.5, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(25.9462, -3.5, 1500, { .forwards = false, .maxSpeed = 50, .minSpeed = 20 });
        bot::toggleGoalClamp();
        pros::delay(200);
        turn2pt(32.8936, -29.9772, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        bot::intake.set_colorsort(1, 0);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(100);
        mv2pt(32.8936, -29.9772, 1000, { .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 3 });
        pros::delay(250);

        std::cout << "(midRing) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        // mid ring
        bot::spin_intk(0);
        turn2pt(7.85229, 18.0956, 750);
        bot::spin_intk(100);
        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });
        mv2pt(7.85229, 18.0956, 2000, { .minSpeed = 10,.earlyExitRange = 30 });
        mv2pt(7.85229, 18.0956, 2000, { .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 2 });
        bot::toggleIntakeLift();
        pros::delay(250);

        std::cout << "(end) intake settings: " << bot::intake.doAntiStuck << ' ' << bot::intake.doColorSort << ' ' << bot::intake.colorSortRed << '\n';

        mv2pt(17.8366, -1.57987, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(28.4639, 1.86478, 1000);
        bot::bigArm.set_target(19000);
        mv2pt(28.4639, 1.86478, 1000);
    }
}