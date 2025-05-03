#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace blue {
    void neg_rrush() {
        toggleFrontRightArm();
        spin_intk(100);
        mv2pt(7.5, 26.9659, 1000, { .minSpeed = 1, .earlyExitRange = 7 });
        cout << "chassVelo: " << bot::getChassVelo() << endl;

        mv2pt(12, 43, 560);
        intake.stopNextRing = true;

        mv2pt(5.19645, 10, 1000, { .forwards = false, .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontRightArm();
        pros::delay(250);

        turn2pt(-8.56626, 29.5, 670, { .forwards = false });
        mv2pt(-8.56626, 29.5, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 5 });
        mv2pt(-8.56626, 29.5, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2 });
        toggleGoalClamp();
        pros::delay(250);

        intake.stopNextRing = false;
        spin_intk(-15);
        turn2pt(18.9218, 28.8533, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(18.9218, 28.8533, 1300, { .maxSpeed = 50 });

        // corner
        turn2pt(22.5, 8.5, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        mv2pt(22.5, 8.5, 1000, { .minSpeed = 10, .earlyExitRange = 1.5 });
        turn2pt(34.75, -2.5, 500);
        mv2pt(34.75, -2.5, 1000, { .maxSpeed = 45 });

        mv2pt(23.5, 6.5, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        mv2pt(34.75, -2.5, 700, { .maxSpeed = 60 });

        mv2pt(23.5, 6.5, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        mv2pt(34.75, -2.5, 700, { .maxSpeed = 60 });

        // alli stake
        mv2pt(21.4321, 5.79396, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        turn2pt(-7.5576, 0, 1000, { .minSpeed = 1, .earlyExitRange = 2 });

        mv2pt(-6, 1, 1000, { .minSpeed = 1, .earlyExitRange = 1 });
        bigArm.set_load();

        turn2pt(-28.5947, 10.8742, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        toggleIntakeLift();
        pros::delay(310);
        spin_intk(0);
        pros::delay(50);
        bigArm.raise();
        pros::delay(100);
        spin_intk(100);
        mv2pt(-28.5947, 10.8742, 1000);
        toggleFrontLeftArm();
        turn2pt(-23.5, -11, 1000, { .minSpeed = 1, .earlyExitRange = 1.5 });
        toggleFrontLeftArm();
        drive_chass(50, 50);
        pros::delay(750);
        alliStakeMacro();
    }

    void neg6_1() {
        neg_rrush();
    }

    void pos_trush() {
        mv2pt(6.01001, 29.5364, 1000, { .minSpeed = 1, .earlyExitRange = 10 });
        mv2pt(6.01001, 29.5364, 1000, { .minSpeed = 100, .earlyExitRange = 2 });
        toggleFrontRightArm();
        swing2pt(13.7675, 53.9935, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(13.7675, 53.9935, 1000, { .minSpeed = 1, .earlyExitRange = 11 });
    }

    void pos6_1() {
        bigArm.set_target(posScore - 3000);
        mv2pt(-17.3345, 45.09771, 1000, { .minSpeed = 1, .earlyExitRange = 25 });
        std::cout << "chassVelo: " << bot::getChassVelo() << std::endl;
        mv2pt(-17.3345, 45.09771, 1000, { .maxSpeed = 100, .minSpeed = 1, .earlyExitRange = 20.5 });
        bigArm.set_target(33000);
        mv2pt(-17.3345, 45.09771, 1000, { .maxSpeed = 100, .minSpeed = 1, .earlyExitRange = 20 });
        std::cout << "chassVelo: " << bot::getChassVelo() << std::endl;
        mv2pt(-12.9839, 39.0194, 2000, { .minSpeed = 1, .earlyExitRange = 2 }, true);
        while (bigArm.rotation->get_position() < 27000) {
            pros::delay(3);
        }
        if (getChass()->isInMotion()) {
            getChass()->cancelMotion();
        }
        mv2pt(-12.9297, 35.0837, 250);
        swing2hd(45, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        turn2hd(80, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        // mv2pt(-32.7091, 31.5225, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 2 });
        // turn2pt(-25.7746, 45.9314, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        // spin_intk(100);
        // mv2pt(-25.7746, 45.9314, 1000, { .minSpeed = 1, .earlyExitRange = 1 });
        // intake.stopNextRing = true;
        // mv2pt(-8.71792, 16.9396, 1000, { .forwards = false });
    }
}