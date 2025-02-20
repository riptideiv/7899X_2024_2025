#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace red {
    void minus2_1_2() {

    }

    void minus5_1() {
        // alliance stake
        pros::Task alliStakeBigArmTask([=]() {
            pros::Task::delay(300);
            bot::bigArm.set_target(14300);
            bot::bigArm.kP = 5;
            });
        mv2pose(4.18527, 9, 45, 1000, { .lead = 0.1, .minSpeed = 28, .earlyExitRange = 4 });
        // pros::delay(250);
        mv2pt(-0.395338, 3.82862, 500, { .minSpeed = 30, .earlyExitRange = 1 });
        bot::bigArm.reset();

        // get mogo
        turn2pt(-10.2104, 4.58229, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 5 });
        mv2pt(-10.2104, 4.58229, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(-33.7587, -5, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 10 });
        mv2pt(-33.7587, -5, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 5 });
        toggleGoalClamp();
        pros::delay(200);

        // get contested rings
        turn2pt(-47, -18, 700);
        spin_intk(100);
        mv2pt(-47, -18, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 5 });
        turn2pt(-46.5, -36, 1000, { .minSpeed = 15, .earlyExitRange = 5 });
        mv2pt(-46.5, -36, 850);

        // get norush ring
        turn2pt(-30.4014, -27.5, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        mv2pt(-30.4014, -27.5, 1000, { .maxSpeed = 51, .minSpeed = 50, .earlyExitRange = 1 });

        // get corner
        mv2pt(-1.7848, -27.5, 1000, { .minSpeed = 20, .earlyExitRange = 1 });
        turn2pt(23, -50, 550);
        mv2pt(23, -50, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 18 });
        pros::delay(250);
        mv2pt(5.74047, -31.7604, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 3.5 });
        pros::delay(300);
        mv2pt(23, -50, 2000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 18 });
        pros::delay(250);
        mv2pt(5.74047, -31.7604, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 3.5 });
        pros::delay(300);
        mv2pt(23, -50, 2000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 18 });
        pros::delay(250);
        mv2pt(5.74047, -31.7604, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 3.5 });
        pros::delay(300);
    }

    void minus6() {

    }

    void minus5clear() {
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

    void plus5() {
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::bigArm.reset();
        bot::spin_intk(0);

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

        // first ring
        turn2pt(-17.2918, -29.7343, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        mv2pt(-17.2918, -29.7343, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 3 });
        pros::delay(300);

        // turn to mid
        mv2pt(5.13989, -30.4452, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(20, -7.85, 1000, { .minSpeed = 10, .earlyExitRange = 5 });

        pros::Task toggleLiftTask([=]() {
            pros::Task::delay(300);
            bot::toggleIntakeLift();
            });

        mv2pt(29.815, -7.85, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        bot::toggleIntakeLift();
        mv2pt(29.815, -7.85, 250);

        turn2pt(-21, 0, 1000);
        mv2pt(-21, 0, 2000, { .minSpeed = 5, .earlyExitRange = 1 });
        turn2pt(-27.4693, 7.13953, 1000);

        mv2pt(-27.4693, 7.13953, 1000, { .minSpeed = 127, .earlyExitRange = 0.5 });
        bot::drive_chass(100, 100);
        pros::delay(750);
        bot::getChass()->setPose(0, 0, 0);
        mv2pt(0, -10, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });

        bot::drive_chass(100, 100);
        pros::delay(1000);
        bot::getChass()->setPose(0, 0, 0);
        mv2pt(0, -10, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });

        bot::drive_chass(100, 100);
        pros::delay(1000);
        bot::getChass()->setPose(0, 0, 0);
        mv2pt(0, -10, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });
    }

    void plus4_1() { // modified from plus5

    }

    void plus3_1() {

    }

    void plusRush3_1() {

    }
}