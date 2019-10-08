// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RgtArm               motor         14              
// LftArm               motor         15              
// swivel               motor         6               
// RgtRoller            motor         19              
// LftRoller            motor         11              
// RgtDrive             motor         12              
// LftDrive             motor         18              
// MidDrive             motor         16              
// arm_pot              pot           A               
// roboGyro             gyro          B               
// rgtEnc               encoder       C, D            
// lftEnc               encoder       E, F            
// bckEnc               encoder       G, H            
// Controller1          controller                    
// Vision               vision        10              
// Vision2              vision        1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
using namespace std;

int autoOptions;

bool colrSeek;

/*---------------------------------------------------------------------------*/
/*  Author: BraydenT                                                         */
/*  4142B 2019 Program                                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton( void ){
  vexcodeInit(); //setup motors and sensors

  if(Competition.isEnabled() != true){
    //reset 
    Drive.reset();
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

  Drive.reset();
  roboGyro.resetAngle();
  Arm.reset();
  Intake.reset();


  if(autoOptions == 0){
    //deploy rollers
    setSwivel(100, 1000); //release ramp and rollers
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    setRoller(100,4000);    //start intake
    setDrive(80,13,0);    //go to first cube
    wait(900);
    setRoller(0,0);     //stop immediately 

    setRoller(100,12000);   //start rollers
    setDrive(90, 18.2, 0);  //go to stack and intake
    wait(2200);
    setRoller(0,0); //stop immediately
    wait(20);

    setRoller(100,5000);  //start rollers
    setDrive(90, 14, 0);  //move forward to pick another
    wait(1600);

    setDrive(80, 0, 150); //turn to zone
    wait(1100);

    setDrive(90, 28.2, 0);  //move to cube infront of zone
    wait(100);
    setRoller(100,10000);
    wait(1700);

    setDrive(100,15,0);  //move to zone
    wait(500);
    setRoller(0,0); //stop intake
    wait(200);  

    setRoller(-100,300); //outake cubes lil
    wait(700);
  
    setSwivel(100, 2000);  //raise tower
    setRoller(78, 900);
    wait(1100);
    setSwivel(30, 3000);
    wait(1500);

    setDrive(40,-10,0);   //back up away from tower
    setRoller(-40,700);
    wait(2000);

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
  
  if(autoOptions == 2){ //reverse my turns
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
    setRoller(100, 1000);
    setDrive(90,11.2);          //move to zone
    wait(200);
    setRoller(-100,100);
    wait(100);
    startCam(false, true);
    wait(650);
    waitDrive(5);

    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 3950);
    setRoller(0,0,true);
    wait(1000);

    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-90,700,true);
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
    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 37.5); //slowly pickup 3 cubes
    wait(1550);

    Drive.isEncoderTurn = true;
    setDrive(80,0,-23); //turn right
    wait(300);
    waitDrive(3);
    Drive.isEncoderTurn = false;

    setDrive(90, -38);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,300);
    wait(500);
    setRoller(100, 1000);
    waitDrive(5);

    setDrive(90, -15, 0.01, 0.7); //swerve to 4 cubes
    wait(100);
    waitDrive();
    setRoller(100, 200000);     //start rollers

    setDrive(90, 51);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(1900);

    setDrive(100,-25,Drive.getRoboAng(),0.9);     //back up 
    wait(600);
    setRoller(0, 0);
    waitDrive(4);

    Drive.isEncoderTurn = true;
    setDrive(90,0,137,0.45,true);  //turn to zones
    wait(300);
    waitDrive(4);
    setRoller(100,900);
    //Drive.stopDrive(brakeType::brake);s
    startCam(true, false);
    Drive.isEncoderTurn = false;
    
    setSwivel(100, 1400);
    setDrive(90,12.5);  //move to zone
    wait(200);
    wait(300);
    setRoller(-100,250);
    startCam(false, true);
    wait(650);
    waitDrive(5);

    setSwivel(100, 2200);  //raise tower
    wait(600);
    setSwivel(70, 4200);
    setRoller(0,0,true);
    wait(1000);

    setDrive(90,-12);   //back up away from stack
    //setSwivel(80, 4200);
    setRoller(-90,700,true);
    wait(1300);
    setSwivel(70,-10);
    
    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  










  if(autoOptions == 6){
    //deploy rollers
    setSwivel(100, 1200);
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(150);
    setDrive(100,16);         //go forward to 1st cube
    wait(300);
    setRoller(100,23000);   //move to first cube

    setDrive(100, 37.5); //slowly pickup 3 cubes
    wait(1550);

    Drive.isEncoderTurn = true;
    setDrive(80,0,-23); //turn right
    wait(300);
    waitDrive(3);
    Drive.isEncoderTurn = false;

    setDrive(90, -38);  //back up robot
  
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,300);
    wait(500);
    setRoller(100, 1000);
    waitDrive(5);

    setDrive(90, -15, 0.01, 0.7); //swerve to 4 cubes
    wait(100);
    waitDrive();
    setRoller(100, 200000);     //start rollers

    setDrive(90, 52);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(2000);

    setDrive(100,-25,Drive.getRoboAng(),0.9);     //back up 
    wait(600);
    setRoller(0, 0);
    waitDrive(4);

    Drive.isEncoderTurn = true;
    setDrive(90,0,137,0.45,true);  //turn to zones
    wait(300);
    waitDrive(4);
    setRoller(100,600);
    //Drive.stopDrive(brakeType::brake);s
    startCam(true, false);
    Drive.isEncoderTurn = false;
    
    //setSwivel(100, 1400);
    wait(200);
    //setRoller(-100,250);
    wait(300);
    startCam(false, true);
    wait(650);
    waitDrive(5);

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
    
    setRoller(100,8400);      //pick up last cube
    pickUp(1,850,9.4);  //stop and go forward multiple times to pick up cubes
    wait(300);

    setDrive(80,0,25);
    wait(100);
    waitDrive();
    setDrive(60,8); 
    wait(100);
    waitDrive();

    Drive.turnPID.changePID(2, 0.125, 0.5);
    setDrive(90,-10,8);     //swerve away from the tower
    setRoller(100, 9000);
    wait(100);
    waitDrive();
    Drive.turnPID.changePID(1.55, 0.08375, 0.45);

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
    startCam(false, false);
    waitDriveNew();

    setDrive(90,13);  //move to zone
    setRoller(100,550);
    wait(200);
    setRoller(-100,370);
    wait(600);
    setRoller(0, 0);
    waitDrive();

    setSwivel(90, 3820);  //raise tower
    wait(100);
    setRoller(100, 100, true);
    wait(1900);

    setDrive(90,-12);   //back up away from stack
    setRoller(-90,600);
    wait(100);
    waitDrive();
    setSwivel(70,-10);

    setDrive(90,0,-282);   //turn to tower
    wait(100);
    waitDrive();

    setDrive(70,-12,0);     //back up 
    wait(900);

    roboGyro.startCalibration();  //reset gyro (long wait for recalibration)
    wait(2500);

    setDrive(90,45,0);      //go to cube
    wait(600);
    setRoller(100,12000);   //pick up cube
    waitDrive(3);

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



    /*
    setDrive(60,-15.5);   //back up to last tower
    wait(700);
    setRoller(70,1000);
    wait(1300);

    setArm(80,1250);
    setDrive(80,0,-94.7);   //turn to tower
    wait(100);
    waitDrive();

    setDrive(80,17,0,1,true);   //drift to tower
    wait(800);
    wait(1000);

    setRoller(-100,4000);   //spit cube into tower
    wait(900);
    setDrive(90,-3);  //back up a lil
    wait(300);

    setDrive(90,0,-85,1,true);  //turn to 3rd quadrant (red 1)
    wait(100);
    setArm(70,340);   //lower arm
    wait(100);
    waitDrive();
    
    setRoller(100,7000);
    setDrive(90,30,0);  //move forward 
    wait(1600);

    setDrive(100,15,15);    //grab 3 or 4 cubes by swerving in S shape
    setRoller(100,8000);
    wait(800);
    setDrive(100,9,-15);    
    wait(400);
    //setRoller(0,0);

    setDrive(100,10,0); //move forward
    wait(900);
    
    setSwivel(100, 1200);   //swerve to zone
    setDrive(100,35,-47);
    wait(1600);

    setSwivel(90, 3550);  //raise tower
    wait(100);
    setRoller(100, 400, true);
    wait(300);
    setDrive(10,3);
    wait(1100);

    setDrive(90,-10.5,0);   //back up away from stack
    setRoller(-90,600);
    wait(1300);
    setSwivel(70,-10);*/

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

  Brain.Screen.clearScreen();
  Brain.resetTimer();

  //stop subsystems threads
  DriveControl.interrupt();
  ArmControl.interrupt();
  IntakeControl.interrupt();
  SwivelControl.interrupt();

  Drive.reset();

  while (1){  
    Brain.Screen.printAt(20,20,"%f",radToDeg(Drive.sPos.Ang));
    Brain.Screen.printAt(20,40,"%d",rgtEye.isExisting());
    
    //link joystick to drive
    rgt = Controller1.Axis2.value()*0.95;
    lft = Controller1.Axis3.value()*0.95;
  
    Drive.move_drive(lft, rgt);

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

    Brain.Screen.render();
    Brain.Screen.clearScreen();
    
    wait(10); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {					
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
