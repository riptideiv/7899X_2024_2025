#pragma once
#include "main.h"

namespace auton {
    enum class Color { Red, Blue };
    enum class Side { Plus, Minus };
    enum class Mode { Rush, Safe };

    extern Color selectedColor;
    extern Side selectedSide;
    extern Mode selectedMode;
    extern bool AWP;

    void toggleAWP();
    void runSelectedAuton();
}