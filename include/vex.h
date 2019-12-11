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
#include "utilities.h"

#include "drive.h"
#include "arm.h"
#include "intake.h"
#include "screen.h"

vex::competition Competition = vex::competition();

vex::task DriveControl;
vex::task ArmControl;
vex::task SwivelControl;
vex::task IntakeControl;

arm Arm;
intake Intake;
PCHSdrive Drive;

#include "Commands.h"

int driveControl(){
  int turn;
  int correction;
  int driveLft = 0;
  int driveRgt = 0;
  int rgt, lft;

  float desDist;
  
  while(1){
    Drive.trackPos();

    //if planning to turn robot
    if(Drive.desiredAng != Drive.initAng){ 
      if(Drive.isEncoderTurn){
        //PID to turn robot to correct angle with encoders
        turn = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(radToDeg(Drive.sPos.Ang), (Drive.desiredAng)));
      }
      else{
        //PID to turn robot to correct angle
        turn = Drive.turnPID.getOutputPower(Drive.DesPower, Drive.turnPID.getError(Drive.getRoboAng(), (Drive.desiredAng)));
      }

      if(Drive.desiredPos == 0){
        driveLft = driveRgt = 0;
      }
    }
    else {turn=0;} //dont turn robot 

    //if planning to move robot 
    if(Drive.desiredPos != 0){
      //PID to move robot to position
      driveLft = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError(Drive.getRobotDistTraveled(false), Drive.desiredPos));
      driveRgt = Drive.drivePID.getOutputPower(Drive.DesPower, Drive.drivePID.getError(Drive.getRobotDistTraveled(false), Drive.desiredPos));
      
      // // if(Drive.straighten){
      // //   correction = Drive.turnPID.getOutputPower(15, Drive.turnPID.getError(Drive.getRoboAng(), Drive.initGyroAng));
      // // }
      // else{correction = 0;}

    }
    else{driveLft = 0; driveRgt = 0;correction = 0;} //dont move robot

    //set drive power
    lft = (driveLft+correction) + turn;  
    rgt = (driveRgt-correction) - turn;

    Drive.move_drive(lft, rgt);
    
    wait(10); //prevent cpu hog
  }
  return 0;
}

int ArmPosControl(){
  int ArmPow;
  int duration;
  
  while(1){
    Brain.Screen.printAt(20,20,"%d",Arm.getArmPos());

    if(Arm.getArmPos() < 290 && Arm.desiredPos < 400){
      if(duration < 1000){
        ArmPow = -10;
        duration++;
      }
      else{
        ArmPow = 0;
        Arm.Stop(brakeType::hold);
      }
    }
    else{
      ArmPow = Arm.armPID.getOutputPower(Arm.DesPower, Arm.armPID.getError(Arm.getArmPos(), Arm.desiredPos));
      duration = 0;
    }

    Arm.move_arm(ArmPow);
    wait(10); //prevent cpu hog
  }
  return 0;
}

int swivelControl(){
  int swivelPow; 
  while(1){
    //calculate power PID power based off of des pos for swivel
    swivelPow = Intake.swivelPID.getOutputPower(Intake.swivelSpeed, Intake.swivelPID.getError(Intake.getSwivelPos(), Intake.swiveldesPos));

    //set power
    Intake.moveSwivel(swivelPow);
    wait(10); //prevent cpu hog
  }
  return 0;
}

int intakeControl(){
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
  return 0;
}

int opControlMacs(){
  int count;
  count = 0;
  while(1){
    if((Drive.checkInstalled() || Arm.checkInstalled() || Intake.checkInstalled()) && count < 3){
      count = count+1;
      Controller1.rumble(".-.-");
    }

    wait(10);
  }
  return 0;
}
