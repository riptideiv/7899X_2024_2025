#include "xrc/auton.hpp"

using namespace xrobot;

namespace auton {
    Color selectedColor = Color::Red;
    Side selectedSide = Side::Plus;
    Mode selectedMode = Mode::Rush;
    bool AWP = true;

    void toggleAWP() {
        AWP = !AWP;
    }

    void runSelectedAuton() {
        if (selectedColor == Color::Blue) {
            imu_flipped = true;
        } else {
            imu_flipped = false;
        }

        if (selectedSide == Side::Plus) {
            if (selectedMode == Mode::Rush) {
                if (AWP) {
                    // Plus Rush AWP
                    // Add your autonomous code here
                } else {
                    // Plus Rush non-AWP
                    // Add your autonomous code here
                }
            } else {
                if (AWP) {
                    // Plus Safe AWP
                    // Add your autonomous code here
                } else {
                    // Plus Safe non-AWP
                    // Add your autonomous code here
                }
            }
        } else {
            if (selectedMode == Mode::Rush) {
                if (AWP) {
                    // Minus Rush AWP
                    // Add your autonomous code here
                } else {
                    // Minus Rush non-AWP
                    // Add your autonomous code here
                }
            } else {
                if (AWP) {
                    // Minus Safe AWP
                    // Add your autonomous code here
                } else {
                    // Minus Safe non-AWP
                    // Add your autonomous code here
                }
            }
        }

        // Reset imu_flipped state after autonomous
        imu_flipped = false;
    }
}