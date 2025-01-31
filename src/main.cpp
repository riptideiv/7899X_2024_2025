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
motor bigArm = motor(PORT4, ratio36_1, true);
motor intake = motor(PORT10, ratio18_1, true);
motor_group leftDrive(LM, LB, LF);
motor_group rightDrive(RM, RB, RF);
double pie = 3.14159;
double dia = 2.75;
double g = 1.0 / 1.0;
int autonNum = 1;


vex::digital_out intakeupper(Brain.ThreeWirePort.A);
vex::digital_out mogoClamp(Brain.ThreeWirePort.B);
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
  float kp = 0.60;
  float ki = 0;
  float kd = 0.4;
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
  int count = 0;


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
      count++;
    }
    else {
      count = 0;
    }
    if (count > 20) {
      break;
    }


    speed = kp * error + kd * derivative + ki * integral;
    DriveVolts(speed, -speed, 1, 0);
  }
  Brake1();
  wait(10, msec);
}


void intakeSpinF(double time, double speed)
{
  intake.spin(forward, speed * 120, voltageUnits::mV);
  wait(time, msec);
}


void intakeSpinR(double time, double speed)
{
  intake.spin(reverse, speed * 120, voltageUnits::mV);
  wait(time, msec);
}


void bigArmRotateF(double time, double speed)
{
  bigArm.spin(forward, speed * 120, voltageUnits::mV);
  wait(time, msec);
  bigArm.stop();
}


void bigArmRotateR(double time, double speed)
{
  bigArm.spin(reverse, speed * 120, voltageUnits::mV);
  wait(time, msec);
  bigArm.stop();
}


