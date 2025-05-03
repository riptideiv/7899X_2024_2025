#pragma once

#include "main.h"

namespace display {
    pros::Task *displayTask;

    lv_obj_t *leftMotorsDisplay[3] = { nullptr };
    lv_obj_t *rightMotorsDisplay[3] = { nullptr };
    lv_obj_t *leftMotorsTempSquares[3] = { nullptr };
    lv_obj_t *rightMotorsTempSquares[3] = { nullptr };

    lv_obj_t *coordsDisplay = nullptr;
    lv_obj_t *angleDisplay = nullptr;

    void displayMotorCurrentAndTemperature() {

    }

    void update() {
        displayMotorCurrentAndTemperature();
        std::vector<double> lvals = bot::drivetrain->leftMotors->get_position_all();
        std::vector<double> rvals = bot::drivetrain->rightMotors->get_position_all();
        lv_label_set_text_fmt(leftMotorsDisplay[0], "bigArm: %i ;; ColorProxim: %i", (bot::bigArm.rotation->get_position()), (int)(colorSortSensor.get_proximity()));
        lv_label_set_text_fmt(rightMotorsDisplay[0], "intakeDist: %i ;; chassVelo: %i", (int)(intakeDist.get()), (int)(bot::getChassVelo() / 600.0 * 100));
        lv_obj_set_style_text_font(angleDisplay, &lv_font_montserrat_40, 0);
        lv_label_set_text_fmt(angleDisplay, "%i.%i", (int)(bot::chass[0]->getPose().theta), abs((int)(bot::chass[0]->getPose().theta * 100) % 100));
        lv_label_set_text_fmt(coordsDisplay, "%i.%i ;; %i.%i", (int)(bot::chass[0]->getPose().x * 100), abs((int)(bot::chass[0]->getPose().x * 100) % 100), (int)(bot::chass[0]->getPose().y * 100), abs((int)(bot::chass[0]->getPose().y * 100) % 100));
    }

    void initialize() {
        leftMotorsDisplay[0] = lv_label_create(lv_scr_act());
        lv_obj_align(leftMotorsDisplay[0], LV_ALIGN_TOP_LEFT, 10, 10);

        rightMotorsDisplay[0] = lv_label_create(lv_scr_act());
        lv_obj_align(rightMotorsDisplay[0], LV_ALIGN_TOP_LEFT, 10, 40);

        coordsDisplay = lv_label_create(lv_scr_act());
        lv_obj_align(coordsDisplay, LV_ALIGN_TOP_LEFT, 10, 80);

        angleDisplay = lv_label_create(lv_scr_act());
        lv_obj_align(angleDisplay, LV_ALIGN_TOP_LEFT, 10, 120);

        displayTask = new pros::Task([=] {
            while (true) {
                update();
                pros::delay(500);
            }
            });
    }
}