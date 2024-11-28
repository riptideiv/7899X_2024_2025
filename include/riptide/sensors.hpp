#pragma once

#include "main.h"

namespace bot {
    pros::IMU *imu;
    const double imuConstant = 360.0 / 359.0;

    pros::Rotation *horizTrackRotSensor;
    lemlib::TrackingWheel *horizTrack[2]; // 0 = no mogo, 1 = mogo

    pros::Rotation *vertTrackRotSensor;
    lemlib::TrackingWheel *vertTrack[2]; // 0 = no mogo, 1 = mogo

    lemlib::OdomSensors *odomSensors[2]; // 0 = no mogo, 1 = mogo

    void init_sensors() {
        imu = new pros::IMU(5);
        imu->reset();

        horizTrackRotSensor = new pros::Rotation(-2);
        horizTrack[0] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, 0.000); // done
        horizTrack[1] = new lemlib::TrackingWheel(horizTrackRotSensor, lemlib::Omniwheel::NEW_275, 0.049);

        vertTrackRotSensor = new pros::Rotation(12);
        vertTrack[0] = new lemlib::TrackingWheel(vertTrackRotSensor, lemlib::Omniwheel::NEW_2, 0.017);
        vertTrack[1] = new lemlib::TrackingWheel(vertTrackRotSensor, lemlib::Omniwheel::NEW_2, 0.026);

        odomSensors[0] = new lemlib::OdomSensors(vertTrack[0], nullptr, horizTrack[0], nullptr, imu);
        odomSensors[1] = new lemlib::OdomSensors(vertTrack[1], nullptr, horizTrack[1], nullptr, imu);
    }
}