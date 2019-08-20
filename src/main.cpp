#include "vex.h"

using namespace vex;
using namespace std;

int autoOptions;

//background tasks
thread DriveControl;
thread ArmControl;
thread SwivelControl;   
thread IntakeControl;

bool colrSeek;

/*---------------------------------------------------------------------------*/
/*  Author: BraydenT                                                         */
/*  4142B 2019 Program                                                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton( void ){
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
    //deploy rollers
    setSwivel(100, 1200); //release ramp and rollers
    wait(600);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(100);
    setRoller(100,20000);   //move to first cube
    setDrive(100,16);
    wait(400);

    setDrive(60, 36); //slowly pick up 3
    wait(1900);

    setDrive(90,0,20);  //turn right
    wait(400);

    setDrive(90, -37.5);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,500);
    wait(500);
    setRoller(100, 1000);
    waitDrive(5);

    setDrive(90, -15, 0.01, true, 0.7);  //swerve to face 4 cubes
    wait(100);
    waitDrive(3);
    setRoller(100, 200000); //start roller

    setDrive(75, 44.5); //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);
    wait(1300);

    setDrive(90, -13);   //back up 
    wait(1000);

    setDrive(90,0,-147,true); //turn to zone
    wait(300);
    setRoller(0, 0, true);
    waitDrive();    //wait for drive

    setSwivel(100, 1300);
    setDrive(80,20,-147.8,true,1,true);  //move to zone
    setRoller(-100,500);    
    wait(500);
    wait(700);

    setSwivel(100, 3600);  //raise tower
    wait(100);
    setRoller(0, 0, true);
    wait(1600);

    setDrive(90,-12,0);   //back up away from stack
    setSwivel(60, 3700);
    setRoller(-90,600);
    wait(1300);
    setSwivel(70,-10);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 2){
    
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,13.5,0);
    wait(300);
    setRoller(100,20000); //start rollers
    wait(400);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,870,8.5);
    pickUp(1,800,13.8);
    setRoller(0,0);   //stop rollers
    wait(300);

    setRoller(100,6000);  //start rollers
    setDrive(80,0,23);    //turn to cube infront
    wait(600);
    setDrive(60,8,0);     //forward a little
    wait(700);

    setDrive(80,-8, -37, false, 0.5);   //backup
    wait(500);
    setRoller(0, 0);    //stop roller
    wait(400);
    
    setDrive(57,11.6,0);    //pickup last cube
    setRoller(100,7000);  //start roller
    wait(1100);

    setDrive(80,-21,0);   //back up 
    wait(700);
    wait(800);
    
    setDrive(85,0,-151.6,true); //turn to zone
    wait(300);
    setRoller(0, 0);    //stop rollers
    wait(1850);

    setDrive(100,20,0);  //move to zone
    setRoller(-100,500);
    setSwivel(100, 1300);
    wait(800);
    setRoller(0, 0, true);
    wait(500);

    setSwivel(100, 3350);  //raise tower
    wait(100);
    setRoller(0, 0, true);
    wait(1200);

    setDrive(90,-12,0);   //back up away from stack
    setRoller(-90,600);
    wait(1300);
    setSwivel(70,-10);
    
    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }

  if(autoOptions == 3){

    wait(500);
    setDrive(90,19,0);      //go to cube
    wait(600);
    setRoller(100,12000);   //pick up cube
    wait(1000);

    setArm(90,1500);          //raise arm to first tower
    wait(1900);
    setArm(90,800);      //spit cube out
    wait(1900);
    setArm(90,2200);      //spit cube out
    wait(1900);
    setArm(90,800);      //spit cube out
    wait(1900);

    Brain.Screen.printAt(20,20,"done");
    wait(1000000);
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
    wait(100);
    setRoller(100,20000);   //move to first cube
    setDrive(100,16);         //go forward to 1st cube
    wait(400);

    setDrive(60, 37); //slowly pickup 3 cubes
    wait(1900);

    setDrive(90,0,-21); //turn right
    wait(400);

    setDrive(90, -39.5);  //back up robot
    wait(500);
    setRoller(0,0);
    wait(100);
    setRoller(-100,400);
    wait(500);
    setRoller(100, 1000);
    waitDrive(5);

    setDrive(90, -15, 0.01, true, 0.7); //swerve to 4 cubes
    wait(100);
    waitDrive();
    setRoller(100, 200000);     //start rollers

    setDrive(75, 44);   //slowly pickup 4 cubes
    wait(700);
    setRoller(100,20000);   //start rollers
    wait(1300);

    setDrive(90, -13);     //back up 
    wait(1100);
    setRoller(0, 0);

    setDrive(90,0,147,true);  //turn to zones
    wait(900);
    setRoller(0, 0, true);
    waitDrive();

    setSwivel(100, 1500);    
    setDrive(80,19,147.5,true,0.8,true);  //move to zone
    setRoller(-100,600);
    wait(500);
    wait(900);

    setSwivel(80, 3600);  //raise tower
    wait(300);
    setRoller(70, 200, true);
    wait(1600);

    setDrive(90,-12,0);   //back up away from stack
    setSwivel(80, 3700);
    setRoller(-90,600);
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
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,13.5,0);
    wait(300);
    setRoller(100,20000); //start rollers
    wait(400);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,870,8.5);
    pickUp(1,800,13.8);
    setRoller(0,0);   //stop rollers
    wait(300);

    setRoller(100,6000);  //start rollers
    setDrive(80,0,-23);    //turn to cube infront
    wait(600);
    setDrive(60,8,0);     //forward a little
    wait(700);

    setDrive(80,-8, 37, false, 0.5);   //backup
    wait(500);
    setRoller(0, 0);    //stop roller
    wait(400);
    
    setDrive(57,11.6,0);    //pickup last cube
    setRoller(100,7000);  //start roller
    wait(1100);

    setDrive(80,-21,0);   //back up 
    wait(700);
    wait(800);
    
    setDrive(85,0,151.6,true); //turn to zone
    wait(300);
    setRoller(0, 0);    //stop rollers
    wait(1850);

    setDrive(100,20,0);  //move to zone
    setRoller(-100,500);
    setSwivel(100, 1300);
    wait(800);
    setRoller(0, 0, true);
    wait(500);

    setSwivel(100, 3350);  //raise tower
    wait(100);
    setRoller(0, 0, true);
    wait(1200);

    setDrive(90,-12,0);   //back up away from stack
    setRoller(-90,600);
    wait(1300);
    setSwivel(70,-10);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }

  if(autoOptions == 7){


    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 8){
    //deploy rollers
    setSwivel(100, 1000);
    wait(550);
    setRoller(100,4000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,13.5,0);
    wait(300);
    setRoller(100,20000);
    wait(400);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,870,8.5);
    pickUp(1,870,13.8);
    setRoller(0,0);
    wait(300);

    setRoller(100,7200);      //pick up last cube
    setDrive(80,0,23);
    wait(600);
    setDrive(60,8,0); 
    wait(900);

    setDrive(80,-15,-0.01,true,0.62);     //swerve away from the tower
    wait(600);

    setDrive(90,-14);     //back up to zone
    wait(1100);
    
    setDrive(80,0,-148.5,true);   //turn to zones
    wait(950);
    waitDrive();
    setRoller(0, 0);

    setDrive(100,17,0);  //move to zone
    setRoller(-100,370);
    //setSwivel(100, 1300);
    wait(700);
    setRoller(0, 0, true);
    waitDrive();

    setSwivel(90, 3600);  //raise tower
    wait(100);
    setRoller(100, 100, true);
    wait(300);
    setDrive(10,3);
    wait(1100);

    setDrive(90,-10.5,0);   //back up away from stack
    setRoller(-90,600);
    wait(1300);
    setSwivel(70,-10);
    
    setDrive(90,0,-282,true);   //turn to tower
    wait(2000);

    setDrive(70,-12,0);     //back up 
    wait(900);

    roboGyro.startCalibration();  //reset gyro (long wait for recalibration)
    wait(2500);
    
    setDrive(90,48,0);      //go to cube
    wait(600);
    setRoller(100,12000);   //pick up cube
    wait(2000);

    setArm(90,1500);          //raise arm to first tower
    wait(1000);
    setRoller(-100,2900);     //spit cube out
    wait(1300);

    setArm(70,600);               //lower arm
    wait(1000);

    setDrive(80,-14,-80.4,true);    //swerve to cubes
    wait(100);
    waitDrive();

    setArm(70,300);         //lower arm
    wait(800);

    setDrive(80,15,0);      //pick up first cube
    setRoller(100,15000);
    wait(1000);

    pickUp(2);        //pick up 2 cubes
    wait(200);
    //setRoller(0,0);

    setDrive(80,10,35);     //swerve to tower
    wait(800);
    setRoller(0,0);

    setArm(100, 2200);      //raise arm to tall tower
    wait(1400);
    setDrive(80,8.8,0);     //move closer to tower
    wait(700);
    setRoller(-100,1600);    //spit out cube into tower
    wait(1600);
    setRoller(100,800);     //intake cube
    wait(500);

    setDrive(60,-28.6,0);   //back up
    wait(500);
    setArm(70,280);          //lower arm
    wait(300);
    setArm(70,800);         //raise arm
    setRoller(70,1100);     //intake cubes
    wait(2000);

    setDrive(100,0,-56.3);    //turn to tower
    wait(100);
    waitDrive();

    setArm(100,1240);       //raise arm 
    wait(1000);
    setDrive(60,11.8,0);    //forward to tower
    wait(700);
    setRoller(-100,2000);   //spit cube into tower
    wait(1500);
    setRoller(70,900);

    setDrive(60,-15.5,0);   //back up to last tower
    wait(700);
    setRoller(70,1000);
    wait(1300);

    setArm(80,1250);
    setDrive(80,0,-94.7);   //turn to tower
    wait(100);
    waitDrive();

    setDrive(80,17,0,false,1,true);   //drift to tower
    wait(800);
    wait(1000);

    setRoller(-100,4000);   //spit cube into tower
    wait(900);
    setDrive(90,-3);  //back up a lil
    wait(300);

    setDrive(90,0,-85,true);  //turn to 3rd quadrant (red 1)
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
    setSwivel(70,-10);

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

  Brain.Screen.clearScreen();
  Brain.resetTimer();

  //stop subsystems threads
  DriveControl.interrupt();
  ArmControl.interrupt();
  IntakeControl.interrupt();
  SwivelControl.interrupt();

  Drive.reset();

  while (1){

    //link joystick to drive
    rgt = Joystick.Axis2.value()*0.95;
    lft = Joystick.Axis3.value()*0.95;


    //slow back up button
    if(Joystick.ButtonDown.pressing()){
      Drive.move_drive(10, 10);
    }
    else{
      Drive.move_drive(lft, rgt);
    }

    //move arm up/ down when buttons is pressed
    if(Joystick.ButtonL1.pressing()){
      Arm.move_arm(100);
      pastPos = Arm.getArmPos();
    }
    else if(Joystick.ButtonL2.pressing()){
      Arm.move_arm(-80);
      pastPos = Arm.getArmPos();
    }
    else{
      Arm.Stop(brakeType::hold);
    }

    //intake or spit out cubes when button is pressed
    if(Joystick.ButtonR1.pressing()){
      Intake.moveRoller(100);   //fast
    }
    else if(Joystick.ButtonR2.pressing()){
      Intake.moveRoller(-100);  //fast
    }
    else if(Joystick.ButtonX.pressing()){
      Intake.moveRoller(5);   //slow
    }
    else if(Joystick.ButtonB.pressing()){
      Intake.moveRoller(-5);  //slow
    }
    else{
      Intake.stopRoller(brakeType::hold);
    }

    //move swivel forward/ back when button is pressed
    if(Joystick.ButtonUp.pressing()){
      Intake.moveSwivel(100);   //fast up
    }
    else if(Joystick.ButtonRight.pressing()){
      Intake.moveSwivel(30);    //slow up
    }
    else if(Joystick.ButtonLeft.pressing()){
      Intake.moveSwivel(-80);   //fast down
    }
    //prevent swivel from going lower
    else if(Intake.getSwivelPos() < -10){
      Intake.stopSwivel(brakeType::hold); 
    }
    else{
      //stop 
      Intake.stopSwivel(brakeType::hold);
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
    //Run the pre-autonomous function. 
    pre_auton();
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.   
    while(1){
        wait(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }
}
