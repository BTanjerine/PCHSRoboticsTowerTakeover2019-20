/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       BraydenT                                                  */
/*    Created:      1 June 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
#include "utilities.h"
#include "vision-config.h"
#include "vision2-config.h"

vex::competition Competition = vex::competition();

vex::brain             Brain;

vex::motor             RgtArm(vex::PORT14, vex::gearSetting::ratio36_1, false);
vex::motor             LftArm(vex::PORT15, vex::gearSetting::ratio36_1, true);
vex::motor             swivel(vex::PORT17, vex::gearSetting::ratio36_1, false);
vex::motor             RgtRoller(vex::PORT19, vex::gearSetting::ratio18_1, false);
vex::motor             LftRoller(vex::PORT11, vex::gearSetting::ratio18_1, true);
vex::motor             RgtDrive(vex::PORT12, vex::gearSetting::ratio18_1, true);
vex::motor             LftDrive(vex::PORT18, vex::gearSetting::ratio18_1, false);
vex::motor             MidDrive(vex::PORT16, vex::gearSetting::ratio18_1, false);

vex::encoder           rgtEnc(Brain.ThreeWirePort.C);
vex::encoder           lftEnc(Brain.ThreeWirePort.E);
vex::encoder           bckEnc(Brain.ThreeWirePort.G);
vex::gyro              roboGyro(Brain.ThreeWirePort.B);

vex::pot               arm_pot(Brain.ThreeWirePort.A);

vex::controller        Joystick(vex::controllerType::primary);

vex::thread DriveControl;
vex::thread ArmControl;
vex::thread SwivelControl;
vex::thread IntakeControl;

using namespace vex;
using namespace std;

//initialize robot subsystems
#include "pidcontrol.h"

#include "drive.h"
drive Drive;
#include "arm.h"
arm Arm;
#include "camera.h"
EYE rgtEye(EYE::V2);
EYE lftEye(EYE::V1);

#include "intake.h"
intake Intake;

#include "screen.h"
#include "Commands.h"

void driveControl(){
  int turn;
  int correction;
  int driveLft = 0;
  int driveRgt = 0;
  int rgt, lft;

  float desDist;

  int MainObjX;
  int MainObjY;

  float initAngle;

  //make following line 
  _line followLine;

  //Drive.reset();
  
  while(1){
    Drive.trackPos();

    //if planning to turn robot
    if(Drive.desiredAng != Drive.getRoboAng() || Drive.camState){
      if(!Drive.camState){
        //PID to turn robot to correct angle
        turn = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(Drive.getRoboAng(), (Drive.desiredAng)));
      }
      else{
        if(Drive.colorMode){
          Vision.takeSnapshot(SIG_1); //start tracking
          Vision2.takeSnapshot(SIG1);
        }
        else{
          Vision.takeSnapshot(SIG_2);
          Vision2.takeSnapshot(SIG2);
        }

        //check if goal is in front
        if(lftEye.isExisting() && rgtEye.isExisting()){
          //find goal by find avg position of object from 2 cameras
          MainObjX = (lftEye.getObjectX(0,EYE::OG) + rgtEye.getObjectX(0, EYE::OG))/2;
          MainObjY = (lftEye.getObjectY(0,EYE::OG) + rgtEye.getObjectX(0, EYE::OG))/2;

          if(Drive.colorMode){turn = Drive.visionPID.getOutputPower(80, Drive.visionPID.getError(MainObjX,89));}
          else{turn = Drive.visionPID.getOutputPower(80, Drive.visionPID.getError(MainObjX,95));}
        }
        else{
          MainObjX = 90;
          MainObjY = 0;
          turn = 0;
        }
      }
    }
    else {turn=0;} //dont turn robot 

    //if planning to move robot 
    if(Drive.desiredPos != 0){
      //PID to move robot to position
      driveLft = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError((Drive.getLeftPosInches()+Drive.getRightPosInches())/2, Drive.desiredPos));
      driveRgt = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError((Drive.getLeftPosInches()+Drive.getRightPosInches())/2, Drive.desiredPos));
      
      if(turn == 0 && (abs(driveLft) > 4 && abs(driveRgt) > 4) && abs(Drive.sPos.x) > 0.8){
        //set points for the line the robot has to follow
        followLine.p1.x = Drive.initPos.x; //start
        followLine.p1.y = Drive.initPos.y;

        followLine.p2.x = Drive.desiredPos * sinf(Drive.desiredAng);  //end
        followLine.p2.y = Drive.desiredPos * cosf(Drive.desiredAng);

        //find angle of line
        if(abs(Drive.followAng-Drive.sPos.Ang)>M_PI/2 && abs(Drive.followAng-Drive.sPos.Ang)<(3*M_PI)/2 && Drive.followAng != 0){
          Drive.followAng = fmod((Drive.followAng+180), 360.0);
        }
        else{
          Drive.followAng = lineAngle(followLine); 
        }      

        //calculate the correcting power
        correction = Drive.correctionPID.getOutputPower(10, Drive.correctionPID.getError(Drive.getRoboAng(), (Drive.getRoboAng() + radToDeg(Drive.followAng))));
      }
      else{
        if(turn == 0 && (abs(driveLft) > 5 && abs(driveRgt) > 5) ){
          correction = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(Drive.getRoboAng(), (Drive.initAng)));
        }
        else{
          correction = 0;
        }
      }
    }
    else{driveLft = 0; driveRgt = 0;correction = 0;} //dont move robot

    //set drive power
    lft = (driveLft+correction) + turn;  
    rgt = (driveRgt-correction) - turn;

    Drive.move_drive(lft, rgt);

    wait(10); //prevent cpu hog
  }
}

void ArmPosControl(){
  while(1){
    int ArmPow = Arm.armPID.getOutputPower(Arm.DesPower, Arm.armPID.getError(Arm.getArmPos(), Arm.desiredPos));
    
    Arm.move_arm(ArmPow);
    wait(10); //prevent cpu hog
  }
}

void swivelControl(){
  int swivelPow; 
  while(1){
    //calculate power PID power based off of des pos for swivel
    swivelPow = Intake.swivelPID.getOutputPower(Intake.swivelSpeed, Intake.swivelPID.getError(Intake.getSwivelPos(), Intake.swiveldesPos));

    //set power
    Intake.moveSwivel(swivelPow);
    wait(10); //prevent cpu hog
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
      if(!Intake.isCoasting){
        //hold intake roller position to hold cubes
        Intake.stopRoller(brakeType::hold);
      }
      else{
        Intake.stopRoller(brakeType::coast);
      }
      
    }
    wait(10);
  }
}

void trackZone(bool colorMode, float desDist){
  int correction;
  int MainObjX;
  int MainObjY;

  int pow = 90;

  DriveControl.interrupt();

  while(1){
    if(colorMode){
      Vision.takeSnapshot(SIG_1); //start tracking
      Vision2.takeSnapshot(SIG1);
    }
    else{
      Vision.takeSnapshot(SIG_2);
      Vision2.takeSnapshot(SIG2);
    }
  
    pow = Drive.drivePID.getOutputPower(90, Drive.drivePID.getError((Drive.getLeftPosInches()+Drive.getRightPosInches())/2, desDist));

    //check if goal is in front
    if(lftEye.isExisting() && rgtEye.isExisting()){
      //find goal by find avg position of object from 2 cameras
      MainObjX = (lftEye.getObjectX(0,EYE::OG) + rgtEye.getObjectX(0, EYE::OG))/2;
      MainObjY = (lftEye.getObjectY(0,EYE::OG) + rgtEye.getObjectX(0, EYE::OG))/2;

      if(colorMode){correction = Drive.visionPID.getOutputPower(50, Drive.visionPID.getError(MainObjX,85));}
      else{correction = Drive.correctionPID.getOutputPower(50, Drive.correctionPID.getError(MainObjX,110));}
    }
    else{
      MainObjX = 100;
      MainObjY = 0;
      correction = 0;
      pow = 0;
    }

    Drive.move_drive(pow+correction,pow-correction);
  }

  Drive.move_drive(0,0);

  Drive.reset();
  wait(100);

  DriveControl = thread(driveControl);
}



