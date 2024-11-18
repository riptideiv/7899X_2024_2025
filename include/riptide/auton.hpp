#pragma once

#include "auton/autonSelect.hpp"

namespace auton {
    void initialize() {
        autonSelectTask = new pros::Task(autonSelectLoop);
    }
}