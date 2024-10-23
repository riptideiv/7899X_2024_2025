#pragma once

#include "main.h"

inline void motorMedic(pros::Motor *motors[3], int voltage = 5000, int time = 30) {
    double overallSum = 0;
    for (int i = 0; i < 3; i++) {
        int t = clock();
        double sum = 0;
        int cnt = 0;
        while (clock() - t <= time) {
            // printf("clock: %d\n", clock());
            motors[i]->move_voltage(voltage);
            double vel = motors[i]->get_actual_velocity();
            sum += fabs(vel);
            cnt++;
            pros::delay(80);
        }
        sum /= cnt;
        printf("Motor on port: %d         Avg (positive) velo: %f\n", motors[i]->get_port(), sum);
        motors[i]->move_voltage(0); // Stop the motor
        overallSum += sum;
    }
    printf("Overall avg: %f", overallSum / 3.0);
}