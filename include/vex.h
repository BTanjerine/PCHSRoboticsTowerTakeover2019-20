/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       BraydenT                                                  */
/*    Created:      1 June 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
#include "utilities.h"

vex::competition Competition = vex::competition();

vex::brain             Brain;
vex::motor             RgtDrive(vex::PORT12, vex::gearSetting::ratio18_1, true);
vex::motor             LftDrive(vex::PORT19, vex::gearSetting::ratio18_1, false);
vex::motor             MidDrive(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::motor             RgtArm(vex::PORT14, vex::gearSetting::ratio36_1, false);
vex::motor             LftArm(vex::PORT15, vex::gearSetting::ratio36_1, true);
vex::motor             swivel(vex::PORT17, vex::gearSetting::ratio36_1, false);
vex::motor             RgtRoller(vex::PORT20, vex::gearSetting::ratio18_1, true);
vex::motor             LftRoller(vex::PORT11, vex::gearSetting::ratio18_1, false);

vex::pot               arm_pot(Brain.ThreeWirePort.A);
vex::gyro              Rgyro(Brain.ThreeWirePort.B);
vex::encoder           rgtEnc(Brain.ThreeWirePort.C);
vex::encoder           lftEnc(Brain.ThreeWirePort.E);
vex::encoder           bckEnc(Brain.ThreeWirePort.G);

vex::controller        Joystick(vex::controllerType::primary);

using namespace vex;
using namespace std;

//initialize robot subsystemS
#include "pidcontrol.h"

#include "drive.h"
drive Drive;
#include "arm.h"
arm Arm;
#include "intake.h"
intake Intake;

#include "screen.h"
#include "Commands.h"


void trackPos(){

  while(1){
    //track pos of robot
    Drive.trackPos();
    Brain.Screen.printAt(100,100,"%f",Drive.sPos.Ang);
    wait(10);
  }


}

void driveControl(){
  int turn, turn1 = 0;
  int driveLft = 0;
  int driveRgt = 0;
  int rgt, lft;

  float initAngle;

  int correction;
  
  while(1){
    //track robots position

    //if planning to turn robot
    if((Drive.desiredAng != 0 || Drive.desiredPos == 0)){
      //PID to turn robot to correct angle
      turn = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(Drive.sPos.Ang, Drive.desiredAng));
      //turn = PIDCalculator(Drive.DesPower, radToDeg(Drive.sPos.Ang), radToDeg(Drive.sPos.Ang), Drive.desiredAng, 1.3, 0.08125, 0.325);
    }
    else {turn=0; turn1 = 0;} //dont turn robot 

    //if planning to move robot 
    if(Drive.desiredPos != 0){
      //PID to move robot to position
      driveLft = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError(Drive.getMidPosInches(), Drive.desiredPos));
      driveRgt = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError(Drive.getMidPosInches(), Drive.desiredPos));
    }
    else{driveLft = 0; driveRgt = 0;} //dont move robot

    //set drive power
    lft = driveLft+turn;  
    rgt = driveRgt-turn;

    Drive.move_drive(lft, rgt);

    wait(10); //prevent cpu hog
  }
}

void ArmPosControl(){
  while(1){
    /*
    int ArmPow = -PIDCalculator(Arm.DesPower, Arm.getArmPos(), Arm.getArmPos(),
    Arm.desiredPos, Arm.kp, Arm.ki, Arm.kd);*/
    int ArmPow = Arm.armPID.getOutputPower(Arm.DesPower, Arm.armPID.getError(Arm.getArmPos(), Arm.desiredPos));
    
    Arm.move_arm(ArmPow);
    wait(25); //prevent cpu hog
  }
}

void swivelControl(){
  int swivelPow; 
  while(1){
    //calculate power PID power based off of des pos for swivel
    swivelPow = Intake.swivelPID.getOutputPower(Intake.swivelSpeed, Intake.swivelPID.getError(Intake.getSwivelPos(), Intake.swiveldesPos));

    //set power
    Intake.moveSwivel(swivelPow);
    wait(25); //prevent cpu hog
  }
}

void intakeControl(){
  int rollerPow;
  while(1){
    if(Intake.rollerState == true){
      //run rollers
      Intake.moveRoller(Intake.rollerSpeed);

      //stop intake based on direction of motor and encoder values
      if(Intake.rollerSpeed > 0 &&  Intake.getRollerPos() >= Intake.rollerRot) {Intake.rollerState = false;}
      else if(Intake.rollerSpeed < 0 && Intake.getRollerPos() <= -Intake.rollerRot) {Intake.rollerState = false;}
    }
    else{
      //hold intake roller position to hold cubes
      Intake.stopRoller(brakeType::hold);
    }
  }
}



