#pragma once

#include "main.h"

#include "autonIncludes.hpp"

namespace auton {
    void plusAllianceStake() {
        turn2pt(-4.164485, -3.904427, 500);
        bot::bigArm.set_target(5000);
        mv2pose(-4.5809335 * 1.2, -4.2948697 * 1.2, -130.252594, 1000);
    }

    void plusAllianceStake_PickupMogo() {
        plusAllianceStake();
        // printPose();
        drWait(0.2, 0.2, -4);
        bot::toggleIntakeLift();
        turn2pt(-17.556730, 7.157436, 500);
        // printPose();
        bot::bigArm.reset();
        bot::spin_intk(100);
        mv2pt(-5.45, 2.303006, 550);
        drWait(0.2, 0.2, 4.5);
        bot::toggleIntakeLift();
        pros::delay(250);
        drWait(0.3, 0.3, -4);
        mv2pt(-5.45, 1.36, 300);
        bot::spin_intk(15);
        turn2pt(13.310891, 37.665257, 600, { .forwards = false });
        mv2pt(2.5, 21, 1000, { .forwards = false, .maxSpeed = 60 });
        drWait(0.3, 0.3, -2);
        int i;
        for (i = 30; i--;) {
            pros::delay(10);
            if (bot::mogoDist.get() < 40) {
                bot::toggleGoalClamp();
                pros::delay(200);
                break;
            }
        }

        if (i < 0) {
            bot::toggleGoalClamp();
            pros::delay(200);
        }
    }
    void plusRiskAWP() {
        printf("plusRiskAWP was run\n");
    }
    void plusRiskNoAWP() {
        printf("plusRiskNoAWP was run\n");

        // lazy setup (for tuning)
        bot::setPose(0, 0, -90);

        // normal (tournament) setup
        // bot::setPose(0, 0, bot::getChass()->getPose().theta);

        plusAllianceStake_PickupMogo();

        bot::spin_intk(100);
        bot::getChass()->tank(0, 0);
        pros::delay(1500);
        turn2pt(32.328323, 31.935890, 1000, {});
        bot::spin_intk(-100);
        drWait(0.5, 0.5, 2, true);
        bot::spin_intk(100);
        drWait(0.5, 0.5, 18, true);
        bot::getChass()->tank(0, 0);
        pros::delay(1500);
        turn2pt(-12.7, 2.26, 1000, { .forwards = false });
        mv2pt(-16.7, 2.26, 5000, { .forwards = false });
    }
    void plusSafeAWP() {
        // lazy setup (for tuning)
        // bot::setPose(0, 0, -90);

        // normal (tournament) setup
        bot::setPose(0, 0, bot::getChass()->getPose().theta);

        plusAllianceStake_PickupMogo();

        bot::spin_intk(100);
        bot::getChass()->tank(0, 0);
        pros::delay(1500);
        turn2pt(32.328323, 32.435890, 1000, {});
        bot::spin_intk(-100);
        drWait(0.5, 0.5, 2, true);
        bot::spin_intk(100);
        drWait(0.5, 0.5, 18, true);
        bot::getChass()->tank(0, 0);
        pros::delay(1500);

        turn2pt(7.742729, 38.747849, 1000, {});
        bot::bigArm.set_target(9800);
        mv2pose(7.742729, 38.747849, -431.813049, 1500, {}, true);
        bot::spin_intk(-100);
        pros::delay(200);
        bot::spin_intk(100);
        printf("plusSafeAWP was run\n");
    }
    void plusSafeNoAWP() {
        bot::setPose(0, 0, bot::getChass()->getPose().theta);

        plusAllianceStake();

        // printPose();
        drWait(0.2, 0.2, -7);
        // bot::toggleIntakeLift();
        // turn2pt(-17.556730, 7.157436, 600);
        // printPose();
        bot::bigArm.reset();
        // bot::spin_intk(100);
        // mv2pt(-6.95, 1.803006, 700);
        // drWait(0.2, 0.2, 3);
        // bot::toggleIntakeLift();
        // drWait(0.3, 0.3, -1);
        // mv2pt(-8, 1.36, 400);
        // bot::spin_intk(1);
        // turn2pt(9.310891, 37.665257, 1000, { .forwards = false });
        // mv2pt(2, 20.375, 1000, { .forwards = false });
        // drWait(0.3, 0.3, -10);
        // for (int i = 60; i--;) {
        //     pros::delay(10);
        //     if (bot::mogoDist.get() < 40) {
        //         bot::toggleGoalClamp();
        //         pros::delay(200);
        //         break;
        //     }
        // }
        // bot::spin_intk(100);
        // bot::getChass()->tank(0, 0);
        // pros::delay(1500);
        // bot::spin_intk(-30);;
        // turn2pt(32.328323, 34.935890, 750);
        // bot::spin_intk(100);
        // drWait(0.5, 0.5, 20, true);
        // bot::getChass()->tank(0, 0);
        // pros::delay(1500);

        turn2pt(7.742729, 38.747849, 1000, { .forwards = false });
        mv2pt(7.742729, 38.747849, 3000, { .forwards = false });
        bot::bigArm.set_target(9800);
        turn2hd(-71.813049, 5000);
        printf("plusSafeNoAWP was run\n");
    }
}