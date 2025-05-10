#pragma once

#include "main.h"

namespace bot {
    pros::Distance mogoDist(18);
    pros::Distance rWallDist(14);
    pros::Distance lWallDist(16);
    pros::Distance intakeDist(5);

    pros::IMU *imu;

    pros::Rotation *horizTrackRotSensor;
    lemlib::TrackingWheel *horizTrack[2]; // 0 = no mogo, 1 = mogo

    const double odomOffset[2] = { -2.3125, -0.0625 };

    pros::Optical colorSortSensor(17);

    lemlib::OdomSensors *odomSensors[2]; // 0 = no mogo, 1 = mogo

    void init_sensors() {
        imu = new pros::IMU(10);

        horizTrackRotSensor = new pros::Rotation(15);
        horizTrackRotSensor->set_reversed(true);
        horizTrack[0] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, odomOffset[0]);
        // -5.25
        horizTrack[1] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, odomOffset[1]);

        odomSensors[0] = new lemlib::OdomSensors(nullptr, nullptr, horizTrack[0], nullptr, imu);
        odomSensors[1] = new lemlib::OdomSensors(nullptr, nullptr, horizTrack[1], nullptr, imu);

        // odomSensors[0] = new lemlib::OdomSensors(nullptr, nullptr, nullptr, nullptr, imu);
        // odomSensors[1] = new lemlib::OdomSensors(nullptr, nullptr, nullptr, nullptr, imu);
    }

    bool mogoInRange(int range = 58) {
        return mogoDist.get() <= range;
    }
}