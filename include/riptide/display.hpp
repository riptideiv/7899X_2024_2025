#pragma once

#include "main.h"

namespace display {
    pros::Task *displayTask;

    lv_obj_t *leftMotorsDisplay[3] = { nullptr };
    lv_obj_t *rightMotorsDisplay[3] = { nullptr };
    lv_obj_t *leftMotorsTempSquares[3] = { nullptr };
    lv_obj_t *rightMotorsTempSquares[3] = { nullptr };

    lv_obj_t *imuDisplay = nullptr;

    void displayMotorCurrentAndTemperature() {
        for (int i = 0; i < 3; i++) {
            int temp = bot::chass.leftMotors->get_temperature(i);
            lv_label_set_text_fmt(leftMotorsDisplay[i], "Port %d, Curr: %d mA, Temp: %d °C        ", bot::chass.leftMotors->get_port(i), bot::chass.leftMotors->get_current_draw(i), temp);
            if (temp >= 60) {
                lv_obj_set_style_bg_color(leftMotorsTempSquares[i], lv_color_hex(0xFF0000), LV_PART_MAIN); // red
            } else {
                lv_obj_set_style_bg_color(leftMotorsTempSquares[i], lv_color_hex(0x00FF00), LV_PART_MAIN); // green
            }
        }

        for (int i = 0; i < 3; i++) {
            int temp = bot::chass.rightMotors->get_temperature(i);
            lv_label_set_text_fmt(rightMotorsDisplay[i], "Port %d, Curr: %d mA, Temp: %d °C        ", bot::chass.rightMotors->get_port(i), bot::chass.rightMotors->get_current_draw(i), temp);
            if (temp >= 60) {
                lv_obj_set_style_bg_color(rightMotorsTempSquares[i], lv_color_hex(0xFF0000), LV_PART_MAIN); // red
            } else {
                lv_obj_set_style_bg_color(rightMotorsTempSquares[i], lv_color_hex(0x00FF00), LV_PART_MAIN); // green
            }
        }
    }

    void update() {
        displayMotorCurrentAndTemperature();
        lv_label_set_text_fmt(imuDisplay, "IMU: %d", (int)(bot::get_rotation() * 100));
        // std::cout << "IMU: " << bot::get_rotation() << std::endl;
    }

    void initialize() {
        imuDisplay = lv_label_create(lv_scr_act());
        lv_obj_align(imuDisplay, LV_ALIGN_BOTTOM_LEFT, 10, -10);

        for (int i = 0; i < 3; i++) {
            leftMotorsDisplay[i] = lv_label_create(lv_scr_act());
            lv_obj_align(leftMotorsDisplay[i], LV_ALIGN_TOP_LEFT, 10, 10 + i * 20);

            leftMotorsTempSquares[i] = lv_obj_create(lv_scr_act());
            lv_obj_set_size(leftMotorsTempSquares[i], 20, 20);
            lv_obj_align(leftMotorsTempSquares[i], LV_ALIGN_TOP_RIGHT, -60, 10 + i * 20);
            lv_obj_set_style_bg_color(leftMotorsTempSquares[i], lv_color_hex(0xFF0000), LV_PART_MAIN);
        }

        for (int i = 0; i < 3; i++) {
            rightMotorsDisplay[i] = lv_label_create(lv_scr_act());
            lv_obj_align(rightMotorsDisplay[i], LV_ALIGN_TOP_LEFT, 10, 10 + (3 + i) * 20);

            rightMotorsTempSquares[i] = lv_obj_create(lv_scr_act());
            lv_obj_set_size(rightMotorsTempSquares[i], 20, 20);
            lv_obj_align(rightMotorsTempSquares[i], LV_ALIGN_TOP_RIGHT, -60, 10 + (3 + i) * 20);
            lv_obj_set_style_bg_color(rightMotorsTempSquares[i], lv_color_hex(0xFF0000), LV_PART_MAIN);
        }

        displayTask = new pros::Task([=] {
            while (true) {
                update();
                pros::delay(20);
            }
            });
    }
}