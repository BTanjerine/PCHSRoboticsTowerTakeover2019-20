
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
  }
  Brain.Screen.clearScreen();
}                                      

void autonomous( void ) {
  DriveControl = thread(driveControl);
  ArmControl = thread(ArmPosControl);
  SwivelControl= thread(swivelControl);
  IntakeControl = thread(intakeControl);

  Brain.Screen.clearScreen();

  Drive.fullReset();
  roboGyro.resetAngle();
  Arm.reset();
  Intake.reset();

  autoOptions = 8;

  if(autoOptions == 0){
    //deploy rollers  
    Drive.isEncoderTurn = true;
    wait(100);
    setRoller(100, 200);
    Drive.turnPID.changePID(1, 0.125, 0.25);
    setDrive(90,0,132,0.45,true);  //turn to zones
    wait(300);
    waitDriveNew();
    Drive.turnPID.changePID(1.55, 0.08375, 0.45);
    setRoller(100,600);
    wait(200);
    startCam(true, false);
    wait(200);

    setDrive(60,16);  //move to zone
    wait(400);
    startCam(false, true);
    setRoller(-100,150);
    wait(650);
    setSwivel(100, 1400);
    waitDriveNew();
    
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1000);

    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-90,300,true);
    wait(1300);
    setSwivel(70,-10);

