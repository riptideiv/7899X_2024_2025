#include "main.h"

lv_obj_t *Display::hTrackerDisplay = nullptr;

void Display::init() {
    // Initialize display-related stuff
    hTrackerDisplay = lv_label_create(lv_scr_act());
    lv_obj_align(hTrackerDisplay, LV_ALIGN_TOP_LEFT, 0, 0);
}

void Display::update() {
    displayMotorCurrent();
    lv_label_set_text_fmt(hTrackerDisplay, "tracking wheel position (centideg): %d", (int)(xrobot::horizTracker.get_position()));
    // Call other display update methods as needed
}

void Display::displayMotorCurrent() {
    // Display motor current for drivetrain, goal intake, and claw

}