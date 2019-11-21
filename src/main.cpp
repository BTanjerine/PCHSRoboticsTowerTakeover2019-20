
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.h                                                    */
/*    Author:       BraydenT                                                  */
/*    Created:      1 June 2019                                               */
/*    Description:  Main file for V5 projects                                 */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
using namespace std;

int autoOptions;

bool colrSeek;

void pre_auton( void ){
  
  if(Competition.isEnabled() != true){
    //reset 
    Drive.fullReset(); 
    Arm.reset();
    Intake.reset();
    roboGyro.resetAngle();
    autoOptions = 0;
  }

  while(Competition.isEnabled() != true){
    Brain.Screen.drawImageFromFile("V5-Brain-small.png", 27, 0);  //set background

    button Auto0Btn = button(20,10,48,70,false,color::cyan);  //blue front 1
    button Auto1Btn = button(20,68,48,70,false,color::cyan);    //blue front 2
    button Auto2Btn = button(20,128,48,70,false,color::cyan);  //blue back 1
    button Auto3Btn = button(20,188,48,70,false,color::cyan);    //blue back 2

    button Auto4Btn = button(390,10,48,70,false,color::red);  //red front 1
    button Auto5Btn = button(390,68,48,70,false,color::red);    //red front 2
    button Auto6Btn = button(390,128,48,70,false,color::red);  //red back 1
    button Auto7Btn = button(390,188,48,70,false,color::red);    //red back 2

    button Auto8Btn = button(190,50,100,100,false,color::purple);    //Pskils; 

    //track if the button is being touched
    Auto0Btn.update();
    Auto1Btn.update();
    Auto2Btn.update();
    Auto3Btn.update();
    Auto4Btn.update();
    Auto5Btn.update();
    Auto6Btn.update();
    Auto7Btn.update();
    Auto8Btn.update();

    Brain.Screen.printAt(100,200,"Auto is:");


    //select auto if the button is being pressed 
    if(Auto0Btn.buttonState == true){
      autoOptions = 0;
      Brain.Screen.printAt(188,200,"blue front");
    }
    else if(Auto1Btn.buttonState == true){
      autoOptions = 1;
      Brain.Screen.printAt(188,200,"blue front");
    }
    else if(Auto2Btn.buttonState == true){
      autoOptions = 2;
      Brain.Screen.printAt(188,200,"blue back");
    }
    else if(Auto3Btn.buttonState == true){
      autoOptions = 3;
      Brain.Screen.printAt(188,200,"blue back");
    }
    else if(Auto4Btn.buttonState == true){
      autoOptions = 4;
      Brain.Screen.printAt(188,200,"red front");
    }
    else if(Auto5Btn.buttonState == true){
      autoOptions = 5;
      Brain.Screen.printAt(188,200,"red front");
    }
    else if(Auto6Btn.buttonState == true){
      autoOptions = 6;
      Brain.Screen.printAt(188,200,"red back");
    }
    else if(Auto7Btn.buttonState == true){
      autoOptions = 7;
      Brain.Screen.printAt(188,200,"red back");
    }
    else if(Auto8Btn.buttonState == true){
      autoOptions = 8;
      Brain.Screen.printAt(188,200,"Program Skills");
    }

    Brain.Screen.render();
    wait(10);
  }
  Brain.Screen.clearScreen();
}                                      

