#include "main.h"

double xrobot::prevL, xrobot::prevR, xrobot::prevS, xrobot::prevAngle, xrobot::odomX, xrobot::odomY;

pros::Task *xrobot::odomTask;

void xrobot::updatePos(bool log) {
    if (isnan(odomX) || isnan(odomY)) {
        odomX = 0;
        odomY = 0;
        // printf("RESET+++++++++++++++++");
    }
    double currL = get_avg_pos(left_mg),
        currR = get_avg_pos(right_mg),
        currS = horizTracker.get_position() / 100.0, // it's in degrees now
        currAngle = xrobot::get_rotation() / 180.0 * M_PI; // because it's in degrees and we want radians
    double dL = currL - prevL,
        dR = currR - prevR,
        dS = currS - prevS,
        dAngle = currAngle - prevAngle;

    prevL = currL;
    prevR = currR;
    prevS = currS;
    prevAngle = currAngle;
    double dX, dY;
    if (fabs(dAngle) < 0.05) {
        dX = dS;
        dY = (dL + dR) / 2;
    } else {
        dX = (2 * sin(dAngle / 2)) * (dS / dAngle + constants.hWheelOffset);
        dY = (2 * sin(dAngle / 2)) * ((dL + dR) / 2 / dAngle + constants.lWheelOffset);
    }

    // convert to polar coords and then adjust back for global
    double r = sqrt(dX * dX + dY * dY);
    double theta = atan2(dY, dX) - currAngle;

    odomX += r * cos(theta);
    odomY += r * sin(theta);
    if (log) {
        /********
         * Prints in table format
         */
         // printf("currAngle: %.2f\n", currAngle);

         /********
          * Prints in json format, compatible for show_odom_from_log.py
          */
        printf("{\"currL\": %.2f, \"currR\": %.2f, \"currS\": %.2f, \"currAngle\": %.2f, ", currL, currR, currS, currAngle);
        printf("\"dL\": %.2f, \"dR\": %.2f, \"dS\": %.2f, \"dAngle\": %.2f, ", dL, dR, dS, dAngle);
        printf("\"dX\": %.2f, \"dY\": %.2f, ", dX, dY);
        printf("\"r\": %.2f, \"theta\": %.2f, ", r, theta);
        printf("\"odomX\": %.2f, \"odomY\": %.2f}\n", odomX, odomY);
    }
}

void updatePosLoop(void) {
    for (int i = 0;;i = (i + 1) % 15) {
        xrobot::updatePos(!i);
        pros::delay(10);
    }
}

void xrobot::initTracking() {
    horizTracker.reset_position();
    odomTask = new pros::Task(updatePosLoop, "Odometry Task");
}