/*
    Drive.isEncoderTurn = true;

    for(int i=0; i<4; i++){
      setDrive(90,10,Drive.sPos.Ang);
      wait(100);
      waitDriveNew();
      wait(20);

      setDrive(90,0,90);
      wait(100);
      waitDriveNew(2,6);
      wait(20);
    }*/
    
    wait(1000000);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 1){
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(80, 28.5);
    wait(100);
    waitDrive();
    setRoller(0, 0);
    wait(300);
    
    setRoller(100,9000);      //pick up last cube
    pickUp(1,850,9.4);  //stop and go forward multiple times to pick up cubes
    wait(300);

    setDrive(80,0,25);
    wait(100);
    waitDrive();
    setDrive(60,8); 
    wait(100);
    waitDrive(4);

    Drive.turnPID.changePID(2, 0.125, 0.5);
    setDrive(90,-10,6);     //swerve away from the tower
    setRoller(100, 900);
    wait(100);
    waitDrive(5);
    Drive.turnPID.changePID(1.55, 0.08375, 0.45);

    setRoller(100, 4000);
    setDrive(50,16);
    wait(100);
    waitDrive();

    setRoller(100,500);
    setDrive(90,-30);     //back up to zone
    wait(100);
    waitDrive();
    
    setDrive(80,0,-149,true);   //turn to zones
    wait(950);
    waitDrive();
    setRoller(0, 0);
    startCam(true, true);
    wait(400);
    waitDriveNew(4,5);

    setDrive(90,12.5);  //move to zone
    setRoller(100,800);
    wait(200);
    startCam(false, false);
    setRoller(-100,100);
    wait(600);
    setRoller(0, 0);
    waitDrive();

    setSwivel(100, 2200);  //raise tower
    wait(700);
    setSwivel(70, 3950);
    setRoller(-100,50,true);
    wait(1000);

    setDrive(90,-12);   //back up away from stack
    setRoller(-90,600);
    wait(100);
    waitDrive();
    setSwivel(70,-10);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 2){ 
    Drive.isEncoderTurn = true;

    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 37.8); //slowly pickup 3 cubes
    wait(100);
    waitDriveNew(6,5);
    wait(100);

    setDrive(80,0,21.4); //turn right
    wait(150);
    waitDriveNew(4,4);
    

    setDrive(100, -38);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDrive(16);

    setDrive(100, -26, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDriveNew(4);

    setRoller(100, 200000);     //start rollers
    setDrive(90, 51);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(1500);

    setDrive(100,-24,radToDeg(Drive.sPos.Ang));     //back up 
    wait(900);
    setRoller(0, 0);
    waitDrive(10);
    wait(100);

    Drive.turnPID.changePID(0.9, 0.05625, 0.225);
    setDrive(100,0,-137);  //turn to zones
    setRoller(100, 400);
    setArm(90, 180);
    wait(1100);
    setSwivel(100, 1200);
    waitDriveNew(4,7);
    Drive.turnPID.changePID(1.55, 0.1125, 0.45);
    
    startCam(true, true);
    wait(150);
    
    setDrive(90,15.3);  //move to zone
    startCam(false, false);
    wait(300);
    setRoller(-100,180);
    wait(650);
    waitDriveNew(10);
    
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1200);

    setArm(60, 340);
    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-90,300,true);
    wait(1300);
    setSwivel(70,-10);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }











  if(autoOptions == 3){
    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(90, 37.5);     //quick pick up
    wait(1550);

    Drive.isEncoderTurn = true;
    setDrive(80,0,23.5); //turn right
    wait(300);
    waitDrive(3);
    Drive.isEncoderTurn = false;

    setDrive(90, -39);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,300);
    wait(500);
    setRoller(100, 1000);
    waitDrive(5);

    setDrive(95, -15, -2, 0.75); //swerve to 4 cubes
    wait(100);
    waitDrive(4);
    setRoller(100, 200000);     //start rollers

    setDrive(86, 49.3);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(1700);

    setDrive(100,-25,Drive.getRoboAng(),0.9);     //back up 
    wait(400);
    setRoller(0, 0);
    waitDrive(4);

    Drive.isEncoderTurn = true;
    setDrive(90,0,-141,0.38,true);  //turn to zones
    wait(300);
    waitDriveNew(3,5);
    setRoller(100,400);
    startCam(true, true);
    Drive.isEncoderTurn = false;
    
    setSwivel(100, 1300);
    setRoller(100, 900);
    setDrive(90,11.2);          //move to zone
    wait(200);
    setRoller(-100,100);
    wait(100);
    startCam(false, true);
    wait(650);
    waitDrive(5);


    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    //setRoller(-90,700,true);
    wait(1300);
    setSwivel(70,-10);
    
    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }











  
  if(autoOptions == 4){
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    setRoller(100,4000);
    setDrive(80,13,0);
    wait(900);
    setRoller(0,0);

    setRoller(100,12000);
    setDrive(90, 18.2, 0);
    wait(2200);
    setRoller(0,0);
    wait(20);

    setRoller(100,5000);
    setDrive(90, 18, 0);
    wait(1600);

    setDrive(80, 0, -150);
    wait(1100);

    setDrive(90, 32.5, 0);
    wait(100);
    setRoller(100,10000);
    wait(1700);

    setDrive(100,15,0);  //move to zone
    wait(400);
    setRoller(0,0);
    wait(200);  

    setRoller(-100,900);
    wait(700);
  
    setSwivel(100, 2300);  //raise tower
    wait(1100);
    setSwivel(30, 3000);
    wait(1500);

    setDrive(40,-10,0);   //back up away from tower
    setRoller(-40,900);
    wait(2000);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }

  if(autoOptions == 5){
    Drive.isEncoderTurn = true;

    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 37.8); //slowly pickup 3 cubes
    wait(100);
    waitDriveNew(6,5);
    wait(100);

    setDrive(80,0,-21.4); //turn right
    wait(150);
    waitDriveNew(4,4);
    

    setDrive(100, -38);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDrive(16);

    setDrive(100, -26, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDriveNew(4);

    setRoller(100, 200000);     //start rollers
    setDrive(90, 51);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(1500);

    setDrive(100,-24,radToDeg(Drive.sPos.Ang));     //back up 
    wait(900);
    setRoller(0, 0);
    waitDrive(10);
    wait(100);

    Drive.turnPID.changePID(0.9, 0.05625, 0.225);
    setDrive(100,0,137);  //turn to zones
    setRoller(100, 400);
    setArm(90, 180);
    wait(1100);
    setSwivel(100, 1200);
    waitDriveNew(4,7);
    Drive.turnPID.changePID(1.55, 0.1125, 0.45);
    
    startCam(true, false);
    wait(180);
    
    setDrive(90,16.5);  //move to zone
    startCam(false, true);
    wait(300);
    setRoller(-100,180);
    wait(650);
    waitDriveNew(10);
    
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1200);

    setArm(60, 340);
    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-90,300,true);
    wait(1300);
    setSwivel(70,-10);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  










  if(autoOptions == 6){
    Drive.isEncoderTurn = true;

    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 40); //slowly pickup 3 cubes
    wait(100);
    waitDriveNew();
    wait(100);

    setDrive(80,0,-23); //turn right
    wait(100);
    waitDriveNew();

    setDrive(100, -40);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,200);
    wait(500);
    setRoller(100, 1000);
    waitDriveNew();

    setDrive(90, -15, 0, 0.7); //swerve to 4 cubes
    wait(100);
    waitDrive();
    setRoller(100, 200000);     //start rollers
    setDrive(90, 52);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(2000);

    setDrive(100,-25,radToDeg(Drive.sPos.Ang),0.9);     //back up 
    wait(600);
    setRoller(0, 0);
    waitDrive(4);

    setDrive(90,0,137,0.45,true);  //turn to zones
    wait(300);
    waitDrive(4);
    setRoller(100,600);
    //Drive.stopDrive(brakeType::brake);
    startCam(true, false);
    //setSwivel(100, 1400);
    wait(200);
    //setRoller(-100,250);
    wait(300);
    wait(650);
    waitDrive(5);
    startCam(false, true);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }















  if(autoOptions == 7){
    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,12);         //go forward to 1st cube
    wait(100);
    waitDrive(3);
    setRoller(-100,2000);   //move to first cube
    wait(1000);

    setDrive(90, -8);
    wait(100);
    waitDrive();

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 8){

    /*********Stack 7 cubes*********/
    Drive.isEncoderTurn = true;

    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    setArm(80, 200);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(80, 28.5);
    wait(100);
    waitDriveNew(5,5);

    setRoller(0, 0);
    wait(500);
    setArm(60, 280);
    
    setRoller(100,8400);      //pick up last cube
    pickUp(1,850,9.4);  //stop and go forward multiple times to pick up cubes
    wait(500);

    setDrive(80,0,22);
    wait(100);
    waitDriveNew(3,6);
    setDrive(60,10); 
    wait(200);
    setRoller(100, 24000);
    waitDriveNew(5);
    wait(300);

    Drive.turnPID.changePID(0.9, 0.05625, 0.225);
    setDrive(90,-8,2);     //swerve away from the tower
    wait(100);
    waitDriveNew(6,7);
    Drive.turnPID.changePID(1.55, 0.08375, 0.45);

    setDrive(90,12,6,0.75);
    wait(100);
    waitDriveNew(2,6);
    setRoller(0,0);

    setDrive(100,-30,-5,0.7);     //back up to zone
    wait(100);
    waitDriveNew(5);
    
    setDrive(100,0,-145);   //turn to zones
    wait(950);
    waitDriveNew(5,7);
    setRoller(100,500);

    startCam(true, true);
    wait(200);

    setDrive(90,14);  //move to zone
    startCam(false, true);
    wait(300);
    setRoller(-100,180);
    wait(650);
    waitDriveNew(10);
    
    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4800);
    setRoller(0,0,true);
    wait(1400);

    setArm(60, 300);
    setDrive(90,-17);   //back up away from stack
    //setSwivel(80, 4200);
    wait(100);
    setRoller(-90,400,true);
    wait(1300);
    setSwivel(70,-10);





    /************Place cubes in towers***********/
    setDrive(90,0,-282);   //turn to tower
    wait(100);
    waitDriveNew(5);

    setDrive(70,-13);     //back up 
    wait(100);
    waitDrive();

    setDrive(90,48);      //go to cube
    wait(600);
    setRoller(100,12000);   //pick up cube
    waitDriveNew(3);

    setDrive(60,4);
    setArm(90,1500);          //raise arm to first tower
    wait(1200);
    setRoller(-100,2900);     //spit cube out
    wait(1300);

    setArm(70,600);               //lower arm
    wait(1000);

    setDrive(80,-14,-74.4);    //swerve to cubes
    wait(100);
    waitDrive(3);

    while(1);

    setArm(100,260);         //lower arm
    wait(800);

    setDrive(80,12);      //pick up 2 cube
    setRoller(100,15000);
    wait(100);
    waitDriveNew();

    pickUp(1,880,9.5);              //pick up 2 cubes
    wait(20);
    setArm(100, 2200);      //raise arm to tall tower
    wait(200);

    setRoller(0,0);
    setDrive(80,19,-47);     //swerve to tower
    wait(1400);

    setDrive(80,10.8);     //move closer to tower
    wait(700);
    setRoller(100,400);
    wait(400);
    setRoller(-100,1300);    //spit out cube into tower
    wait(1600);
    setRoller(100,800);     //intake cube
    wait(500);

    setDrive(60,-28.6);   //back up
    wait(500);
    setArm(100,280);          //lower arm
    wait(500);
    setArm(100,950);         //raise arm
    setRoller(70,1100);     //intake cubes
    wait(2000);

    setDrive(100,0,-103);    //turn to tower
    wait(100);
    waitDrive();

    setArm(100,1240);       //raise arm 
    wait(1000);
    setDrive(60,11.8);    //forward to tower
    wait(700);
    setRoller(-100,2000);   //spit cube into tower
    wait(1500);
    setRoller(70,900);
    wait(600);

    setDrive(80,-6,-82);
    wait(700);
    setArm(100, 270);
    wait(500);

    setRoller(100, 9000);
    setDrive(90,9);
    wait(300);
    waitDrive();
    wait(200);

    setRoller(0, 0);
    setDrive(90, -9);
    wait(100);
    waitDrive();

    setDrive(90, 0, 2);
    wait(100);
    waitDriveNew();

    setDrive(90,-28);
    wait(100);
    waitDrive();

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  //stop subsystem threads
  DriveControl.interrupt();
  ArmControl.interrupt();
  SwivelControl.interrupt();
  IntakeControl.interrupt();
}

