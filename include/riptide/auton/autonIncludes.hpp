#pragma once
#include "main.h"

using bot::bigArm, bot::toggleFrontLeftArm, bot::toggleGoalClamp, bot::drive_chass;

namespace auton {
    void printPose() {
        printf("Pose: %f %f %f\n", bot::getPose().x, bot::getPose().y, bot::getPose().theta);
    }

    /**
     * use for moving to a point. recomend to use when moving straight.
     */
    void mv2pt(double x, double y, double timeout, lemlib::MoveToPointParams params = {}, bool async = false) {
        bot::moveToPoint(x, y, timeout, params, async);
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

namespace auton {
    void rightSideAlli(int speed = 70) {
        // score alliance stake
        bigArm.setMaxSpeed(speed);
        bigArm.set_target(14300);
        int start = pros::millis();
        mv2pt(10.8389, 6.83514, 1000, { .maxSpeed = 40, .minSpeed = 20, .earlyExitRange = 5 });
        while (pros::millis() - start < 1000 && bigArm.rotation->get_position() > 17850) pros::delay(3);
        pros::delay(150 * 70.0 / speed);
        drWait(0.6, 0.6, -2);
        bigArm.reset();
        bigArm.raise();
        drive_chass(0, 0);
    }

    void rightSideGoal() {
        // get mogo
        swing2pt(-5.60366, -29.6529, lemlib::DriveSide::RIGHT, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 3 });
        mv2pt(-7, -29.6529, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 15 });
        toggleFrontLeftArm();
        mv2pt(-6, -29.6529, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 5 });
        toggleGoalClamp();
        toggleFrontLeftArm();
        mv2pt(-6, -29.6529, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 4 });
    }

    void leftSideAlli(int speed = 70) {
        // score alli stake
        bigArm.setMaxSpeed(speed);
        bigArm.set_target(14300);
        int start = pros::millis();
        mv2pt(-11.0571, 5.9038, 1000, { .minSpeed = 20, .earlyExitRange = 5 });
        while (pros::millis() - start < 1000 && bigArm.rotation->get_position() > 17850) pros::delay(3);
        pros::delay(150 * 70.0 / speed);
        drWait(0.6, 0.6, -2);
        bigArm.reset();
        bigArm.raise();
        drive_chass(0, 0);
    }

    void leftSideGoal() {
        // get mogo
        swing2pt(7.5, -29.1135, lemlib::DriveSide::LEFT, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 3 });
        mv2pt(7.5, -29.1135, 1000, { .forwards = false, .maxSpeed = 60, .minSpeed = 25, .earlyExitRange = 15 });
        toggleFrontLeftArm();
        mv2pt(8.7195, -29.1135, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 5 });
        toggleFrontLeftArm();
        toggleGoalClamp();
        mv2pt(8.7195, -29.1135, 1000, { .forwards = false, .maxSpeed = 30, .minSpeed = 20, .earlyExitRange = 4 });
    }
}