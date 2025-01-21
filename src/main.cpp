/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nnico                                                     */
/*    Created:      1/19/2025, 12:16:44 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;
controller Controller1;
motor LM = motor(PORT12, ratio6_1, false);
motor LB = motor(PORT15, ratio6_1, true);
motor LF = motor(PORT11, ratio6_1, true);
motor RF = motor(PORT13, ratio6_1, false);
motor RM = motor(PORT20, ratio6_1, true);
motor RB = motor(PORT19, ratio6_1, false);
motor BigArm = motor(PORT4, ratio36_1, true);
motor intake = motor(PORT10, ratio18_1, true);
motor_group leftDrive(LM, LB, LF);
motor_group rightDrive(RM, RB, RF);
double pie = 3.14159;
double dia = 2.75;
double g = 1.0 / 1.0;

vex::digital_out intakeupper(Brain.ThreeWirePort.A);
vex::digital_out mogoclamp(Brain.ThreeWirePort.B);
vex::digital_out Rdoinker(Brain.ThreeWirePort.C);
vex::digital_out Ldoinker(Brain.ThreeWirePort.D);
inertial Inertial = inertial(PORT2);

void DriveVolts(double lspeed, double rspeed, double multiplier, int wt)
{
  lspeed = lspeed * 120 * multiplier;
  rspeed = rspeed * 120 * multiplier;
  LF.spin(forward, lspeed, voltageUnits::mV);
  LM.spin(forward, lspeed, voltageUnits::mV);
  LB.spin(forward, lspeed, voltageUnits::mV);
  RF.spin(forward, rspeed, voltageUnits::mV);
  RM.spin(forward, rspeed, voltageUnits::mV);
  RB.spin(forward, rspeed, voltageUnits::mV);
  task::sleep(wt);
}

void Coast1()
{
  RB.stop(coast);
  RF.stop(coast);
  RM.stop(coast);
  LB.stop(coast);
  LF.stop(coast);
  LM.stop(coast);
}

void Brake1()
{
  RB.stop(brake);
  RF.stop(brake);
  RM.stop(brake);
  LB.stop(brake);
  LF.stop(brake);
  LM.stop(brake);
}

void inchDrive(float target, int timeout = 1500, float kp = 1.6)
{
  timer t2;
  t2.reset();
  float x = 0.0;
  float tolerance = 1;
  float accuracy = 1;
  float ki = 0;
  float error = target - x;
  float speed = error * kp;
  float integral = 0;
  float prevError = target;
  float derivative = 0;
  float kd = 0;
  RF.setPosition(0.0, rev);
  while (t2.time(msec) < timeout)
  {
    x = RF.position(rev) * pie * dia * g;
    error = target - x;

    if (fabs(error) < tolerance)
    {
      integral += error;
    }
    derivative = error - prevError;
    prevError = error;
    DriveVolts(speed, speed, 1, 10);
    speed = error * kp + integral * ki + derivative * kd;
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine();
    Controller1.Screen.print(error);
  }
  Coast1();
}
void gyroturnAbs(double target, int timeout = 1500)
{
  timer t1;
  t1.reset();
  float kp = 0.50;
  float ki = 0;
  float kd = 0.3;
  float integral = 0;
  float integralTolerance = 3;
  // float integralMax = 100;
  float heading = 0.0;
  float error = target - heading;
  float prevError = 0;
  float derivative;
  float speed = kp * error;
  float accuracy = 0.1;
  float bias = 0;

  while (t1.time(msec) < timeout)
  {
    heading = Inertial.rotation(degrees);
    error = target - heading;
    derivative = (error - prevError);
    prevError = error;
    if (fabs(error) < integralTolerance)
    {
      integral += error;
    }
    if (fabs(error) < accuracy)
    {
      integral = 0;
    }

    speed = kp * error + kd * derivative + ki * integral;
    DriveVolts(-speed, speed, 1, 0);
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.clearLine();
    Controller1.Screen.print(error);
  }
  Coast1();
  wait(10, msec);
}

void intakespinf(double time, double speed)
{
  intake.spin(forward, speed * 120, voltageUnits::mV);
  wait(time, msec);
  intake.stop();
}
void intakespinr(double time, double speed)
{
  intake.spin(reverse, speed * 120, voltageUnits::mV);
  wait(time, msec);
  intake.stop();
}

void BigArmrotatef(double time, double speed)
{
  BigArm.spin(forward, speed * 120, voltageUnits::mV);
  wait(time, msec);
  BigArm.stop();
}

void BigArmrotater(double time, double speed)
{
  BigArm.spin(reverse, speed * 120, voltageUnits::mV);
  wait(time, msec);
  BigArm.stop();
}

// void resetBigArm () {
//   BigArm.setRotation(0, degrees);
//   double BigArmPos = BigArm.rotation(degrees);
//   while(BigArmPos<100) {
//     BigArmrotate(100);
//     BigArmPos=BigArm.rotation(degrees);
//   }
//   BigArmrotate(0);
// }

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{
  Inertial.resetRotation();
  wait(2,msec);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{ 
  wait(200, msec);
  BigArmrotater(900, 100);
  wait(400,msec);
  inchDrive(-25,900);
  mogoclamp.set(true);
  BigArmrotatef(900,100);
  BigArmrotatef(900,100);
  wait(400,msec);
  gyroturnAbs(-80,300);
  inchDrive(20,800);
  intakespinf(2000,100);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void)
{
  // User control code here, inside the loop
  while (1)
  {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
