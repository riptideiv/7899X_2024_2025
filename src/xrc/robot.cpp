#include "xrc/robot.hpp"

namespace xrobot {
    bool goal_out = false;
    bool GOAL_TOGGLING = false;
    bool goal_locked = false;
    bool imu_flipped = false;

    pros::Controller master(pros::E_CONTROLLER_MASTER);
    pros::MotorGroup left_mg({ -1, 2, 7 });
    pros::MotorGroup right_mg({ 11, -12, -17 });
    pros::Imu sinertial(19);
    pros::Motor goal_intake(21);
    pros::Rotation srotation(9);
    pros::ADIDigitalOut glock('B', true);

    bool claw_inward = false;
    bool CLAW_TOGGLING = false;
    pros::Motor claw(20);

    bool lifting = false;
    pros::Motor lift(16);

    void initialize() {
        srotation.reset_position();
        sinertial.reset();
        goal_intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        // Wait for IMU calibration
        while (sinertial.is_calibrating()) {
            pros::delay(20);
        }
    }

    double get_rotation() {
        double rotation = sinertial.get_rotation();
        return imu_flipped ? -rotation : rotation;
    }

    void toggle_goal() {
        if (goal_out) {
            goal_out = false;
            goal_intake.move(127);
            pros::delay(200);
            while (abs(goal_intake.get_actual_velocity()) > 20) {
                pros::delay(20);
            }
            goal_intake.move(0);
        } else {
            goal_out = true;
            goal_intake.move(-127);
            pros::delay(200);
            while (abs(goal_intake.get_actual_velocity()) > 20) {
                pros::delay(20);
            }
            goal_intake.move(0);
        }
        goal_intake.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        pros::delay(200);
        goal_intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        GOAL_TOGGLING = false;
    }

    void toggle_glock() {
        goal_out = !goal_out;
        glock.set_value(goal_out);
    }

    void toggle_claw() {
        if (claw_inward) {
            claw_inward = false;
            claw.move(127);
            pros::delay(200);
            while (abs(claw.get_actual_velocity()) > 20) {
                pros::delay(20);
            }
            claw.move(0);
        } else {
            claw_inward = true;
            claw.move(-127);
            pros::delay(200);
            while (abs(claw.get_actual_velocity()) > 20) {
                pros::delay(20);
            }
            claw.move(0);
        }
        claw.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        pros::delay(200);
        claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        CLAW_TOGGLING = false;
    }

    void lower_lift_task() {
        bool lowest = false;
        while (1) {
            pros::delay(20);
            if (!lifting && !lowest) {
                lift.move(-127);
            }
        }
    }

    void drivedist(double dist, int timeout) {
        const double kP = 0.5;  // Proportional constant, adjust as needed
        const double kI = 0.01; // Integral constant, adjust as needed
        const double kD = 0.1;  // Derivative constant, adjust as needed
        const double kR = 0.1;  // Rotation correction constant, adjust as needed

        double error = dist;
        double integral = 0;
        double lastError = 0;
        double derivative = 0;
        double output = 0;
        double rotationError = 0;

        int startTime = pros::millis();

        while (pros::millis() - startTime < timeout) {
            error = dist - (left_mg.get_position() + right_mg.get_position()) / 2.0;
            integral += error;
            derivative = error - lastError;

            rotationError = get_rotation();  // Get current rotation

            output = kP * error + kI * integral + kD * derivative;

            left_mg.move(output - kR * rotationError);
            right_mg.move(output + kR * rotationError);

            lastError = error;

            pros::delay(20);  // Short delay to prevent CPU hogging
        }

        // Stop motors after timeout
        left_mg.move(0);
        right_mg.move(0);
    }
}