#include "main.h"

lv_obj_t *Display::odomDebug = nullptr;
lv_obj_t *Display::odomDisplay = nullptr;
lv_obj_t *Display::hLeftMotorCurrentDisplay[3] = { nullptr };
lv_obj_t *Display::hRightMotorCurrentDisplay[3] = { nullptr };
lv_obj_t *Display::hLeftMotorTempSquare[3] = { nullptr };
lv_obj_t *Display::hRightMotorTempSquare[3] = { nullptr };

void Display::init() {
    // Initialize display-related stuff
    odomDebug = lv_label_create(lv_scr_act());
    lv_obj_align(odomDebug, LV_ALIGN_TOP_LEFT, 0, 0);

    odomDisplay = lv_label_create(lv_scr_act());
    lv_obj_align(odomDisplay, LV_ALIGN_TOP_LEFT, 0, 20);

    // Initialize left motor group current display labels
    for (int i = 0; i < 3; ++i) {
        hLeftMotorCurrentDisplay[i] = lv_label_create(lv_scr_act());
        hLeftMotorTempSquare[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_size(hLeftMotorTempSquare[i], 20, 20);
        lv_obj_align(hLeftMotorCurrentDisplay[i], LV_ALIGN_TOP_LEFT, 40, 40 + i * 20); // Adjust position as needed
        lv_obj_align(hLeftMotorTempSquare[i], LV_ALIGN_TOP_LEFT, 0, 40 + i * 20); // Adjust position as needed
    }

    // Initialize right motor group current display labels
    for (int i = 0; i < 3; ++i) {
        hRightMotorCurrentDisplay[i] = lv_label_create(lv_scr_act());
        hRightMotorTempSquare[i] = lv_obj_create(lv_scr_act());
        lv_obj_set_size(hRightMotorTempSquare[i], 20, 20);
        lv_obj_align(hRightMotorCurrentDisplay[i], LV_ALIGN_TOP_LEFT, 40, 40 + (i + 3) * 20); // Adjust position as needed
        lv_obj_align(hRightMotorTempSquare[i], LV_ALIGN_TOP_LEFT, 0, 40 + (i + 3) * 20); // Adjust position as needed
    }
}

void Display::update() {
    lv_label_set_text_fmt(odomDebug, "Angle (centidegrees): %d", (int)(xrobot::get_rotation() * 100));
    displayMotorCurrentAndTemperature();
}

void Display::displayMotorCurrentAndTemperature() {
    // Display motor current for left motor group
    for (int i = 0; i < 3; ++i) {
        lv_label_set_text_fmt(hLeftMotorCurrentDisplay[i], "Left Motor %d;; current: %d mA;; temperature: %d °C", xrobot::left_mg.get_port(i), (int)(xrobot::left_mg.get_current_draw(i)), (int)(xrobot::left_mg.get_temperature(i)));
        int temp = (int)(xrobot::left_mg.get_temperature(i));
        if (temp < 40) {
            lv_obj_set_style_bg_color(hLeftMotorTempSquare[i], lv_color_hex(0x00FF00), LV_PART_MAIN); // Green
        } else if (temp < 60) {
            lv_obj_set_style_bg_color(hLeftMotorTempSquare[i], lv_color_hex(0xFFFF00), LV_PART_MAIN); // Yellow
        } else {
            lv_obj_set_style_bg_color(hLeftMotorTempSquare[i], lv_color_hex(0xFF0000), LV_PART_MAIN); // Red
        }
    }

    // Display motor current for right motor group
    for (int i = 0; i < 3; ++i) {
        lv_label_set_text_fmt(hRightMotorCurrentDisplay[i], "Right Motor %d;; current: %d mA;; temperature: %d °C", xrobot::right_mg.get_port(i), (int)(xrobot::right_mg.get_current_draw(i)), (int)(xrobot::right_mg.get_temperature(i)));
        int temp = (int)(xrobot::right_mg.get_temperature(i));
        if (temp < 40) {
            lv_obj_set_style_bg_color(hRightMotorTempSquare[i], lv_color_hex(0x00FF00), LV_PART_MAIN); // Green
        } else if (temp < 60) {
            lv_obj_set_style_bg_color(hRightMotorTempSquare[i], lv_color_hex(0xFFFF00), LV_PART_MAIN); // Yellow
        } else {
            lv_obj_set_style_bg_color(hRightMotorTempSquare[i], lv_color_hex(0xFF0000), LV_PART_MAIN); // Red
        }
    }
}