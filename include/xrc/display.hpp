#pragma once
#include "main.h"

// No need to include "main.h" or "robot.hpp" here anymore

class Display {
public:
    static lv_obj_t *odomDebug;
    static lv_obj_t *odomDisplay;
    static lv_obj_t *hLeftMotorCurrentDisplay[3];
    static lv_obj_t *hRightMotorCurrentDisplay[3];
    static lv_obj_t *hLeftMotorTempSquare[3];
    static lv_obj_t *hRightMotorTempSquare[3];

    static void init();
    static void update();
    static void displayMotorCurrentAndTemperature();
};