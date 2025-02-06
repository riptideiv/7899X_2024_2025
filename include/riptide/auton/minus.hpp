#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void minusRedBegin() {
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
        turn2pt(10, -44, 800);

        int t = pros::millis();
        mv2pt(10, -44, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "1 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(0.475137, -30.0357, 1000, { .forwards=false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(17.6335, -45.0706, 400);

        t = pros::millis();
        mv2pt(17.6335, -45.0706, 500, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 3 });
        std::cout << "3 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(-4.61257, -26.5479, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(18.1098, -25.2177, 500);

        t = pros::millis();
        mv2pt(18.1098, -25.2177, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "4 " << pros::millis() - t << '\n';

        pros::delay(500);
    }

    void minusRedV1() {
        printf("minusRedV1 was run\n");
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
        
        bot::bigArm.reset();

        minusRedBegin();

        bot::spin_intk(0);

        turn2pt(-34.0755, -2.19481, 900);

        bot::spin_intk(100);

        pros::Task toggleLiftTask([=](){
            pros::Task::delay(300);
            bot::toggleIntakeLift();
        });

        mv2pt(-34.0755, -2.19481, 2000, { .minSpeed = 10,.earlyExitRange = 2 });
        bot::bigArm.raise();
        bot::toggleIntakeLift();
        mv2pt(-34.0755, -2.19481, 250);
    }
    
    void minusRedV2() {
        printf("minusRedV2 was run\n");
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;
        bot::spin_intk(0);
        
        bot::bigArm.reset();

        minusRedBegin();

        bot::spin_intk(0);

        turn2pt(-34.0755, -2.19481, 900);

        bot::spin_intk(100);

        pros::Task toggleLiftTask([=](){
            pros::Task::delay(300);
            bot::toggleIntakeLift();
        });

        mv2pt(-34.0755, -2.19481, 2000, { .minSpeed = 10,.earlyExitRange = 2 });
        mv2pt(-34.0755, -2.19481, 250);
        mv2pt(-91.7966, 18, 1500, {.minSpeed=10,.earlyExitRange=24});
        bot::toggleIntakeLift();
        bot::toggleFrontRightArm();
        mv2pt(-91.7966, 18, 500, {.minSpeed=10,.earlyExitRange=10});
        mv2pt(-91.7966, 18, 500);
        turn2hd(-150, 1000, {.minSpeed=100, .earlyExitRange=20});
        bot::toggleFrontRightArm();
        turn2pt(-74.0122, 15.3511, 650, {.forwards=false});
        mv2pt(-74.0122, 15.3511, 1000, {.forwards=false,.minSpeed=10,.earlyExitRange=1});
        turn2pt(-95.9906, 13.7505, 300);
        mv2pt(-95.9906, 13.7505, 1000);
    }

    void minusBlueBegin() {
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

        mv2pt(2.97034, -32.5705, 1000, { .forwards=false, .minSpeed = 10, .earlyExitRange = 6 });

        turn2pt(-19.1308, -50.2083, 400);

        t = pros::millis();
        mv2pt(-19.1308, -50.2083, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 6.5 });
        std::cout << "3 " << pros::millis() - t << '\n';
        pros::delay(500);

        mv2pt(-1.40067, -34.134, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 8 });

        turn2pt(-16.6362, -31.8627, 500);

        t = pros::millis();
        mv2pt(-16.6362, -31.8627, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 5 });
        std::cout << "4 " << pros::millis() - t << '\n';

        pros::delay(500);
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

        minusBlueBegin();
    }
}