void autonomous( void ) {
  //start background tasks
  DriveControl = task(driveControl);
  ArmControl = task(ArmPosControl);
  SwivelControl= task(swivelControl);
  IntakeControl = task(intakeControl);

  //clear screen
  Brain.Screen.clearScreen();

  //auto preset0
  Drive.straighten = true;
  autoOptions = 8;

  //reset robot
  Drive.fullReset();
  Drive.initAng = Drive.getRoboAng();
  //Arm.reset();
  Intake.reset();

  if(autoOptions == 0){
    //deploy rollers  
    Drive.isEncoderTurn = true;

    //deploy rollers
    setArm(90, 260);
    setSwivel(100, 1950);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(850);
    Drive.straighten = false;
    setDrive(100,-1.5);         //go forward to 1st cube
    wait(300);
    Drive.straighten = true;
    wait(300);

    setRoller(100,14000);  //move forward and pick up cubes
    setDrive(100,38);
    wait(100);
    waitDriveNew(6);
    wait(700);

    setRoller(100,12000);
    setDrive(90, 16);  //knock stack down
    wait(100);
    waitDriveNew(9);
    wait(700);
    setRoller(0,0);

    setDrive(100, -54);
    wait(100);
    waitDriveNew(10);

    setDrive(90, 0, 97); //turn to zones
    setRoller(100, 300);
    wait(100);
    waitDriveNew(5,8);

    Drive.straighten = false;

    setDrive(100,26);  //move to zone
    wait(500);
    setRoller(-100, 150);
    waitDriveNew(10);  
  
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1600);

    setArm(60, 360);
    setDrive(90,-14);   //back up away from stack
    wait(100);
    setRoller(-90,900,true);
    wait(1300);
    setSwivel(70,-10);
    waitDriveNew(5);

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }
  
  if(autoOptions == 1){
    //deploy rollers  
    Drive.isEncoderTurn = true;

    //deploy rollers
    setSwivel(100, 1900);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    //setArm(70, 270);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);

    setDrive(100, 39.5); //pickup 3 cubes
    waitDriveNew(10,7);

    setDrive(100,0,33); //turn right
    wait(100);
    waitDriveNew(8,9);

    setDrive(100, -33.5);  //back up robot
    //setArm(70,320);
    wait(500);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDriveNew(14,5);

    setDrive(100, -31, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDriveNew(11,4);

    setRoller(100, 200000);     //start rollers
    setDrive(90, 51);   //pickup 4 cubes
    wait(800);
    //setRoller(100,20000);   //start rollers
    wait(1200);
    //setRoller(0, 0);
    wait(300);
    waitDrive(17);

    setDrive(100,-20,radToDeg(Drive.sPos.Ang));     //back up 
    setRoller(70, 1000);
    setArm(90, 270);
    wait(500);
    setRoller(0, 0);
    
    wait(100000);
    

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }
  
  if(autoOptions == 2){ 
    
    Drive.isEncoderTurn = true;
    //deploy rollers
    setArm(90, 260);
    setSwivel(100, 1950);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(850);
    Drive.straighten = false;
    setDrive(100,-1.5);         //go forward to 1st cube
    wait(300);
    Drive.straighten = true;
    wait(300);

    setArm(80, 270);
    setRoller(100,23000);   //move to first cube  

    setDrive(80, 41);       //pick up cubes
    wait(100);
    waitDriveNew(12,5);
    setRoller(0, 0);
    /*
    
    pickUp(1,700,7);  
    wait(100);*/
    
    setRoller(100,14000);      //pick up last cube in row
    setDrive(70, 0, 21);
    wait(100);
    waitDriveNew(7,7);

    setDrive(100, 10);        //pick up cube near tower
    wait(100);
    waitDriveNew(15,8);

    setDrive(100, -13, 5);        //pick up cube near tower
    wait(400);
    setRoller(0, 0);
    waitDriveNew(6,7);

    setArm(70, 290);
    setDrive(100,-43,radToDeg(Drive.sPos.Ang),0.7);     //back up to zone
    wait(500);
    setRoller(0,0);
    waitDriveNew(10);

    setDrive(100, 16.5);  //move forward away from wall
    wait(100);
    waitDriveNew(10);
    
    setDrive(100,0,-132);   //turn to zones
    //setRoller(100,2200);
    wait(950);
    waitDriveNew(10,7);

    //startCam(true, true);
    //wait(130);

    Drive.straighten = false;
    setDrive(90,7.5);         //move to zone
    //startCam(false, false);
    setRoller(100, 300);
    wait(700);
    setRoller(-100,180);
    waitDriveNew(10);
    Drive.straighten = true;
    
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1600);

    //setArm(60, 300);
    setDrive(90,-14);   //back up away from stack
    wait(100);
    setRoller(-90,400,true);
    wait(1300);
    setSwivel(70,-10);
    waitDriveNew(5);

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }











  if(autoOptions == 3){
    Drive.isEncoderTurn = true;

    //deploy rollers
    setSwivel(100, 1900);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    //setArm(70, 270);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);

    setDrive(100, 39.5); //pickup 3 cubes
    waitDriveNew(10,7);

    setDrive(100,0,37); //turn right
    wait(100);
    waitDriveNew(8,9);

    setDrive(100, -33.5);  //back up robot
    //setArm(70,320);
    wait(500);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDriveNew(14,5);

    setDrive(100, -31, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDriveNew(11,4);

    setRoller(100, 200000);     //start rollers
    setDrive(90, 48.5);   //pickup 4 cubes
    wait(800);
    //setRoller(100,20000);   //start rollers
    wait(1200);
    //setRoller(0, 0);
    wait(300);
    waitDrive(17);

    setDrive(100,-25.4,radToDeg(Drive.sPos.Ang));     //back up 
    setRoller(70, 1000);
    setArm(90, 270);
    wait(500);
    setRoller(0, 0);
    waitDrive(10);

    Drive.turnPID.changePID(0.9, 0.05625, 0.225);
    setDrive(95,0,-150.5);            //turn to zones
    setRoller(50, 500);
    wait(1100);
    setSwivel(100, 1600);
    waitDriveNew(9,7);
    Drive.turnPID.changePID(1.55, 0.1125, 0.45);
    
    Drive.straighten = false;
    wait(100);
    
    //startCam(true, true);
    //wait(170);
    
    setDrive(90,13.4);          //move to zone
    //startCam(false, false);
    //wait(300);
    setRoller(-100,180);
    wait(100);
    wait(550);
    waitDriveNew(9,3);
    
    //setRoller(-60,100);
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(65, 5100);
    setRoller(0,0,true);
    wait(400);
    wait(900);

    setArm(60, 280);
    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-80,4000,true);
    wait(1300);
    setSwivel(70,-10);
    wait(10000);

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }











  
  if(autoOptions == 4){
    //deploy rollers  
    Drive.isEncoderTurn = true;

    //deploy rollers
    setArm(90, 260);
    setSwivel(100, 1950);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(850);
    Drive.straighten = false;
    setDrive(100,-1.5);         //go forward to 1st cube
    wait(300);
    Drive.straighten = true;
    wait(300);

    setRoller(100,14000);  //move forward and pick up cubes
    setDrive(100,38);
    wait(100);
    waitDriveNew(6);
    wait(700);

    setRoller(100,12000);
    setDrive(90, 16);  //knock stack down
    wait(100);
    waitDriveNew(9);
    wait(700);
    setRoller(0,0);

    setDrive(100, -54);
    wait(100);
    waitDriveNew(10);

    setDrive(90, 0, -97); //turn to zones
    setRoller(100, 300);
    wait(100);
    waitDriveNew(5,8);

    Drive.straighten = false;
    setDrive(100,26);  //move to zone
    wait(500);
    setRoller(-100, 150);
    waitDriveNew(10);  
  
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1600);

    setArm(60, 360);
    setDrive(90,-14);   //back up away from stack
    wait(100);
    setRoller(-90,900,true);
    wait(1300);
    setSwivel(70,-10);
    waitDriveNew(5);

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
    
    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }

  if(autoOptions == 5){
    Drive.isEncoderTurn = true;

    setDrive(80,-2);
    setArm(100,1210);       //raise arm 
    wait(1500);
    //setDrive(90, 4.5);
    setRoller(-100,2900);     //spit cube out
    wait(1570);

    wait(1000000);
/*
    setDrive(100, -33.5);  //back up robot
    //setArm(70,320);
    wait(500);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    wait(1000000);*/

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }
  
  if(autoOptions == 6){
    
    Drive.isEncoderTurn = true;
    //deploy rollers
    setArm(90, 260);
    setSwivel(100, 1950);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(850);
    Drive.straighten = false;
    setDrive(100,-1.5);         //go forward to 1st cube
    wait(300);
    Drive.straighten = true;
    wait(300);

    setArm(80, 260);
    setRoller(100,23000);   //move to first cube  

    setDrive(80, 41);       //pick up cubes
    wait(100);
    waitDriveNew(12,5);
    setRoller(0, 0);
    /*
    
    pickUp(1,700,7);  
    wait(100);*/

    setRoller(100,14000);      //pick up last cube in row
    setDrive(70, 0, -21);
    wait(100);
    waitDriveNew(7,7);

    setDrive(100, 10);        //pick up cube near tower
    wait(100);
    waitDriveNew(15,8);

    setDrive(100, -13, -0.8);        //pick up cube near tower
    wait(100);
    waitDriveNew(6,7);

    setDrive(100,-47,radToDeg(Drive.sPos.Ang),0.85);     //back up to zone
    wait(500);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDriveNew(10);

    setDrive(100, 16.5);  //move forward away from wall
    wait(100);
    waitDriveNew(10);
    
    setDrive(100,0,132);   //turn to zones
    //setRoller(100,2200);
    wait(950);
    waitDriveNew(10,7);

    //startCam(true, true);
    //wait(130);

    Drive.straighten = false;
    setDrive(90,7.5);         //move to zone
    //startCam(false, false);
    wait(300);
    setRoller(-100,150);
    wait(650);
    waitDriveNew(10);
    Drive.straighten = true;
    
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1600);

    //setArm(60, 300);
    setDrive(90,-14);   //back up away from stack
    wait(100);
    setRoller(-90,400,true);
    wait(1300);
    setSwivel(70,-10);
    waitDriveNew(5);
    
    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }















  if(autoOptions == 7){

    Drive.isEncoderTurn = true;

    //deploy rollers
    setArm(70, 280);
    setSwivel(100, 1950);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(850);
    Drive.straighten = false;
    setDrive(100,-1.5);         //go forward to 1st cube
    wait(300);
    Drive.straighten = true;
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 44); //slowly pickup 3 cubes
    wait(100);
    waitDriveNew(10,7);

    setDrive(100,0,-25); //turn left
    wait(100);
    waitDriveNew(10,7);

    setDrive(100, -32.4);  //back up robot
    wait(500);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDriveNew(14,5);

    setDrive(100, -38, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDriveNew(9,7);

    setRoller(100, 200000);     //start rollers
    setDrive(90, 49);   //pickup 4 cubes
    wait(800);
    setRoller(100,23000);   //start rollers
    wait(1500);
    waitDriveNew(13,5);

    setDrive(100,-22.4,radToDeg(Drive.sPos.Ang));     //back up 
    setRoller(90, 2000);
    setArm(90, 270);
    wait(500);
    waitDrive(10);
    setRoller(0, 0);

    Drive.turnPID.changePID(0.9, 0.05625, 0.225);
    setDrive(95,0,150);  //turn to zones
    setRoller(50, 500);
    wait(1100);
    setSwivel(100, 1200);
    waitDriveNew(9,7);
    Drive.turnPID.changePID(1.55, 0.1125, 0.45);
    
    Drive.straighten = false;
    wait(100);
    
    //startCam(true, true);
    //wait(170);
    
    setDrive(90,14);  //move to zone
    //startCam(false, false);
    //wait(300);
    setRoller(-100,210);
    wait(100);
    wait(550);
    waitDriveNew(9,3);
    
    //setRoller(-60,100);
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(65, 4900);
    setRoller(0,0,true);
    wait(400);
    wait(900);

    setArm(60, 280);
    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-80,4000,true);
    wait(1300);
    setSwivel(70,-10);
    wait(10000);

    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }















  if(autoOptions == 8){

    /*********Stack 7 cubes*********/
    Drive.isEncoderTurn = true;
    Drive.sPos.Ang = degToRad(-373);
/*
    //deploy rollers
    setArm(60, 270);
    wait(200);
    setSwivel(100, 1950);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(850);
    Drive.straighten = false;
    setDrive(100,-1.5);         //go forward to 1st cube
    wait(300);
    Drive.straighten = true;
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 43); //pickup 3 cubes
    wait(100);
    waitDriveNew(6,7);
    wait(100);

    setDrive(70,0,38); //turn left
    wait(100);
    waitDriveNew(5,9);

    setDrive(100, -33.5);  //back up robot
    //setArm(70,320);
    wait(500);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDriveNew(14,5);

    setDrive(100, -27, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDriveNew(11,4);

    setRoller(100, 200000);     //start rollers
    setDrive(90, 51);   //pickup 4 cubes
    wait(800);
    setRoller(100,23000);   //start rollers
    wait(1500);
    waitDriveNew(13,5);

    setDrive(100,-25.4,radToDeg(Drive.sPos.Ang));     //back up 
    setRoller(90, 2000);
    setArm(90, 270);
    wait(500);
    waitDriveNew(8,7);
    setRoller(0, 0);

    Drive.turnPID.changePID(0.9, 0.05625, 0.225);
    setDrive(95,0,-142);  //turn to zones
    setRoller(50, 500);
    wait(1100);
    setSwivel(100, 1300);
    waitDriveNew(9,7);
    Drive.turnPID.changePID(1.55, 0.1125, 0.45);
    
    Drive.straighten = false;
    wait(100);
    
    setDrive(90,15.4);  //move to zone
    setRoller(-100,200);
    wait(100);
    wait(550);
    waitDriveNew(9,3);
    
    //setRoller(-60,100);
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(65, 5100);
    setRoller(0,0,true);
    wait(400);
    wait(900);

    setArm(60, 280);
    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-80,4000,true);
    wait(1300);
    setSwivel(70,-10);
    wait(100);
    waitDriveNew(9,5);

    // **********Place cubes in towers**********
    wait(1000);
    setArm(70, 260);
    setDrive(100,0,-280);   //turn to tower
    wait(100);
    waitDriveNew(4);

    Drive.straighten = false;
    setDrive(70,-22);     //back up 
    wait(100);
    wait(1700);
    Drive.straighten = true;

    setDrive(90,48);      //go to cube
    wait(600);
    setRoller(100,12000);   //pick up cube
    waitDriveNew(3);

    setDrive(80,-2);
    setArm(100,1355);          //raise arm to first tower
    wait(1500);
    setDrive(40, 4.5);
    setRoller(-100,2900);     //spit cube out
    wait(1570);

    setDrive(50,-20);
    wait(200);
    setArm(80, 400);
    waitDriveNew(4);
    wait(200);

    //Drive.turnPID.changePID(1.7, 0.10625, 0.425);
    setDrive(90,0,-372);
    wait(300);
    setArm(70,300);               //lower arm
    waitDriveNew(4);
    //Drive.turnPID.changePID(1.55, 0.1125, 0.45);

    setDrive(80,-26);
    wait(100);
    waitDriveNew(5);

    setDrive(100,52);      //pick up 2 cube
    setRoller(100,15000);
    wait(100);
    waitDriveNew(4,5);
    wait(200);
    wait(200);
    setRoller(0, 0);

    setDrive(100, -10);
    wait(100);
    waitDriveNew(10);

    setArm(100,1210);       //raise arm 
    wait(1500);
    setDrive(60,6,radToDeg(Drive.sPos.Ang),1,true);    //forward to tower
    wait(1100);
    setRoller(-100,1600);   //spit cube into tower
    wait(1000);
    setRoller(70,900);
    wait(600);

    setDrive(100, -10);
    wait(100);
    waitDriveNew(10);*/


    setDrive(100, -12, -417);
    wait(900);
    setDrive(100, -12, -373);
    wait(100000);/*

    setRoller(0, 0);
    setDrive(90, -50);
    wait(200);
    waitDrive();

    setDrive(90, 38);
    wait(200);
    waitDriveNew();

    setDrive(90,0,-482);
    wait(100);
    waitDriveNew(4);

    setArm(100,1220);       //raise arm 
    wait(1000);
    setDrive(80,29,radToDeg(Drive.sPos.Ang),1,true);    //forward to tower
    wait(100);
    waitDriveNew(5);

    setRoller(-100,1300);   //spit cube into tower
    wait(1500);
    //setRoller(70,900);
    wait(600);

    setDrive(100, -20);
    wait(100);
    setArm(70, 330);
    waitDrive();*/


    //stop subsystem threads
    DriveControl.stop();
    ArmControl.stop();
    SwivelControl.stop();
    IntakeControl.stop();
  }
  //stop subsystem threads
  DriveControl.stop();
  ArmControl.stop();
  SwivelControl.stop();
  IntakeControl.stop();
}

