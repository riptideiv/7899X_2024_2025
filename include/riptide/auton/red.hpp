#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace red {
    void minus2_1_2() {
        chass[1]->turnToHeading(45, 1000);
    }

    void minus5_1() {
        // score alli stake
        bigArm.setMaxSpeed(70);
        bigArm.set_target(14300);
        int start = pros::millis();
        mv2pt(4.82649, 9.65794, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        while (pros::millis() - start < 1000 && bigArm.rotation->get_position() > 17000) pros::delay(3);

        // position to get mogo
        drWait(0.6, 0.55, -2);
        bigArm.reset();
        mv2pt(-12.4457, -14.2492, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });

        // get mogo
        turn2pt(-30.1466, -6.94558, 1000, { .forwards = false, .minSpeed = 25, .earlyExitRange = 2 });
        toggleFrontRightArm();
        mv2pt(-30.1466, -6.94558, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 4 });
        toggleGoalClamp();
        mv2pt(-30.1466, -6.94558, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 2 });
        toggleFrontRightArm();

        // get contested rings
        turn2pt(-45.75, -24.0684, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(-45.75, -24.0684, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 2 });
        turn2pt(-45.75, -37.394, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        mv2pt(-45.75, -37.394, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 1 });

        // get norush ring
        drWait(0, 0.7, -1);
        turn2pt(-29.9316, -29.3272, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(-29.9316, -29.3272, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 3 });

        // get corner
        mv2pt(-3.4428, -27.2393, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        turn2pt(10.436, -39.2978, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(10.436, -39.2978, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        drive_chass(40, 40);
        pros::delay(1000);
        drWait(0.6, 0.6, -10);

        // get mid
        turn2pt(-8.14447, 6.37123, 1000, { .minSpeed = 40, .earlyExitRange = 2 });
        mv2pt(-8.14447, 6.37123, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        toggleIntakeLift();
        turn2pt(-6.68803, 26.3079, 1000, { .minSpeed = 20, .earlyExitRange = 1 });
        mv2pt(-6.68803, 26.3079, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        toggleIntakeLift();
        drWait(0.6, 0.6, -5);
        drive_chass(0, 0);
        pros::delay(5000);
    }

    void minus6() {}

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