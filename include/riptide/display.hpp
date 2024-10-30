#pragma once

#include "main.h"

namespace display {
    pros::Task *displayTask;

    lv_obj_t *leftMotorsDisplay[3] = { nullptr };
    lv_obj_t *rightMotorsDisplay[3] = { nullptr };
    lv_obj_t *leftMotorsTempSquares[3] = { nullptr };
    lv_obj_t *rightMotorsTempSquares[3] = { nullptr };

    void displayMotorCurrentAndTemperature() {

    }

    void update() {
        displayMotorCurrentAndTemperature();
    }

    void initialize() {
        for (int i = 0; i < 3; i++) {
            leftMotorsDisplay[i] = lv_label_create(lv_scr_act());
            leftMotorsTempSquares[i] = lv_obj_create(lv_scr_act());
            lv_obj_set_size(leftMotorsDisplay[i], 20, 20);
            lv_obj_align(leftMotorsTempSquares[i], LV_ALIGN_TOP_LEFT, 0, 40 + i * 20);
            lv_obj_align(leftMotorsDisplay[i], LV_ALIGN_TOP_LEFT, 40, 40 + i * 20);
        }

        for (int i = 0; i < 3; i++) {
            rightMotorsDisplay[i] = lv_label_create(lv_scr_act());
            rightMotorsTempSquares[i] = lv_obj_create(lv_scr_act());
            lv_obj_set_size(rightMotorsDisplay[i], 20, 20);
            lv_obj_align(rightMotorsTempSquares[i], LV_ALIGN_TOP_RIGHT, 0, 40 + (3 + i) * 20);
            lv_obj_align(rightMotorsDisplay[i], LV_ALIGN_TOP_RIGHT, 40, 40 + (3 + i) * 20);
        }

        displayTask = new pros::Task([=] {
            while (true) {
                update();
                pros::delay(20);
            }
            });
    }
}