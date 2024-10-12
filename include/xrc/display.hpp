#pragma once
#include "main.h"

// No need to include "main.h" or "robot.hpp" here anymore

class Display {
public:
    static void init();
    static void update();
    static lv_obj_t *hTrackerDisplay;

private:
    static void displayMotorCurrent();
};