#pragma once

#include "main.h"

namespace test {
    void offsetTest() {
        bot::reset();
        bot::drive_chass(50, -50);
        double avgV = 0, avgH = 0;
        double origV = bot::getVertPos();
        double origH = bot::getHorizPos();
        for (int i = 0; i < 10; i++) {
            pros::delay(2000);
            double angle = bot::getRotation();
            double vOffset = (bot::getVertPos() - origV) / 36000 * 2 / angle;
            double hTrackOffset = (bot::getHorizPos() - origH) / 36000 * 2.75 / angle;
            avgV += vOffset;
            avgH += hTrackOffset;
            printf("Angle: %f, Vert: %f, Horiz: %f\n", angle, vOffset, hTrackOffset);
        }
        printf("Avg: Vert: %f, Horiz: %f\n", avgV / 10, avgH / 10);
    }
}