void usercontrol( void ) {
  // User control code here, inside the loop
  int rgt = 0;
  int lft = 0;
  int pastPos = Arm.getArmPos();

  bool holdState;
  int holdPos;

  Brain.Screen.clearScreen();
  Brain.resetTimer();

  //stop subsystems threads
  DriveControl.stop();
  ArmControl.stop();
  SwivelControl.stop();
  IntakeControl.stop();

  task OpControl = task(opControlMacs);

  Drive.reset();
  wait(100);

  while (1){ 
    Drive.trackPos();
    //Brain.Screen.printAt(20,40,"%d",Arm.armPID.getOutputPower(10, Arm.armPID.getError(Arm.getArmPos(),pastPos)));

    //link joystick to drive
    rgt = Controller1.Axis2.value()*0.95;
    lft = Controller1.Axis3.value()*0.95;

    if(Controller1.ButtonX.pressing() && Controller1.ButtonB.pressing()){
      Drive.move_drive(50, 50);
      OpControl.stop();
    }
    else{
      Drive.move_drive(lft, rgt);
    }
    

    //move arm up/ down when buttons is pressed
    if(Controller1.ButtonL1.pressing()){
      Arm.move_arm(100);
      pastPos = Arm.getArmPos();
    }
    else if(Controller1.ButtonL2.pressing()){
      Arm.move_arm(-80);
      pastPos = Arm.getArmPos();
    }
    else{
      Arm.Stop(brakeType::hold);
      //Arm.move_arm(Arm.armPID.getOutputPower(10, Arm.armPID.getError(Arm.getArmPos(),pastPos)));
    }

    Brain.Screen.printAt(20,20,"%f",Drive.getRightPosInches());
    Brain.Screen.printAt(20,40,"%f",Drive.getLeftPosInches());
    Brain.Screen.printAt(20,60,"%d", Arm.getArmPos());
    

    //intake or spit out cubes when button is pressed
    if(Controller1.ButtonR1.pressing()){
      Intake.moveRoller(100);   //fast
    }
    else if(Controller1.ButtonR2.pressing()){
      Intake.moveRoller(-100);  //fast
    }
    else{
      Intake.stopRoller(brakeType::hold);
    }

    //move swivel forward/ back when button is pressed
    if(Controller1.ButtonUp.pressing()){
      Intake.moveSwivel(100);   //fast up
      holdPos = Intake.getSwivelPos();
      holdState = false;
    }
    else if(Controller1.ButtonRight.pressing()){
      Intake.moveSwivel(30);    //slow up
      holdPos = Intake.getSwivelPos();
      holdState = false;
    }
    else if(Controller1.ButtonDown.pressing()){
      Intake.moveSwivel(-80);   //fast down
      holdState = true;
    }
    else if(Controller1.ButtonLeft.pressing()){
      Intake.moveSwivel(-80);   //fast down
      holdState = false;
    }
    else{
      //stop 
      if(!holdState){
        Intake.stopSwivel(brakeType::hold);
        //Intake.moveSwivel(Intake.swivelPID.getOutputPower(20, Intake.swivelPID.getError(Intake.getSwivelPos(), holdPos)));
        //Intake.stopSwivel(brakeType::hold);
      }
      else{
        Intake.stopSwivel(brakeType::coast);
      }
      
    }

    Brain.Screen.render();
    
    wait(10); //Sleep the task for a short amount of time to prevent wasted resources.
    Brain.Screen.clearScreen();
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {	
  //VVVVV Dont Delete me!!!!
  vexcodeInit(); //setup motors and sensors
				
  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
                                                              
  //Run the pre-autonomous function. 
  pre_auton();

  //Prevent main from exiting with an infinite loop.   
  while(1){
      wait(100);//Sleep the task for a short amount of time to prevent wasted resources.
  }
}
