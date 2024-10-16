#include "main.h"

lv_obj_t *Display::hTrackerDisplay = nullptr;
lv_obj_t *Display::hOdomDisplay = nullptr;
lv_obj_t *Display::hLeftMotorCurrentDisplay[3] = { nullptr };
lv_obj_t *Display::hRightMotorCurrentDisplay[3] = { nullptr };

void Display::init() {
    // Initialize display-related stuff
    hTrackerDisplay = lv_label_create(lv_scr_act());
    lv_obj_align(hTrackerDisplay, LV_ALIGN_TOP_LEFT, 0, 0);

    // Initialize odometry display label
    hOdomDisplay = lv_label_create(lv_scr_act());
    lv_obj_align(hOdomDisplay, LV_ALIGN_TOP_LEFT, 0, 20); // Adjust position as needed

    // Initialize left motor group current display labels
    for (int i = 0; i < 3; ++i) {
        hLeftMotorCurrentDisplay[i] = lv_label_create(lv_scr_act());
        lv_obj_align(hLeftMotorCurrentDisplay[i], LV_ALIGN_TOP_LEFT, 0, 40 + i * 20); // Adjust position as needed
    }

    // Initialize right motor group current display labels
    for (int i = 0; i < 3; ++i) {
        hRightMotorCurrentDisplay[i] = lv_label_create(lv_scr_act());
        lv_obj_align(hRightMotorCurrentDisplay[i], LV_ALIGN_TOP_LEFT, 0, 40 + (i + 3) * 20); // Adjust position as needed
    }
}

void Display::update() {
    displayMotorCurrent();
    lv_label_set_text_fmt(hTrackerDisplay, "tracking wheel position (centideg): %d", (int)(xrobot::horizTracker.get_position()));

    // Display the current coordinates
    lv_label_set_text_fmt(hOdomDisplay, "X: %d, Y: %d", (int)(xrobot::odomX * 100), (int)(xrobot::odomY * 100));
}

void Display::displayMotorCurrent() {
    // Display motor current for left motor group
    for (int i = 0; i < 3; ++i) {
        lv_label_set_text_fmt(hLeftMotorCurrentDisplay[i], "Left Motor %d current: %d mA", xrobot::left_mg.get_port(i), (int)(xrobot::left_mg.get_current_draw(i)));
    }

    // Display motor current for right motor group
    for (int i = 0; i < 3; ++i) {
        lv_label_set_text_fmt(hRightMotorCurrentDisplay[i], "Right Motor %d current: %d mA", xrobot::right_mg.get_port(i), (int)(xrobot::right_mg.get_current_draw(i)));
    }
}