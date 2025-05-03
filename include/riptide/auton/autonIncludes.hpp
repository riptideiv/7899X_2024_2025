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
        bot::chass[2]->moveToPoint(x, y, timeout, params, async);
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

    /**
     * turn in place to face a specified POINT
     */
    void turn2pt(double x, double y, double timeout, lemlib::TurnToPointParams params = {}, bool async = false) {
        bot::turnToPoint(x, y, timeout, params, async);
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