int bigArmTarget = 350;
int bigArmPIDLoop(){
  while(1){
    //PID
    wait(20,msec);
  }
  return 0;
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
  // make something for the gyro to calibrate at a predetermined angle
  // print gyro value to brain

}
  // rotate the robot to find the starting pos degree
  // set a starting degree to startingpos degree so that the robot's turns are not weird




  // Inertial.resetRotation();
  // wait(2,msec);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


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
  switch(autonNum) {
    case 0:
      Inertial.calibrate();
      while (Inertial.isCalibrating()) {
        wait(20, msec);
      }
      while (true) {
        int gyroReading = Inertial.value();
        Brain.Screen.print("Gyro: %d", gyroReading);
        wait(20, msec);
      }
    case 1:
      wait(200, msec);
      // step 1 (alliance stake)
      intakeSpinF(10,100);
      wait(600,msec);
      intake.stop();
      inchDrive(20,350);
      gyroturnAbs(-100,700);
      inchDrive(-25,900);
      // step 2 (first mogo)
      mogoClamp.set(true);

      wait(400,msec);
      gyroturnAbs(12,400);
      // step 3 (first floor ring)
      intakeSpinF(10,100);
      inchDrive(27,800);
      wait(500, msec);

      
      // ----------- STARTING TEMPLATE ----------------
      gyroturnAbs(-55,600);
      
      // step 4
    
      inchDrive(32,750);
      wait(1500,msec);
      intake.stop();
      
      // step 5
      gyroturnAbs(50,500);
      inchDrive(30,325);
      intakeSpinF(10,100);
      inchDrive(15,325);
      wait(900,msec);
      intake.stop();
      /*
      // step 6 (THIS RING GOES INTO THE WALL STAKE)
      bigArmRotateF(); // rotate up just a little bit just so that the ring goes into the LB instead of mogo
      intakeSpinF();
      inchDrive();
      intake.stop();
      // step 7 & 8 (a little diff cuz we intake at the same time as we put LB ring on wall stake)
      gyroTurnAbs();
      inchDrive();
      gyroTurnAbs(); // idk if we need this im guestimating
      inchDrive();
      // spin intake & score on wall stake at same time
      intakeSpinF(); // dont spin into mogo yet until the big arm finishes on wall stake
      bigArmRotateF(); // LB onto wall stake
      inchDrive() // drive backwards to get off the wall stake
      bigArmRotateR(); // rotate back down to position to put in the ring in the intake
      intakeSpinF(); // spin ring into LB
      // MAY NEED to move forward (idk deepends where the robot ends up)
      bigArmRotateF(); // score onto the wall stake
      inchDrive(); // drive backwards off the wall stake
      bigArmRotateR(); // set to LOWEST position
      // step 9 (the 3 rings in the top right corner)
      gyroTurnAbs(); // turn left
      intakeSpinF();
      inchDrive();
      // step 10
      gyroTurnAbs();
      inchDrive();
      // step 11
      gyroTurnAbs();
      inchDrive();
      intake.stop();
      // step 12
      gyroTurnAbs(); // turn so the mogo clamp is facing the corner
      inchDrive(); // drive backwards with mogo clamp to corner
      mogoClamp.set(false); // drop off mogo
      // step 13
      gyroTurnAbs();
      inchDrive();
      gyroTurnAbs(); // now turn again so that the mogo clamp faces the middle mogo out of the 3
      inchDrive();
      mogoClamp.set(True); // clamp onto mogo
      // step 14
      gyroTurnAbs(); // turn so that intake is facing the next closest red ring
      intakeSpinF();
      inchDrive();
      // step 15
      gyroTurnAbs(); // may or may not need depending on where u end up
      inchDrive();
      intake.stop();
      // step 16
      gyroTurnAbs(); // get ring that is reflected over the double white line
      intakeSpinF();
      inchDrive();
      // step 17 (get the two rings)
      inchDrive();
      // step 18
      gyroTurnAbs();
      intakeSpinF();
      inchDrive();
      intake.stop();
      // step 19
      gyroTurnAbs(); // turn so that the mogo faces the corner
      inchDrive(); // drive backwards to put mogo goal in corner
      mogoClamp.set(False); // drop mogo in corner
      // step 20 (GOES INTO LB FOR WALL STAKE)
      gyroTurnAbs(); // may or may not need depending on where u end up (agian lol)
      bigArmRotateF(); // rotate just enough for the ring to go into the LB instead of mogo
      intakeSpinF();
      inchDrive();
      intake.stop();
      // step 21 AND 22 (this stuff is probably all over the place and needs to be changed alot)
      gyroTurnAbs();
      inchDrive();
        // now spin the intake and big arm at the same time
      bigArmRotateF(); // score on the wall stake
      intakeSpinF(); // don't spin all the way up (wait for the big arm to go back down before u spin more)
      inchDrive(); // drive backwards off the wall stkae
      bigArmRotateR(); // rotate back down so that the ring in the intake can go into the LB
      intakeSpinF(); // spin ring into the LB
      bigArmRotateF(); // score on the wall stake
      inchDrive(); // drive backwards to get off the wall stake
      bigArmRotateR(); // rotate LB all the way down to lowest pos
      // step 23 (this ring goes into LB)
      gyroTurnAbs();
      inchDrive();
      bigArmRotateF(); // rotate LB up just a little but so that the ring goes into the LB
      gyroTurnAbs();
      intakeSpinF(); // intake into LB
      inchDrive();
      intake.stop();
      // step 24
      gyroTurnAbs();
      inchDrive();
      gyroTurnAbs();
      inchDrive(); // stop just in front of the alliance wall stake
      bigArmRotateF(); // turn LB onto wall stake
      inchDrive(); // drive backward to get off the wall stake
      bigArmRotateR(); // rotate LB back to lowest pos
      // step 25
      gyroTurnAbs(); // rotate bot so that the mogo clamp is facing the mogo with blue ring on it
      inchDrive(); // drive backward to get the mogo
      mogoClamp.set(True);
      // step 26 (SAVE THESE TWO RINGS FOR THE OTHER MOGO (step 28 ish))
      gyroTurnAbs(); // do a 180 turn so that the front intake faces the other rings
      intakeSpinF(); // only run it a little bit cuz it needs to stay in the intake
      inchDrive(); // drive forward to get the ring
      intake.stop();
      gyroTurnAbs(); // turn to get the other ring next to it
      intakeSpinF(); // also only run a little bit
      inchDrive();
      intake.stop();
      // step 27
      gyroTurnAbs(); // turn so that the clamp faces the corner
      inchDrive(); // drive backwards into the corner
      mogoClamp.set(False);
      // step 28
      gyroTurnAbs(); // turn to the direction to get the last mogo
      inchDrive();
      gyroTurnAbs(); // once u get to a close enough pos, turn so that mogo clamp faces the mogo
      inchDrive(); // a little
      mogoClamp.set(True);
      intakeSpinF(); // spin enough so that the rings that were previously stored go onto the mogo
      intake.stop();
      // step 29
      gyroTurnAbs();
      intakeSpinF();
      inchDrive();
      // step 30
      gyroTurnAbs();
      inchDrive();
      // step 31
      gyroTurnAbs();
      inchDrive();
      intake.stop();
      // step 32
      gyroTurnAbs(); // turn so mogo clamp faces the corner
      inchDrive(); // drive backwards into mogo
      mogoClamp.set(False);
      // step 33
      gyroTurnAbs(); // rotate to prep drive to the hang
        // include whaterver we are using to hang
      inchDrive();
    */
  }
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

