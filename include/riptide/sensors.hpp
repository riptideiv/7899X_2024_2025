#pragma once

#include "main.h"

namespace bot {
    pros::Distance mogoDist(18);
    pros::Distance rWallDist(15);
    pros::Distance lWallDist(16);
    pros::Distance intakeDist(5);

    pros::IMU *imu;

    pros::Rotation *horizTrackRotSensor;
    lemlib::TrackingWheel *horizTrack[2]; // 0 = no mogo, 1 = mogo

    pros::Optical colorSortSensor(17);

    lemlib::OdomSensors *odomSensors[2]; // 0 = no mogo, 1 = mogo

    void init_sensors() {
        imu = new pros::IMU(10);

        horizTrackRotSensor = new pros::Rotation(11);
        horizTrackRotSensor->set_reversed(true);
        horizTrack[0] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, -3.5);
        horizTrack[1] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, 1.07);

        odomSensors[0] = new lemlib::OdomSensors(nullptr, nullptr, horizTrack[0], nullptr, imu);
        odomSensors[1] = new lemlib::OdomSensors(nullptr, nullptr, horizTrack[1], nullptr, imu);
        // odomSensors[0] = new lemlib::OdomSensors(vertTrack[0], nullptr, nullptr, nullptr, imu);
        // odomSensors[1] = new lemlib::OdomSensors(vertTrack[1], nullptr, nullptr, nullptr, imu);
    }

    bool mogoInRange(int range = 58) {
        return mogoDist.get() <= range;
    }
}