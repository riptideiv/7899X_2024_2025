#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

using std::cout, std::endl;

namespace red {
    void neg_rrush() {
        toggleFrontLeftArm();
        spin_intk(100);
        mv2pt(-8.5, 30.7458, 1000, { .minSpeed = 1, .earlyExitRange = 7 });
        cout << "chassVelo: " << bot::getChassVelo() << endl;

        mv2pt(-11.3, 42.8146, 470);
        intake.stopNextRing = true;

        mv2pt(-4.5, 11.893, 1000, { .forwards = false, .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontLeftArm();
        pros::delay(250);

        turn2pt(4.57842, 22.25, 670, { .forwards = false });
        mv2pt(4.57842, 22.25, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 5 });
        mv2pt(4.57842, 22.25, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2 });
        toggleGoalClamp();
        pros::delay(250);

        intake.stopNextRing = false;
        spin_intk(-15);
        turn2pt(-22, 23, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        spin_intk(100);
        mv2pt(-22, 23, 1400, { .maxSpeed = 50 });

        // corner
        turn2pt(-23.1772, -6, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        mv2pt(-23.1772, -6, 1000, { .minSpeed = 10, .earlyExitRange = 1.5 });
        turn2pt(-33.1636, -15.5, 370);
        mv2pt(-33.1636, -15.5, 700, { .maxSpeed = 45 });

        mv2pt(-22.1772, -8, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        mv2pt(-33.1636, -15.5, 700, { .maxSpeed = 45 });

        mv2pt(-22.1772, -8, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        mv2pt(-33.1636, -15.5, 700, { .maxSpeed = 45 });

        // alliance stake
        mv2pt(-12.9397, -2.69194, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 1 });
        turn2pt(14.7008, -12.2876, 1000);
        bigArm.set_load();
        mv2pt(14.7008, -12.2876, 1000);
    }

    void neg6_1() {
        neg_rrush();
    }

    void pos_trush() { // tower rush
        mv2pt(-6.43687, 33.1175, 1000, { .minSpeed = 1, .earlyExitRange = 10 });
        mv2pt(-6.43687, 33.1175, 1000, { .minSpeed = 80, .earlyExitRange = 2 });
        swing2pt(-2.72077, 41.1318, lemlib::DriveSide::RIGHT, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 3 });
        mv2pt(-2.02077, 42.6318, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 2 });
        turn2hd(-35, 450, { .maxSpeed = 70, .minSpeed = 1 });
        drWait(0.42, 0.42, 2);
        swing2hd(-75, lemlib::DriveSide::LEFT, 1000, { .maxSpeed = 60 });
        toggleFrontRightArm();
        pros::delay(150);
        turn2pt(7.81314, 27.9262, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 3 });
        mv2pt(7.81314, 27.9262, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 50, .earlyExitRange = 3 });
        toggleGoalClamp();
        pros::delay(250);
        swing2hd(58, lemlib::DriveSide::LEFT, 1000, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .maxSpeed = 70 });
        toggleFrontRightArm();
        pros::delay(250);
        turn2pt(31.0939, 31.5826, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(31.0939, 31.5826, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 1 });
    }

    void pos6_1() {
        bigArm.set_target(28800);
        bigArm.maxSpeed = 80;
        chass[2]->moveToPoint(17, 22, 1000, { .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 20 }, false);
        pros::delay(400);
        mv2pt(-7.0848, -25.4775, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 20 });
        bigArm.maxSpeed = 100;
        bigArm.reset();
        mv2pt(-7.0848, -25.4775, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 1, .earlyExitRange = 2 });
        toggleGoalClamp();
        mv2pt(-7.0848, -25.4775, 200, { .forwards = false, .maxSpeed = 50 });

        turn2pt(3.5, -31.4775, 600);
        mv2pt(3.5, -31.4775, 540);
        turn2hd(158, 350);

        toggleFrontLeftArm();
        chass[2]->moveToPoint(5.85926, -38.5027, 1000, { .minSpeed = 1, .earlyExitRange = 1.5 }, false);
        swing2hd(144, lemlib::DriveSide::RIGHT, 500, { .maxSpeed = 70 });
        toggleFrontRightArm();
        pros::delay(250);

        mv2pt(-14.9364, -4.18556, 1000, { .forwards = false, .minSpeed = 1,.earlyExitRange = 20 });
        mv2pt(-14.9364, -4.18556, 1000, { .forwards = false, .maxSpeed = 60,.minSpeed = 1,.earlyExitRange = 1 });
        turn2hd(181.577, 1000, { .maxSpeed = 70 });
    }
}