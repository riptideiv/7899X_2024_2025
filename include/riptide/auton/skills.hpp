#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace bot;

namespace auton {
    void corner1() {
        int start; // used for wall stake timing

        bigArm.reset();

        // alliance stake
        intake.mtr->set_zero_position(0);
        spin_intk(100);
        double distAvg = 0;
        for (int i = 0; i < 5; i++) {
            distAvg += mogoDist.get();
            pros::delay(5);
        }
        while (intake.mtr->get_position() < 520) pros::delay(3);
        pros::delay(50);
        spin_intk(-50);
        getChass()->setPose(0, (distAvg / 5 - 130) * 0.0393701, 0);

        // get mogo
        mv2pt(0, 11, 1000, { .minSpeed = 15, .earlyExitRange = 3 });

        spin_intk(0);
        turn2pt(20.6659, 12.5, 600, { .forwards = false });
        toggleFrontRightArm(); // expand the aligner
        mv2pt(20.6659, 12.5, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 30, .earlyExitRange = 12 });
        mv2pt(20.6659, 12.5, 1000, { .forwards = false, .maxSpeed = 40, .minSpeed = 30, .earlyExitRange = 3 });
        toggleGoalClamp();
        pros::delay(250);
        toggleFrontRightArm();

        // first 3 rings
        swing2pt(33, 51.8996, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 60, .earlyExitRange = 4 });
        spin_intk(100);
        mv2pt(32, 51.8996, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        drWait(0.2, 0.7, 0.25);
        mv2pt(41.5717, 79.9639, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        swing2pt(57, 100, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 50, .earlyExitRange = 5 });
        mv2pt(53, 109, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        bigArm.toggleUp();

        // ring pickup + 1st wall stake ring
        turn2pt(37.5, 70, 1000, { .forwards = false, .minSpeed = 50, .earlyExitRange = 1.5 });
        mv2pt(37, 70, 2000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 3 });
        spin_intk(0);
        turn2pt(63, 64, 1000, { .minSpeed = 1, .earlyExitRange = 20 });
        bigArm.raise(); // posToScore
        turn2pt(63, 64, 250);
        spin_intk(100);
        mv2pt(63, 64, 1000, { .minSpeed = 20, .earlyExitRange = 7 });
        drive_chass(20, 20);
        pros::delay(50);
        spin_intk(0);
        bigArm.set_target(18000);
        bigArm.kP = 2.5;
        start = pros::millis();
        while (pros::millis() - start < 700 && bigArm.rotation->get_position() > 19450) pros::delay(3);

        // second wall stake ring
        drWait(0.7, 0.7, -6);
        bigArm.toggleUp();
        drWait(0.4, 0.4, -2);
        spin_intk(-30);
        turn2pt(67, 64, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        mv2pt(63, 64, 1000, { .minSpeed = 20, .earlyExitRange = 11 });
        spin_intk(100);
        intake.stuckFor = 0;
        mv2pt(63, 64, 1000, { .minSpeed = 20, .earlyExitRange = 7 });
        start = pros::millis();
        pros::delay(50);
        while (pros::millis() - start < 600 && intake.stuckFor < 50) pros::delay(3);
        spin_intk(0);
        pros::delay(20);
        bigArm.set_target(18000);
        bigArm.kP = 2.5;
        drive_chass(20, 20);
        start = pros::millis();
        while (pros::millis() - start < 600 && bigArm.rotation->get_position() > 19450) pros::delay(3);

        // use wall stake to reset position
        double theta = getChass()->getPose().theta * M_PI / 180;
        double x = 63 - 11 * std::sin(theta);
        double y = 65 - 11 * std::cos(theta);
        getChass()->setPose(x, y, getChass()->getPose().theta);

        // 3 rings in a row
        spin_intk(100);
        drWait(0.7, 0.7, -6);
        // mv2pt(42, 66, 1000, { .forwards = false,.minSpeed = 80,.earlyExitRange = 4 });
        bigArm.toggleUp();

        turn2pt(41.5997, 45.2527, 1000, { .minSpeed = 30, .earlyExitRange = 1.5 });
        mv2pt(41.5997, 45.2527, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        bigArm.reset();
        swing2pt(42, 6.34163, lemlib::DriveSide::RIGHT, 1000, { .minSpeed = 50, .earlyExitRange = 4 });
        mv2pt(42, 6.34163, 1000, { .maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 26 });
        mv2pt(42, 6.34163, 1000, { .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 1 });

        intake.mtr->set_zero_position(0);
        spin_intk(100);
        while (intake.mtr->get_position() < 450) pros::delay(3);

        // final mogo ring & place mogo into corner
        spin_intk(0);
        turn2pt(53.3294, 18, 1000, { .minSpeed = 35, .earlyExitRange = 5 });
        spin_intk(100);
        turn2pt(53.3294, 18, 1000, { .minSpeed = 35, .earlyExitRange = 2 });
        mv2pt(57.0917, 28, 1000, { .minSpeed = 40, .earlyExitRange = 5 });
        mv2pt(57.0917, 28, 150);
        turn2pt(58, 8, 1000, { .forwards = false, .minSpeed = 50, .earlyExitRange = 3 });
        mv2pt(63, 8, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 9 });
        spin_intk(0);
        toggleGoalClamp();
        mv2pt(63, 8, 300, { .forwards = false, .maxSpeed = 50, .minSpeed = 30 });
        spin_intk(-30);

        // reset for next part
        drWait(0.8, 0.8, 2.2);
        drWait(1, -1, 2);
        turn2hd(90, 1000, { .maxSpeed = 50, .minSpeed = 50, .earlyExitRange = 40 });

        // // DEBUG CODE
        // drive_chass(55, 55);
        // pros::delay(250);
        // drive_chass(30, 30);
        // while (drivetrain->leftMotors->get_actual_velocity() > 15 || drivetrain->rightMotors->get_actual_velocity() > 15) pros::delay(3);
        // spin_intk(0);
        // drive_chass(0, 0);
    }

    void corner2() {
        drive_chass(55, 55);
        pros::delay(250);
        drive_chass(30, 30);
        while (drivetrain->leftMotors->get_actual_velocity() > 15 || drivetrain->rightMotors->get_actual_velocity() > 15) pros::delay(3);
        spin_intk(0);
        drive_chass(0, 0);
        getChass()->setPose(0, 0, getChass()->getPose().theta);
        drWait(0.62, 0.6, -10);
        double distAvg = 0;
        for (int i = 0; i < 5; i++) {
            distAvg += rWallDist.get();
            pros::delay(5);
        }
        double x = getChass()->getPose().x;
        double theta = getChass()->getPose().theta;
        double y = -0.400964 + (distAvg / 5 - 444) * 0.0393701;
        getChass()->setPose(x, y, theta);

        mv2pt(-66.282, -3.35281, 5000, { .forwards = false, .maxSpeed = 80, .minSpeed = 30, .earlyExitRange = 0.5 });
        turn2pt(-90.0252, -4, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 1 });
        mv2pt(-90.0252, -4, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 2 });
        toggleGoalClamp();
        pros::delay(250);

        // first 3 rings
        swing2pt(-107.733, 39.1538, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 60, .earlyExitRange = 4 });
        spin_intk(100);
        mv2pt(-107.733, 41.1538, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        drWait(0.7, 0.2, 0.35);
        mv2pt(-118.145, 69.1572, 1000, { .minSpeed = 50, .earlyExitRange = 2 });
        swing2pt(-134.891, 91, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 50, .earlyExitRange = 4 });
        mv2pt(-134.891, 94, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        bigArm.toggleUp();

        // ring pickup + 1st wall stake ring
        turn2pt(-113.315, 48, 1000, { .forwards = false, .minSpeed = 50, .earlyExitRange = 1.5 });
        mv2pt(-113.315, 48, 2000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 3 });
        spin_intk(0);
        turn2pt(-141, 42, 1000, { .minSpeed = 1, .earlyExitRange = 20 });
        bigArm.raise(); // posToScore
        turn2pt(-141, 42, 250);
        spin_intk(100);
        mv2pt(-141, 42, 600, { .minSpeed = 20, .earlyExitRange = 4 });
        drive_chass(20, 20);
        pros::delay(100);
        bigArm.set_target(18000);
        bigArm.kP = 2.5;
        int start = pros::millis();
        pros::delay(50);
        spin_intk(0);
        while (pros::millis() - start < 400 && bigArm.rotation->get_position() > 19450) pros::delay(3);

        // second wall stake ring
        drWait(0.7, 0.7, -6);
        bigArm.toggleUp();
        drWait(0.4, 0.4, -2);
        spin_intk(-30);
        mv2pt(-141, 42, 1000, { .minSpeed = 20, .earlyExitRange = 8 });
        spin_intk(100);
        intake.stuckFor = 0;
        mv2pt(-141, 42, 1000, { .minSpeed = 20, .earlyExitRange = 4 });
        start = pros::millis();
        pros::delay(200);
        while (pros::millis() - start < 600 && intake.stuckFor < 50) pros::delay(3);
        spin_intk(0);
        pros::delay(20);
        bigArm.set_target(18000);
        bigArm.kP = 2.5;
        drive_chass(20, 20);
        start = pros::millis();
        while (pros::millis() - start < 600 && bigArm.rotation->get_position() > 19450) pros::delay(3);

        // use wall stake to reset position
        theta = getChass()->getPose().theta * M_PI / 180;
        x = -143.115 - 11 * std::sin(theta);
        y = 45.8281 - 11 * std::cos(theta);
        getChass()->setPose(x, y, getChass()->getPose().theta);

        // 3 rings in a row
        spin_intk(100);

        driveWait(0.7, 0.7, -6);
        bigArm.toggleUp();

        turn2pt(-113.5, 21, 1000, { .minSpeed = 30, .earlyExitRange = 1 });
        mv2pt(-113.5, 21, 1000, { .minSpeed = 30, .earlyExitRange = 4 });
        bigArm.reset();
        mv2pt(-113.5, 21, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        swing2pt(-113.5, -16.7421, lemlib::DriveSide::LEFT, 1000, { .minSpeed = 50, .earlyExitRange = 4 });
        mv2pt(-113.5, -16.7421, 1000, { .maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 26 });
        mv2pt(-113.5, -16.7421, 1000, { .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 2 });

        intake.mtr->set_zero_position(0);
        spin_intk(100);
        while (intake.mtr->get_position() < 450) pros::delay(3);

        // final mogo ring & place mogo into corner
        spin_intk(0);
        turn2pt(-127.618, -9, 1000, { .minSpeed = 40, .earlyExitRange = 5 });
        spin_intk(100);
        turn2pt(-127.618, -9, 1000, { .minSpeed = 40, .earlyExitRange = 2 });
        mv2pt(-129.885, 5, 1000, { .minSpeed = 40, .earlyExitRange = 6 });
        mv2pt(-129.885, 5, 50);
        turn2pt(-128, -20, 1000, { .forwards = false, .minSpeed = 60, .earlyExitRange = 3 });
        mv2pt(-134, -20, 1000, { .forwards = false, .maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 8 });
        spin_intk(0);
        toggleGoalClamp();
        mv2pt(-136, -20, 300, { .forwards = false, .maxSpeed = 50, .minSpeed = 30 });
        spin_intk(-30);

        // reset for next part
        // drWait(1, 0, 2);
        mv2pt(-120, 8.70515, 1000, { .minSpeed = 50, .earlyExitRange = 3 });
    }

    void blueCorner() {
        turn2hd(0, 1000, { .minSpeed = 30, .earlyExitRange = 1 });
        turn2hd(0, 800, {}, true);
        pros::delay(700);
        double distAvgL = 0, distAvgBack = 0;
        for (int i = 0; i < 5; i++) {
            distAvgL += lWallDist.get();
            distAvgBack += mogoDist.get();
            pros::delay(5);
        }
        distAvgL /= 5;
        distAvgBack /= 5;
        double x = 2 + (distAvgL - 489) * 0.0393701;
        double y = 2 + (distAvgBack - 752) * 0.0393701;
        double theta = getChass()->getPose().theta;
        getChass()->setPose(x, y, theta);

        // get ring into LB
        spin_intk(100);
        mv2pt(0.423706, 87, 1500, { .minSpeed = 1, .earlyExitRange = 24 });
        bigArm.toggleUp();
        mv2pt(0.423706, 87, 1000, { .maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 5 });

        // get blue mogo
        turn2pt(20.4076, 97.3289, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        mv2pt(20.4076, 97.3289, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 12 });
        mv2pt(20.4076, 97.3289, 1000, { .forwards = false, .maxSpeed = 40, .minSpeed = 30, .earlyExitRange = 7 });
        spin_intk(0);
        toggleGoalClamp();
        pros::delay(250);

        // clear corner & insert mogo
        turn2hd(-89, 1000, { .minSpeed = 40, .earlyExitRange = 5 });
        toggleFrontRightArm();
        mv2pt(-12, 102.324, 1000, { .minSpeed = 40, .earlyExitRange = 8 });
        turn2hd(-223.195, 2000, { .minSpeed = 126, .earlyExitRange = 40 });
        toggleFrontRightArm();
        turn2hd(-223.195, 150);
        toggleGoalClamp();
        drive_chass(-70, -70);
        pros::delay(300);
        drive_chass(-20, -20);
        pros::delay(250);

        // grab empty mogo
        mv2pt(0, 90, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        bigArm.raise();
        turn2pt(33, 87.5, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });
        spin_intk(-100);
        mv2pt(33, 87.5, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 4 });
        mv2pt(49, 87.5, 1000, { .forwards = false, .maxSpeed = 40, .minSpeed = 30, .earlyExitRange = 2 });
        toggleGoalClamp();
        pros::delay(150);

        // set up to score alliance stake
        turn2pt(49, 109, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        spin_intk(0);
        mv2pt(49, 109, 1000, { .minSpeed = 30, .earlyExitRange = 14 });
    }

    void blueAlliStake_finalMogo() {
        // reset odom & score allliance stake
        drive_chass(35, 35);
        pros::delay(400);
        double theta = getChass()->getPose().theta * M_PI / 180;
        double x = -8 * std::sin(theta);
        double y = -8 * std::cos(theta) + 0.5;
        double targx = -17 * std::sin(theta);
        double targy = -17 * std::cos(theta) + 0.5;
        getChass()->setPose(x, y, getChass()->getPose().theta);
        mv2pt(targx, targy, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 7 });
        bigArm.set_target(14300);
        bigArm.kP = 5;
        bigArm.setMaxSpeed(60);
        mv2pt(targx, targy, 800, {}, true);
        while (getChass()->isInMotion() && bigArm.rotation->get_position() > 17191) pros::delay(3);
        getChass()->cancelAllMotions();
        pros::delay(10);
        drWait(0.9, 1, -2.5);
        bigArm.raise();
        bigArm.setMaxSpeed(100);
        drive_chass(0, 0);

        // 1st ring
        spin_intk(100);
        turn2pt(-27, -37.5, 1000, { .minSpeed = 50, .earlyExitRange = 5 });
        mv2pt(-23.9233, -50.5, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        bigArm.reset();

        // 2nd ring (under tower)
        turn2pt(3, -74, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(3, -74, 1000, { .minSpeed = 30, .earlyExitRange = 26 });
        spin_intk(0);
        mv2pt(3, -74, 1000, { .minSpeed = 30, .earlyExitRange = 8 });
        spin_intk(100);
        mv2pt(3, -74, 1000, { .minSpeed = 30, .earlyExitRange = 2 });

        // 3rd, 4th, 5th
        turn2pt(26.9951, -48.501, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(26.9951, -48.501, 1000, { .minSpeed = 30, .earlyExitRange = 23 });
        spin_intk(0);
        mv2pt(26.9951, -48.501, 1000, { .minSpeed = 30, .earlyExitRange = 8 });
        spin_intk(100);
        mv2pt(26.9951, -48.501, 1000, { .minSpeed = 40, .earlyExitRange = 2 });
        turn2pt(49.8712, -24.8684, 1000, { .minSpeed = 50, .earlyExitRange = 3 });
        mv2pt(49.8712, -24.8684, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        turn2pt(49, -11.5, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(49, -11.5, 1000, { .minSpeed = 30, .earlyExitRange = 1 });

        // back up, clear corner, insert mogo
        turn2pt(61.0081, -38, 1000, { .forwards = false, .minSpeed = 70, .earlyExitRange = 10 });
        mv2pt(61.0081, -38, 1000, { .forwards = false, .minSpeed = 50, .earlyExitRange = 3 });
        turn2pt(63, -17.0656, 1000, { .minSpeed = 50, .earlyExitRange = 2 });
        toggleFrontRightArm();
        mv2pt(62.5779, -17.0656, 1000, { .minSpeed = 40, .earlyExitRange = 4 });
        turn2hd(-505.049, 2000, { .minSpeed = 126, .earlyExitRange = 40 });
        toggleFrontRightArm();
        turn2hd(-505.049, 200);
        toggleGoalClamp();
        drive_chass(-70, -70);
        spin_intk(0);
        pros::delay(300);
        drive_chass(-20, -20);
        pros::delay(250);
        spin_intk(-30);

        // hang
        drWait(1, 1, 2);
        spin_intk(-100);
        turn2pt(32.1317, -40, 1000, { .forwards = false, .minSpeed = 35, .earlyExitRange = 2 });
        bigArm.raise();
        mv2pt(32.1317, -40, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 0.5 });
        turn2hd(45, 1000, { .minSpeed = 30, .earlyExitRange = 1 });
        spin_intk(0);
        const double kP = 2.5;
        const double chass_rpm = 600;
        const double targ_spdPct = -0.39 * chass_rpm;
        while (1) {
            double error = targ_spdPct - getChassVelo();
            double chassPower = error * kP + targ_spdPct;
            chassPower = chassPower / chass_rpm * 100;
            drive_chass(chassPower, chassPower);
            pros::delay(5);
        }
        pros::delay(2000);
    }

    void autonSkills() {
        intake.set_colorsort(1, 1);
        intake.doAntiStuck = true;

        // // debug (setup) code for clamping mogo before running
        // toggleGoalClamp();
        // pros::delay(200);

        corner1();

        corner2();

        blueCorner();

        blueAlliStake_finalMogo();


    }
}