#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace blue {
    void neg_rrush() {
        toggleFrontRightArm();
        spin_intk(100);
        intake.stopNextRing = true;
        mv2pt(12.6959, 43.0397, 1000);
        mv2pt(-3.39057, 27.9273, 1000, { .forwards = false,.maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 1 });
        toggleGoalClamp();
        toggleFrontRightArm();
        drWait(0.4, 0.4, -2);
        turn2hd(65, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        intake.stopNextRing = false;
        spin_intk(100);
        mv2pt(16.9988, 31.3872, 1000);
    }

    void neg6_1() {
        rightAlli_Mogo();
        toggleFrontRightArm();
        pros::delay(250);
        toggleFrontRightArm();

        // get 3 rings
        turn2pt(-26.5, -41.5892, 800);
        spin_intk(100);
        mv2pt(-26.5, -41.5892, 1000, { .minSpeed = 1, .earlyExitRange = 1 });
        swing2pt(-39.0941, -42.5, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        mv2pt(-39.0941, -42.5, 1000, { .maxSpeed = 90, .minSpeed = 1, .earlyExitRange = 1 });
        conn2hd(0, 1000);
        mv2pt(-35.832, -32.5801, 1000, { .minSpeed = 1, .earlyExitRange = 1 });

        // get corner
        conn2pt(-51.2501, 2.05019, 1000, { .minSpeed = 20, .earlyExitRange = 3 });
        ms2pt(-51.2501, 2.05019, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        bigArm.set_target(posToScore);
        swing2hd(-45, lemlib::DriveSide::LEFT, 500, { .minSpeed = 40, .earlyExitRange = 3 });
        cornerMacro();

        // get mid ring
        conn2pt(-6, -2, 1000);
        toggleIntakeLift();
        mv2pt(-6, -2, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        mv2pt(3.02053, -2.6028, 1000, { .maxSpeed = 20, .minSpeed = 15, .earlyExitRange = 1 });

        // touch bar
        bigArm.set_target(25100);
        turn2pt(6, -17.5191, 500);
        mv2pt(6, -17.5191, 1000, { .minSpeed = 1, .earlyExitRange = 2.5 });
    }

    void pos_grush() {

    }

    void posRingsReused() {
        turn2pt(-7, -38, 600);
        mv2pt(-7, -38, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        toggleFrontLeftArm();
        mv2pt(-7, -38, 250);

        drWait(0.4, 0.4, -1);
        swing2hd(-153, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        toggleFrontRightArm();
        drWait(0.4, 0.4, 2);
        drive_chass(0, 0);

        // back up to align 3 in a row
        mv2pt(11.5621, -6.63123, 1000, { .forwards = false, .minSpeed = 1,.earlyExitRange = 20 });
        mv2pt(11.5621, -6.63123, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontRightArm();
        toggleFrontLeftArm();
        mv2pt(11.5621, -6.63123, 250, { .forwards = false, .maxSpeed = 60 });

        // get 3 in a row
        turn2pt(2.79039, -11.4024, 1000, { .minSpeed = 15, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(2.79039, -11.4024, 450, { .minSpeed = 1, .earlyExitRange = 1 });
        swing2pt(27.4559, -28.6077, lemlib::DriveSide::LEFT, 1000, { .maxSpeed = 80,.minSpeed = 1,.earlyExitRange = 2 });
        mv2pt(27.4559, -28.6077, 1000, { .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });

        // get corner
        toggleFrontLeftArm();
        swing2pt(41.6484, -1, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        toggleFrontLeftArm();
        mv2pt(41.6484, -1, 1000, { .minSpeed = 1, .earlyExitRange = 2 });
        bigArm.set_target(posToScore);
        swing2hd(-315, lemlib::DriveSide::RIGHT, 500, { .minSpeed = 30, .earlyExitRange = 4 });
        cornerMacro();

        // touch bar
        drWait(0.4, 0.4, -2);
        swconn2hd(180, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 40, .earlyExitRange = 30 });
        spin_intk(0);
        toggleGoalClamp();
        swconn2hd(180, lemlib::DriveSide::LEFT, 250, { .minSpeed = 40 });
        bigArm.set_target(25100);
        mv2pt(5.80181, -26.0871, 1000, { .maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 4 });
        getChass()->setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
        getChass()->arcade(0, 0);
    }

    void pos5_1() {
        leftAlli_Mogo();

        posRingsReused();
    }

    void pos6() {
        leftMogo();

        // first ring
        turn2pt(-7.74108, -43.1909, 500);
        mv2pt(-7.74108, -43.1909, 1000, { .minSpeed = 1, .earlyExitRange = 8 });
        toggleFrontLeftArm();
        mv2pt(-7.74108, -43.1909, 250);

        // second ring
        swing2hd(-153.494, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        toggleFrontRightArm();
        drWait(0.3, 0.3, 1);
        drive_chass(0, 0);

        // back up to align 3 in a row
        mv2pt(14.9879, -2.60653, 1000, { .forwards = false, .minSpeed = 1,.earlyExitRange = 10 });
        mv2pt(14.9879, -2.60653, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 1 });
        toggleFrontRightArm();
        toggleFrontLeftArm();
        mv2pt(14.9879, -2.60653, 250, { .forwards = false, .maxSpeed = 60 });

        // get 3 in a row
        turn2pt(5.6822, -8.22241, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(5.6822, -8.22241, 1000, { .minSpeed = 1, .earlyExitRange = 1.5 });
        swing2pt(33.6738, -29.8087, lemlib::DriveSide::LEFT, 1000, { .maxSpeed = 80,.minSpeed = 1,.earlyExitRange = 2 });
        mv2pt(33.6738, -29.8087, 1000, { .maxSpeed = 80, .minSpeed = 1, .earlyExitRange = 1 });

        // get corner
        swing2pt(43.0299, -1.5, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 1, .earlyExitRange = 5 });
        toggleIntakeLift();
        mv2pt(43.0299, -1.5, 1000, { .minSpeed = 1, .earlyExitRange = 1 });
        bigArm.set_target(posToScore);
        swing2hd(48, lemlib::DriveSide::RIGHT, 500, { .minSpeed = 30, .earlyExitRange = 4 });
        cornerMacro();

        // clear corner
        toggleFrontLeftArm();
        ms2pt(37.5865, -1.50236, 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 1 });
        drWait(0.4, 0.4, 1);
        turn2hd(80, 500, { .direction = lemlib::AngularDirection::CW_CLOCKWISE, .minSpeed = 126, .earlyExitRange = 10 });
        toggleFrontLeftArm();
        drWait(0.4, 0.4, -1);
        turn2hd(-135, 1000, { .minSpeed = 1, .earlyExitRange = 20 });
        toggleGoalClamp();
        turn2hd(-135, 250);
        drWait(0.3, 0.3, -2);
        drWait(0.6, 0.6, -4);
        drWait(0.8, 0.8, -3);
        drive_chass(0, 0);
        pros::delay(100);
        mv2pt(29.433, -8.10289, 1000, { .minSpeed = 1, .earlyExitRange = 3 });
        turn2hd(0, 1000);
    }
}