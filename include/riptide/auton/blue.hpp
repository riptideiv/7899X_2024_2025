#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace blue {
    void minus2_1_2() {
        // // bigArm.reset();
        // // rush 1 ring
        // spin_frintk(100);
        // mv2pt(6.41525, 16.7389, 1000, { .minSpeed = 20, .earlyExitRange = 10 });
        // mv2pt(10.5, 43.3794, 1300, { .minSpeed = 10, .earlyExitRange = 15 });
        // mv2pt(10.5, 43.3794, 850, { .maxSpeed = 40 });

        // // get mogo
        // turn2pt(-2.52609, 39, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 2 });
        // spin_frintk(0);
        // drWait(0.65, 0.8, -3.5);
        // mv2pt(-6.65004, 31.3562, 1100, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 0.5 });
        // toggleGoalClamp();
        // pros::delay(200);

        // // load norush ring into big arm
        // spin_intk(100);
        // turn2pt(24.7293, 36, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        // mv2pt(24.7293, 36, 1000, { .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 5 });
        // bigArm.toggleUp();
        // mv2pt(24.7293, 36, 300, { .maxSpeed = 30 });

        // // move toward alliance stake
        // turn2pt(3, 20.5607, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        // mv2pt(3, 20.5607, 1000, { .minSpeed = 20, .earlyExitRange = 10 });

        // // score alliance stake
        // turn2pt(-28.1, -13, 1000, { .minSpeed = 15, .earlyExitRange = 1 });
        // mv2pt(-28.1, -13, 1000, { .minSpeed = 20, .earlyExitRange = 45 });
        // mv2pt(-28.1, -13, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 25 });
        // mv2pt(-28.1, -13, 1000, { .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 19 });
        // spin_frintk(-100);
        // spin_upintk(0);
        // bigArm.set_target(14300);
        // mv2pt(-28.1, -12.484602, 1000, { .maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 16 });
        // double x = getChass()->getPose().x;
        // double y = getChass()->getPose().y;
        // double theta = getChass()->getPose().theta;
        // mv2pose(x, y, theta, 500);
        // toggleIntakeLift();
        // mv2pt(3, 20.5607, 1000, { .minSpeed = 10, .earlyExitRange = 15 });
        // bigArm.reset();

        // // get mid ring
        // spin_intk(100);
        // turn2pt(-30.3251, 7.0858, 1000, { .minSpeed = 15, .earlyExitRange = 5 });
        // toggleGoalClamp();
        // mv2pt(-30.3251, 7.0858, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        // toggleIntakeLift();
        // mv2pt(-30.3251, 7.0858, 500);
        // spin_intk(0);

        // // get 2nd mogo
        // turn2pt(-50, 30.9903, 1000, { .forwards = false, .direction = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE, .minSpeed = 15, .earlyExitRange = 3 });
        // mv2pt(-54.5671, 30.9903, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 5 });
        // toggleGoalClamp();
        // pros::delay(200);

        // // get last ring
        // turn2pt(-69.93, 31.5863, 1000, { .minSpeed = 20, .earlyExitRange = 10 });
        // spin_intk(100);
        // mv2pt(-75.0669, 30.5846, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        // mv2pt(-75.0669, 30.5846, 250);
        // mv2pt(-49.6032, 31.3722, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 5 });;
        // turn2pt(-50, 44.7983, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        // mv2pt(-50, 44.7983, 1000, { .minSpeed = 40, .earlyExitRange = 5 });
        // getChass()->setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
        // drive_chass(0, 0);
    }

    void minus5_1() {
        // alliance stake
        pros::Task alliStakeBigArmTask([=]() {
            pros::Task::delay(300);
            bot::bigArm.set_target(14300);
            bot::bigArm.kP = 5;
            });
        mv2pose(-4.18527, 8.33226, -45.4873, 1000, { .lead = 0.1, .minSpeed = 25, .earlyExitRange = 4 });
        // pros::delay(250);
        mv2pt(0.395338, 3.82862, 500, { .minSpeed = 30, .earlyExitRange = 1 });
        bot::bigArm.reset();

        // get mogo
        turn2pt(10.2104, 4.58229, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 5 });
        mv2pt(10.2104, 4.58229, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        turn2pt(30.7587, -6.40583, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 10 });
        mv2pt(30.7587, -6.40583, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 20, .earlyExitRange = 5 });
        toggleGoalClamp();
        pros::delay(200);
        spin_intk(100);

        // get contested rings
        turn2pt(50.5, -24.5, 700);
        mv2pt(50.5, -24.5, 1000, { .maxSpeed = 60, .minSpeed = 10, .earlyExitRange = 5 });
        turn2pt(51, -38.2363, 1000, { .minSpeed = 10, .earlyExitRange = 5 });
        mv2pt(51, -38.2363, 850);

        // get norush ring
        turn2pt(30.4014, -33.5, 1000, { .minSpeed = 30, .earlyExitRange = 5 });
        mv2pt(30.4014, -33.5, 1000, { .maxSpeed = 51, .minSpeed = 50, .earlyExitRange = 1 });

        // // get corner
        // mv2pt(13.7848, -33.6309, 1000, { .minSpeed = 40, .earlyExitRange = 2 });
        // turn2pt(-3.54008, -47.7159, 550);
        // mv2pt(-7, -52.7159, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 6 });
        // pros::delay(250);
        // mv2pt(1.79702, -42.686, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 2.5 });
        // pros::delay(300);
        // mv2pt(-7, -52.7159, 2000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 6 });
        // pros::delay(250);
        // mv2pt(1.79702, -42.686, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 2.5 });
        // pros::delay(300);
        // mv2pt(-7, -52.7159, 2000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 6 });
        // pros::delay(250);
        // mv2pt(1.79702, -42.686, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 10, .earlyExitRange = 2.5 });
        // pros::delay(300);
    }

    void minus6() {

    }

    void minus5clear() {

    }

    void plus5() {

    }

    void plus4_1() { // modified from plus5

    }

    void plusRush3_1() {

    }

    void plusRush2_1_1() {

    }
}