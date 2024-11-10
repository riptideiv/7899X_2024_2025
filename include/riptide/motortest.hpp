#pragma once

#include "main.h"

namespace riptide {
    void testMotors(const std::vector<pros::Motor *> &motors) {
        for (auto motor : motors) {
            motor->tare_position();
            motor->move_velocity(127);
        }

        pros::delay(3000);

        double totalDistance = 0;
        std::vector<double> distances;
        for (auto motor : motors) {
            double distance = motor->get_position();
            distances.push_back(distance);
            totalDistance += distance;
            motor->move_velocity(0);
        }

        double averageDistance = totalDistance / motors.size();
        for (size_t i = 0; i < motors.size(); ++i) {
            std::cout << "Motor " << i + 1 << " distance ratio: " << distances[i] / averageDistance << std::endl;
        }
    }
}