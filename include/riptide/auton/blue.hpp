#pragma once

#include "main.h"

#include "autonIncludes.hpp"

using namespace auton;
using namespace bot;

namespace blue {
    void minus2_1_2() {
        // score alliance stake
        turn2pt(-15.5, 18.504, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        bigArm.setMaxSpeed(70);
        bigArm.set_target(14300);
        mv2pt(-6.48405, 7.30317, 1000, { .minSpeed = 30, .earlyExitRange = 1 });
        mv2pt(-6.48405, 7.30317, 300);

        // setup to grab 1st mogo
        mv2pt(14, -13.4615, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 3 });
        bigArm.setMaxSpeed(100);
        bigArm.reset();

        // grab 1st mogo
        turn2pt(33.7049, -3.48534, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(33.7049, -3.48534, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 10 });
        toggleGoalClamp();
        mv2pt(33.7049, -3.48534, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 3 });

        // get contested rings
        turn2pt(47.5907, -17.1683, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(47.5907, -17.1683, 1000, { .maxSpeed = 70, .minSpeed = 60, .earlyExitRange = 3 });
        turn2pt(49.9431, -40, 1000, { .minSpeed = 40, .earlyExitRange = 5 });
        mv2pose(49.9431, -40, -180, 1000, { .minSpeed = 40, .earlyExitRange = 1 });

        // get norush ring
        drWait(0.7, 0, 2);
        turn2pt(28.9244, -27.8521, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        mv2pt(28.9244, -27.8521, 1000, { .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 3 });

        // setup for mid
        mv2pt(9.26243, -16.4627, 1000, { .minSpeed = 40, .earlyExitRange = 3 });

        // get mid
        turn2pt(10.6929, 7.01729, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        mv2pt(10.6929, 7.01729, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(11.5817, 31.4829, 1000, { .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 1 });

        // set up for other norush ring
        mv2pt(12.7124, 50.2427, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        toggleGoalClamp();

        // get other norush ring
        turn2pt(35.1501, 64.5498, 1000, { .minSpeed = 40, .earlyExitRange = 3 });
        mv2pt(35.1501, 64.5498, 1000, { .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 1 });

        pros::Task autoStopIntakeTask([]() {
            while (1) {
                pros::Task::delay(10);
                if (colorSortSensor.get_proximity() > 200) {
                    spin_intk(0);
                    break;
                }
            }
            });

        // get mogo
        turn2pt(33.4189, 42.6774, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 2 });
        mv2pt(33.4189, 42.6774, 1000, { .forwards = false, .minSpeed = 30, .earlyExitRange = 1 });
        toggleGoalClamp();
        mv2pt(33.1288, 37.3024, 1000, { .forwards = false, .minSpeed = 40, .earlyExitRange = 3 }, 1);
        autoStopIntakeTask.suspend();
        pros::delay(150);
        spin_intk(100);

        pros::delay(5000);
        /*
        setup for mid
        x,y,theta: 9.26243, -16.4627, -57.8661, lWall: 958, rWall: 9999, mogoDist: 113

        right before mid
        x,y,theta: 10.6929, 7.01729, 1.16479, lWall: 464, rWall: 9999, mogoDist: 111

        after mid
        x,y,theta: 11.5817, 31.4829, 3.08998, lWall: 481, rWall: 9999, mogoDist: 97

        setup for ring
        x,y,theta: 12.7124, 50.2427, 3.10483, lWall: 509, rWall: 9999, mogoDist: 574

        pick up ring
        x,y,theta: 35.1501, 64.5498, 53.67, lWall: 620, rWall: 9999, mogoDist: 1355

        mogo pickup spot
        x,y,theta: 33.4189, 42.6774, 3.51782, lWall: 1075, rWall: 424, mogoDist: 2337

        drive through the mogo pickup spot
        x,y,theta: 33.1288, 37.3024, 3.05034, lWall: 1066, rWall: 2274, mogoDist: 2218

        touch ladder
        x,y,theta: 42.2523, 26.2728, -44.0295, lWall: 9999, rWall: 371, mogoDist: 254
        x,y,theta: 42.3012, 26.2057, -43.8886, lWall: 9999, rWall: 374, mogoDist: 258
        */
    }

    void minus5_1() {
        /*
        score alli
        x,y,theta: -6.29983, 9.44707, -44.7887, lWall: 190, rWall: 9999, mogoDist: 346

        setup for mogo
        x,y,theta: 16.2361, -12.586, -46.5897, lWall: 522, rWall: 9999, mogoDist: 402

        get mogo
        x,y,theta: 30.5122, -5.55534, -123.927, lWall: 1327, rWall: 9999, mogoDist: 9999

        get contested rings (2nd one)
        x,y,theta: 50.9451, -36.0005, -180.042, lWall: 1855, rWall: 1492, mogoDist: 248

        get norush ring
        x,y,theta: 33.3634, -29.9753, -85.6723, lWall: 446, rWall: 1050, mogoDist: 249

        setup for corner
        x,y,theta: 9.9057, -28.375, -83.9335, lWall: 496, rWall: 9999, mogoDist: 244

        get corner
        x,y,theta: -2.24152, -42.3405, -132.316, lWall: 244, rWall: 212, mogoDist: 251

        setup for mid
        x,y,theta: 11.06, -2.75885, -1.1451, lWall: 475, rWall: 9999, mogoDist: 245

        get mid
        x,y,theta: 9.33841, 18.1733, -1.63779, lWall: 354, rWall: 436, mogoDist: 165
        */
        // score alli stake
        bigArm.setMaxSpeed(70);
        bigArm.set_target(14300);
        int start = pros::millis();
        mv2pt(-6.29983, 9.44707, 1000, { .minSpeed = 20, .earlyExitRange = 2.5 });
        while (pros::millis() - start < 1000 && bigArm.rotation->get_position() > 17000) pros::delay(3);

        // position to get mogo
        drWait(0.55, 0.6, -2);
        bigArm.reset();
        mv2pt(15.2361, -11.586, 1000, { .forwards = false, .minSpeed = 20, .earlyExitRange = 2 });

        // get mogo
        turn2pt(32.9099, -5.84154, 1000, { .forwards = false, .minSpeed = 25, .earlyExitRange = 2 });
        toggleFrontRightArm();
        mv2pt(32.9099, -5.84154, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 4 });
        toggleGoalClamp();
        mv2pt(32.9099, -5.84154, 1000, { .forwards = false, .maxSpeed = 50, .minSpeed = 45, .earlyExitRange = 2 });
        toggleFrontRightArm();

        // get contested rings
        turn2pt(50.9451, -22.6, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        spin_intk(100);
        mv2pt(50.9451, -22.6, 1000, { .maxSpeed = 60, .minSpeed = 20, .earlyExitRange = 3 });
        turn2pt(50.9451, -36.0005, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        mv2pt(50.9451, -36.0005, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 1 });

        // get norush ring
        drWait(0.7, 0, -1);
        turn2pt(33.3634, -29.9753, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(33.3634, -29.9753, 1000, { .maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 3 });

        // get corner
        mv2pt(9.9057, -28.375, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        turn2pt(-2.24152, -42.3405, 1000, { .minSpeed = 30, .earlyExitRange = 3 });
        mv2pt(-2.24152, -42.3405, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        intake.doAntiStuck = false;
        drive_chass(40, 40);
        pros::delay(1000);
        drWait(0.6, 0.6, -5);
        intake.doAntiStuck = true;

        // get mid
        turn2pt(11.06, -5, 1000, { .minSpeed = 40, .earlyExitRange = 2 });
        mv2pt(11.06, -5, 1000, { .minSpeed = 20, .earlyExitRange = 2 });
        toggleIntakeLift();
        turn2pt(9.33841, 18.1733, 1000, { .minSpeed = 20, .earlyExitRange = 1 });
        mv2pt(9.33841, 18.1733, 1000, { .minSpeed = 30, .earlyExitRange = 2 });
        toggleIntakeLift();
        drWait(0.6, 0.6, -5);
        drive_chass(0, 0);
        pros::delay(5000);
    }

    void minus6() {}

    void minus5clear() {

    }

    void plus5() {

    }

    void plus4_1() { // modified from plus5

    }

    void plusRush3_1() {

    }

    void plusRush2_1_1() {

    }
}