void usercontrol( void ) {
  // User control code here, inside the loop
  int rgt = 0;
  int lft = 0;
  int pastPos;

  bool holdState;
  int holdPos;

  int MainObjX;
  int MainObjY;
  int turn;


  Brain.Screen.clearScreen();
  Brain.resetTimer();

  //stop subsystems threads
  DriveControl.interrupt();
  ArmControl.interrupt();
  IntakeControl.interrupt();
  SwivelControl.interrupt();

  Drive.reset();

  while (1){ 
    Drive.trackPos();

    Vision.takeSnapshot(SIG_2);
    Vision2.takeSnapshot(SIG2);

    //check if goal is in front
    if(lftEye.isExisting() && rgtEye.isExisting()){
      //find goal by find avg position of object from 2 cameras
      MainObjX = (lftEye.getObjectX(0,EYE::OG) + rgtEye.getObjectX(0, EYE::OG))/2;
      MainObjY = (lftEye.getObjectY(0,EYE::OG) + rgtEye.getObjectX(0, EYE::OG))/2;

      if(Drive.colorMode){turn = Drive.visionPID.getOutputPower(70, Drive.visionPID.getError(MainObjX,104));}
      else{turn = Drive.visionPID.getOutputPower(70, Drive.visionPID.getError(MainObjX,104));}
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

    Brain.Screen.printAt(20,20,"%f",radToDeg(Drive.sPos.Ang));
    Brain.Screen.printAt(20,40,"%f",Drive.sPos.x);
    Brain.Screen.printAt(20,60,"%f",Drive.sPos.y);

    //link joystick to drive
    rgt = Controller1.Axis2.value()*0.95;
    lft = Controller1.Axis3.value()*0.95;

    if(Controller1.ButtonX.pressing()){
      Drive.move_drive(turn, -turn);
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
    }

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

    //Brain.Screen.render();
    //Brain.Screen.clearScreen();
    
    wait(10); //Sleep the task for a short amount of time to prevent wasted resources. 
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
