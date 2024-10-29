#pragma once

#include "main.h"

using namespace okapi;

namespace bot {
    std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
        .withMotors({ 14,-19,-15 }, { -6,5,7 })
        .withDimensions(AbstractMotor::gearset::green, { {2.75_in, 11.5_in}, imev5BlueTPR })
        .build();

    Controller controller = Controller();

    Motor wallMech(1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor intake(2, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
    Motor hooks(3, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
}