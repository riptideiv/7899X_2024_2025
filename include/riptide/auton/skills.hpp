#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton{
    void autonSkills(){
        bot::bigArm.reset();
        bot::intake.set_colorsort(1, 1);
        bot::intake.doAntiStuck = true;

        // do not change this when changing starting positions!
        // (unless you adjust all the coordinates as well)
        bot::setPose(0,0.0393701*(bot::mogoDist.get_distance()-125),0);
        // starting position (FEB 3): 143 (originally was 120 but that doesnt work anymore)

        bot::spin_intk(100);
        pros::delay(550);
        bot::spin_intk(0);
        mv2pt(0.00230792, 12, 1000, {.minSpeed = 10, .earlyExitRange = 1});
        turn2pt(13.8791, 12, 550, {.forwards = false});
        mv2pt(13.8791, 12, 1000, {.forwards = false, .minSpeed = 10, .earlyExitRange = 1}, true);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
            if (bot::mogoInRange(60)) {
                break;
            }
        }
        bot::toggleGoalClamp();
        pros::delay(100);
        while (bot::getChass()->isInMotion()) {
            pros::delay(5);
        }
        // first ring
        turn2pt(22.7881, 35.9865, 700);
        bot::spin_intk(100);
        mv2pt(22.7881, 35.9865, 1000);
        // ring under ladder
        turn2pt(-2.74142, 60.3817, 700);
        mv2pt(-2.74142, 60.3817, 1000, {.minSpeed = 10, .earlyExitRange = 10});
        bot::spin_intk(0);
        mv2pt(-2.74142, 60.3817, 1000, {.minSpeed = 10, .earlyExitRange = 5});
        bot::spin_intk(100);
        mv2pt(-2.74142, 60.3817, 550);
        // first ring after ladder
        turn2pt(19.5666, 84.5676, 700);
        mv2pt(19.5666, 84.5676, 1000, {.minSpeed = 10, .earlyExitRange = 12});
        bot::spin_intk(0);
        mv2pt(19.5666, 84.5676, 1000, {.minSpeed = 10, .earlyExitRange = 8});
        bot::spin_intk(100);
        mv2pt(22.8929, 88.442, 500);
        // first ring for wall stake
        turn2pt(43.5817, 85.9459, 600);
        mv2pt(43.5817, 85.9459, 1000);
        bot::bigArm.toggleUp();
        pros::Task stopIntakeTask([=]() {
            while (bot::intake.stuckFor < 50) {
                pros::Task::delay(5);
            }
            });
        // move to wall stake position
        turn2pt(43.16, 63.369, 650);
        mv2pt(43.16, 63.369, 1000, {.minSpeed=10, .earlyExitRange=1});
        // turn to face wall stake & score
        stopIntakeTask.join();
        bot::spin_intk(0);
        pros::delay(100);
        bot::bigArm.raise();
        turn2pt(61.7112, 63.5, 1000);
        bot::spin_intk(100);
        // need to change wait vlaue
        mv2pose(65, 64, 90, 1000, {.minSpeed=60, .earlyExitRange=0.1});
        bot::spin_intk(0); 
        bot::bigArm.set_target(19800);

    }
}