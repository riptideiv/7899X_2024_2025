#pragma once

#include "main.h"

namespace bot {
    pros::Distance mogoDist(1);

    pros::IMU *imu;

    pros::Rotation *horizTrackRotSensor;
    lemlib::TrackingWheel *horizTrack[2]; // 0 = no mogo, 1 = mogo

    pros::Optical colorSortSensor(9);

    lemlib::OdomSensors *odomSensors[2]; // 0 = no mogo, 1 = mogo

    void init_sensors() {
        imu = new pros::IMU(2);

        horizTrackRotSensor = new pros::Rotation(3);
        horizTrack[0] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, -0.75); // done
        horizTrack[1] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, 0.82);

        odomSensors[0] = new lemlib::OdomSensors(nullptr, nullptr, horizTrack[0], nullptr, imu);
        odomSensors[1] = new lemlib::OdomSensors(nullptr, nullptr, horizTrack[1], nullptr, imu);
        // odomSensors[0] = new lemlib::OdomSensors(vertTrack[0], nullptr, nullptr, nullptr, imu);
        // odomSensors[1] = new lemlib::OdomSensors(vertTrack[1], nullptr, nullptr, nullptr, imu);
    }
}