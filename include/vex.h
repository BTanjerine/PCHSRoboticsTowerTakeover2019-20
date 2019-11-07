/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       BraydenT                                                  */
/*    Created:      1 June 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include "robot-config.h"
#include "vision-config.h"
#include "vision1-config.h"
#include "utilities.h"

#include "drive.h"
#include "arm.h"
#include "camera.h"
#include "intake.h"
#include "screen.h"

vex::competition Competition = vex::competition();

vex::thread DriveControl;
vex::thread ArmControl;
vex::thread SwivelControl;
vex::thread IntakeControl;

EYE rgtEye(EYE::V2);
EYE lftEye(EYE::V1);
arm Arm;
intake Intake;
PCHSdrive Drive;

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
  
  while(1){
    Drive.trackPos();

    //if planning to turn robot
    if(Drive.desiredAng != initAngle || Drive.camState){ 
      if(!Drive.camState){
        if(Drive.isEncoderTurn){
          //PID to turn robot to correct angle with encoders
          turn = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(radToDeg(Drive.sPos.Ang), (Drive.desiredAng)));
        }
        else{
          //PID to turn robot to correct angle
          turn = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(Drive.getRoboAng(), (Drive.desiredAng)));
        }
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

          if(Drive.colorMode){turn = Drive.visionPID.getOutputPower(60, Drive.visionPID.getError(MainObjX,104));} //104
          else{turn = Drive.visionPID.getOutputPower(60, Drive.visionPID.getError(MainObjX,104));}
        }
        else{
          if(lftEye.isExisting() && !rgtEye.isExisting()){
            turn = Drive.visionPID.getOutputPower(80, Drive.visionPID.getError(lftEye.getObjectX(0, EYE::OG),90));
          }
          else if(!lftEye.isExisting() && rgtEye.isExisting()){
            turn = Drive.visionPID.getOutputPower(80, Drive.visionPID.getError(rgtEye.getObjectX(0, EYE::OG),400));
          }
          else{
            MainObjX = 0;
            MainObjY = 0;
            turn = 0; 
          }
        }
      }
    }
    else {turn=0;} //dont turn robot 

    //if planning to move robot 
    if(Drive.desiredPos != 0){
      //PID to move robot to position
      driveLft = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError(Drive.getMidPosInches(), Drive.desiredPos));
      driveRgt = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError(Drive.getMidPosInches(), Drive.desiredPos));
      if(Drive.straighten){
        correction = Drive.correctionPID.getOutputPower(10, Drive.turnPID.getError(radToDeg(Drive.sPos.Ang), Drive.initAng));
      }
      else{correction = 0;}

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
