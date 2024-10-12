#pragma once
#include "main.h"
namespace xrobot{
    extern double prevL,prevR,prevAngle,odomX,odomY;
    struct Constants{
        static constexpr double wheelDia = 2.75; // diameter of drivetrain wheel
        static constexpr double trackDia = 2.75; // diameter of tracking wheel
        static constexpr double hWheelOffset = 0; // vertical offset of horizontal tracking wheel from the center (forward is +)
        static constexpr double vWheelOffset = 0; // horizontal offset of vertical tracking wheel from the center (rightward is +), we don't have one
        static constexpr double lWheelOffset = -6.4; // horizontal offset of left drivetrain side from the center (rightward is +)
        static constexpr double rWheelOffset = 6.4; // horizontal offset of right drivetrain side from the center (rightward is +)
    };
    extern struct Constants constants;
    void updatePos();
    void initTracking();
    extern pros::Task *odomTask;
}