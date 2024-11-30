#pragma once

#include "main.h"

namespace display {
    pros::Task *displayTask;

    lv_obj_t *leftMotorsDisplay[3] = { nullptr };
    lv_obj_t *rightMotorsDisplay[3] = { nullptr };
    lv_obj_t *leftMotorsTempSquares[3] = { nullptr };
    lv_obj_t *rightMotorsTempSquares[3] = { nullptr };

    lv_obj_t *otherDisplay = nullptr;

    void displayMotorCurrentAndTemperature() {

    }

    void update() {
        displayMotorCurrentAndTemperature();
        std::vector<double> lvals = bot::drivetrain->leftMotors->get_position_all();
        std::vector<double> rvals = bot::drivetrain->rightMotors->get_position_all();
        lv_label_set_text_fmt(leftMotorsDisplay[0], "Left motors: %i %i %i", (int)lvals[0], (int)lvals[1], (int)lvals[2]);
        lv_label_set_text_fmt(rightMotorsDisplay[0], "Right motors: %i %i %i", (int)rvals[0], (int)rvals[1], (int)rvals[2]);
        // lv_label_set_text_fmt(otherDisplay, "Arm: %i", bot::bigArm.rotation->get_position());
        lv_label_set_text_fmt(otherDisplay, "chassis pose: %i %i %i", (int)(100 * bot::chass[0]->getPose().x), (int)(100 * bot::chass[0]->getPose().y), (int)(100 * bot::chass[0]->getPose().theta));
    }

    void initialize() {
        leftMotorsDisplay[0] = lv_label_create(lv_scr_act());
        lv_obj_align(leftMotorsDisplay[0], LV_ALIGN_TOP_LEFT, 10, 10);

        rightMotorsDisplay[0] = lv_label_create(lv_scr_act());
        lv_obj_align(rightMotorsDisplay[0], LV_ALIGN_TOP_LEFT, 10, 40);

        otherDisplay = lv_label_create(lv_scr_act());
        lv_obj_align(otherDisplay, LV_ALIGN_TOP_LEFT, 10, 70);

        displayTask = new pros::Task([=] {
            while (true) {
                update();
                pros::delay(500);
            }
            });
    }
}