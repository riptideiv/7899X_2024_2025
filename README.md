# 7899X · High Stakes (2024–25)

Competition code for team 7899X’s VEX V5 robot, written in C++ with PROS and LemLib. The code includes separate drivetrain tuning for driving with and without a clamped mobile goal, optical ring sorting, and closed-loop scoring arm control using a rotation sensor.

## Where to start

| File or directory | What it does |
| --- | --- |
| [`src/main.cpp`](src/main.cpp) | Connects the PROS competition callbacks to the robot code. |
| [`include/riptide/robot.hpp`](include/riptide/robot.hpp) and [`pidConsts.hpp`](include/riptide/pidConsts.hpp) | Configure the drivetrain and its tuning for both mobile-goal states. |
| [`include/riptide/auton/`](include/riptide/auton) | Contains routine selection and autonomous routines for matches and Programming Skills. |
| [`include/riptide/intake.hpp`](include/riptide/intake.hpp) and [`bigArm.hpp`](include/riptide/bigArm.hpp) | Run the ring intake and sorting logic and control the scoring arm. |
| [`include/riptide/usercontrol.hpp`](include/riptide/usercontrol.hpp) | Maps the driver's controller inputs to the robot's mechanisms. |

[`project.pros`](project.pros) records the project’s dependencies, including PROS kernel 4.1.1 and LemLib 0.5.4.

[Team 7899X robotics showcase](https://www.xingruic.net/works/vex-robotics)
