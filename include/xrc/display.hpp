#pragma once

// No need to include "main.h" or "robot.hpp" here anymore

class Display {
public:
    static void init();
    static void update();

private:
    static void displayMotorCurrent();
};