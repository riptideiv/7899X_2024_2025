#pragma once
#include "main.h"

using bot::bigArm, bot::toggleFrontLeftArm, bot::toggleGoalClamp, bot::drive_chass;

namespace auton {
    void printPose() {
        printf("Pose: %f %f %f\n", bot::getPose().x, bot::getPose().y, bot::getPose().theta);
    }

    /**
     * use for moving to a point.
     */
    void mv2pt(double x, double y, double timeout, lemlib::MoveToPointParams params = {}, bool async = false) {
        bot::moveToPoint(x, y, timeout, params, async);
    }

    /**
     * move straight to point
     * same as mv2pt but uses the lateral-only chassis. recommended to use .minSpeed and .earlyExitRange so the chassis doesn't tweak out when it reaches the target. also recommended to use near the beginning of auton routes, since this one can't autocorrect for errors caused by previous interference/inconsistency.
     */
    void ms2pt(double x, double y, double timeout, lemlib::MoveToPointParams params = {}, bool async = false) {
        bot::straight_chass[bot::MOGO]->moveToPoint(x, y, timeout, params, async);
    }

    /**
     * move to a position with specified ending angle
     */
    void mv2pose(double x, double y, double theta, double timeout, lemlib::MoveToPoseParams params = {}, bool async = false) {
        bot::moveToPose(x, y, theta, timeout, params, async);
    }

    /**
     * turn to a specified ANGLE in place
     */
    void turn2hd(double theta, double timeout, lemlib::TurnToHeadingParams params = {}, bool async = false) {
        bot::turnToHeading(theta, timeout, params, async);
    }
    void conn2hd(double theta, double timeout, lemlib::TurnToHeadingParams params = { .minSpeed = 10, .earlyExitRange = 2 }, bool async = false) {
        bot::connecting_chass[bot::MOGO]->turnToHeading(theta, timeout, params, async);
    }

    /**
     * turn in place to face a specified POINT
     */
    void turn2pt(double x, double y, double timeout, lemlib::TurnToPointParams params = {}, bool async = false) {
        bot::turnToPoint(x, y, timeout, params, async);
    }
    void conn2pt(double x, double y, double timeout, lemlib::TurnToPointParams params = { .minSpeed = 10, .earlyExitRange = 2 }, bool async = false) {
        bot::connecting_chass[bot::MOGO]->turnToPoint(x, y, timeout, params, async);
    }

    void swconn2pt(double x, double y, lemlib::DriveSide side, double timeout, lemlib::SwingToPointParams params = { .minSpeed = 10, .earlyExitRange = 3 }, bool async = false) {
        bot::connecting_chass[bot::MOGO]->swingToPoint(x, y, side, timeout, params, async);
    }

    void swconn2hd(double theta, lemlib::DriveSide side, double timeout, lemlib::SwingToHeadingParams params = { .minSpeed = 10, .earlyExitRange = 3 }, bool async = false) {
        bot::connecting_chass[bot::MOGO]->swingToHeading(theta, side, timeout, params, async);
    }

    /**
     *
     */
    void drWait(double lMult, double rMult, double dist) {
        bot::driveWait(lMult, rMult, dist);
    }

    void swing2pt(double x, double y, lemlib::DriveSide side, double timeout, lemlib::SwingToPointParams params = {}, bool async = false) {
        bot::getChass()->swingToPoint(x, y, side, timeout, params, async);
    }

    void swing2hd(double theta, lemlib::DriveSide side, double timeout, lemlib::SwingToHeadingParams params = {}, bool async = false) {
        bot::getChass()->swingToHeading(theta, side, timeout, params, async);
    }
}

namespace auton {
    using namespace bot;
    void leftAlli_Mogo() {
        bigArm.set_target(28800);
        bigArm.maxSpeed = 80;
        ms2pt(-17, 22, 1000, { .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 20 });
        pros::delay(400);
        mv2pt(7.0848, -25.4775, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 20 });
        bigArm.maxSpeed = 100;
        bigArm.reset();
        drWait(0, 0.6, -3);
        mv2pt(7.0848, -27.5, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 18 });
        mv2pt(7.0848, -27.5, 1000, { .forwards = false, .maxSpeed = 40, .minSpeed = 1, .earlyExitRange = 5 });
        toggleGoalClamp();
        mv2pt(7.0848, -27.5, 300, { .forwards = false });
    }

    void leftMogo() {
        drWait(0.6, 0, -1);
        mv2pt(5.12525, -24.3281, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 14 });
        mv2pt(5.12525, -24.3281, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 1, .earlyExitRange = 4 });
        toggleGoalClamp();
        mv2pt(5.12525, -24.3281, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 1, .earlyExitRange = 3 });
        intake.mtr->set_zero_position(0);
        spin_intk(100);
        drWait(0.25, 0.25, -2);
        drive_chass(0, 0);
        while (intake.mtr->get_position() < 160) pros::delay(3);
        spin_intk(0);
    }

    void rightAlli_Mogo() {
        bigArm.set_target(28800);
        bigArm.maxSpeed = 80;
        ms2pt(17, 22, 1000, { .maxSpeed = 60, .minSpeed = 1, .earlyExitRange = 19.75 });
        pros::delay(400);
        mv2pt(-7.0848, -25.4775, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 20 });
        bigArm.maxSpeed = 100;
        bigArm.reset();
        drWait(0.6, 0, -2);
        mv2pt(-7.0848, -24.5, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 16 });
        mv2pt(-7.0848, -24.5, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 1, .earlyExitRange = 5 });
        toggleGoalClamp();
        drWait(0.25, 0.25, -2);
        drive_chass(0, 0);
    }

    void rightMogo() {
        drWait(0, 0.6, -1);
        mv2pt(-5.12525, -24.3338, 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 14 });
        mv2pt(-5.12525, -24.3338, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 1, .earlyExitRange = 4 });
        toggleGoalClamp();
        mv2pt(-5.12525, -24.3338, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 1, .earlyExitRange = 3 });
        intake.mtr->set_zero_position(0);
        spin_intk(100);
        drWait(0.25, 0.25, -2);
        drive_chass(0, 0);
        while (intake.mtr->get_position() < 160) pros::delay(3);
        spin_intk(0);
    }

    void cornerMacro() {
        spin_intk(100);
        drive_chass(40, 40);
        intake.mtr->set_zero_position(0);
        intake.confirmThrow = true;
        for (int i = 0; i < 800; i += 3) {
            pros::delay(3);
            if (colorSortSensor.get_proximity() > 200) {
                pros::delay(400);
                break;
            }
        }
        drive_chass(0, 0);
        pros::delay(50);
        double ox = getPose().x;
        double oy = getPose().y;
        double otheta = getPose().theta / 180.0 * M_PI;
        ms2pt(ox - 9 * sin(otheta), oy - 9 * cos(otheta), 1000, { .forwards = false, .minSpeed = 1, .earlyExitRange = 2 });
        toggleIntakeLift();
        ms2pt(ox - 8 * sin(otheta), oy - 8 * cos(otheta), 750, { .forwards = false });
        drive_chass(40, 40);
        pros::delay(700);
        drive_chass(0, 0);
        ms2pt(ox - 9 * sin(otheta), oy - 9 * cos(otheta), 1000, { .forwards = false, .minSpeed = 10, .earlyExitRange = 3 });
    }
}