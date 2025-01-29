#pragma once

// #define mv2pt bot::moveToPoint

// #define mv2pose bot::moveToPose

// #define turn2hd bot::turnToHeading

// #define turn2pt bot::turnToPoint

namespace auton {
    void printPose() {
        printf("Pose: %f %f %f\n", bot::getPose().x, bot::getPose().y, bot::getPose().theta);
    }

    void mv2pt(double x, double y, double timeout, lemlib::MoveToPointParams params = {}, bool async = false) {
        bot::moveToPoint(x, y, timeout, params, async);
    }

    void mv2pose(double x, double y, double theta, double timeout, lemlib::MoveToPoseParams params = {}, bool async = false) {
        bot::moveToPose(x, y, theta, timeout, params, async);
    }

    void turn2hd(double theta, double timeout, lemlib::TurnToHeadingParams params = {}, bool async = false) {
        bot::turnToHeading(theta, timeout, params, async);
    }

    void turn2pt(double x, double y, double timeout, lemlib::TurnToPointParams params = {}, bool async = false) {
        bot::turnToPoint(x, y, timeout, params, async);
    }

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