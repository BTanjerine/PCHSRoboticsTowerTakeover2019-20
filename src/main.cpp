#include "vex.h"

using namespace vex;
using namespace std;

int autoOptions;

thread DriveControl;
thread ArmControl;
thread SwivelControl;   
thread IntakeControl;
thread PosTracker;

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
  Arm.reset();
  Intake.reset();

  autoOptions = 2;

  if(autoOptions == 0){
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
    setDrive(90, 14, 0);
    wait(1600);

    setDrive(80, 0, 150);
    wait(1100);

    setDrive(90, 28.2, 0);
    wait(100);
    setRoller(100,10000);
    wait(1700);

    setDrive(100,15,0);  //move to zone
    wait(500);
    setRoller(0,0);
    wait(200);  

    setRoller(-100,1300);
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
    setRoller(100,20000);
    wait(850);

    //pickUp(1,790,8.2);  //stop and go forward multiple times to pick up cubes
    //pickUp(1,850,9.2);
    setDrive(65,17);
    wait(1700);
    pickUp(1,790,10.3);
    wait(400);
    setRoller(0,0);
    wait(100);

    setDrive(80,14,33,0.625); //sharp swerve to green cube next to tower
    wait(100);
    setRoller(100,6000);
    wait(1000);

    setDrive(80,-14,-33);
    wait(700);

    setDrive(80,-12,0);  //back up
    //setRoller(0, 0);
    wait(1100);
    
    setDrive(70,0,-143.4);
    wait(2050);
    setRoller(0, 0);

    setDrive(100,23,0);  //move to zone
    setRoller(-100,500);
    wait(500);

    //if 6 cubes
    if(Intake.trackTopCubes(vex::color::green)){
      wait(1000);

      setSwivel(100, 2100);  //raise tower
      Intake.stopRoller(brakeType::coast);
      wait(1100);
      setSwivel(30, 2800);
      wait(500);

      setDrive(90,-12,0);   //back up away from stack
      setRoller(-90,600);
      wait(1300);
      setSwivel(70,-10);
    }
    //if not
    else{
      wait(1000);
      setRoller(-100,400,true);
      wait(200);

      Intake.stopRoller(brakeType::coast);
      setSwivel(100, 2100);  //raise tower
      setDrive(10,10);
      wait(1100);
      setSwivel(30, 2800);
      wait(500);

      setRoller(-90,600);
      setDrive(90,-12,0);   //back up away from stack
      wait(1300);
      setSwivel(70,-10);
    }
    /*
    //setRoller(100,1500);
    wait(1000);

    setSwivel(100, 1900);  //raise tower
    wait(1300);
    setSwivel(30, 2800);
    wait(900);

    setDrive(70,-12,0);   //back up away from stack
    setRoller(-60,500);
    wait(1300);
    setSwivel(70,-10);*/
    
    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }

  if(autoOptions == 3){
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,13.5,0);
    setRoller(100,20000);
    wait(850);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,830,9.2);
    pickUp(1,780,10.3);
    wait(500);
    setRoller(0,0);

    Drive.drivePID.changePID(5, 0.3125, 1.25);
    setDrive(80,13,33); //swerve to green cube next to tower
    wait(50);
    setRoller(100,5000);
    wait(1000);

    Drive.drivePID.changePID(8, 0.5, 2);
    wait(500);
    setRoller(0,0);
    setDrive(80,-5,0);  //back up
    wait(400);

    setDrive(80,0,1); // turn to other cube next to tower
    wait(300);
    wait(300);
    
    setDrive(60,6.3,0);
    setRoller(100,7000);  //start roller
    wait(750);

    setDrive(80,-15.5,0);
    wait(800);
    setRoller(0,0);

    setDrive(70,0,-153.7);//-175
    wait(1700);

    setRoller(-100,900);
    setDrive(100,27,0);  //move to zone
    wait(500);
    //setRoller(100,1500);
    wait(1000);

    setSwivel(100, 1900);  //raise tower
    wait(1300);
    setSwivel(30, 2800);
    wait(900);

    setDrive(70,-12,0);   //back up away from stack
    setRoller(-60,500);
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

    setDrive(100, 20.0, 0);
    wait(10000);

    
    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 6){
    /*
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,14.7,0);
    setRoller(100,20000);
    wait(850);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,820,9.2);
    pickUp(1,800,10.3);
    wait(900);
    setRoller(0,0);

    Drive.drivePID.changePID(5, 0.3125, 1.25);
    setDrive(80,14,-30); //swerve to green cube next to tower
    wait(50);
    setRoller(100,5000);
    wait(1000);

    Drive.drivePID.changePID(8, 0.5, 2);
    setDrive(80,-4.5,0);  //back up
    wait(700);
    setRoller(0,0);

    setDrive(80,0,1); // turn to other cube next to tower
    wait(300);
    wait(300);
    
    setDrive(60,10.5,0);
    setRoller(100,7000);  //start roller
    wait(1200);

    setDrive(80,-12.5,0);
    wait(800);
    setRoller(0,0);

    setDrive(70,-3,0);//-175
    wait(400);

    setDrive(80,0,143.5);//-175
    wait(1700);

    setRoller(-100,900);
    setDrive(100,29,0);  //move to zone
    wait(500);
    setRoller(100,900);
    wait(1000);

    setSwivel(100, 1900);  //raise towesr
    wait(1300);
    setSwivel(30, 2600);
    wait(900);

    setDrive(70,-12,0);   //back up away from stack
    setRoller(-60,500);
    wait(1300);
    setSwivel(70,-10);*/
    
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,15.3,0);//14.3
    setRoller(100,20000);
    wait(850);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,870,8.5);
    pickUp(1,850,10.8);
    wait(900);
    setRoller(0,0);

    Drive.drivePID.changePID(5, 0.3125, 1.25);
    setDrive(80,12.6,-33); //swerve to green cube next to tower
    wait(50);
    setRoller(100,7300);
    wait(1000);

    setDrive(80,-14,0.01);
    wait(700);

    Drive.drivePID.changePID(8, 0.5, 2);

    setDrive(80,-6.5,0);  //back up
    wait(700);
    //setRoller(0,0);

    setDrive(70,0,141.3);//-175
    wait(1700);

    setRoller(-100,200);
    setDrive(100,26.3,0);  //move to zone
    wait(500);
    //setRoller(100,1500);
    wait(1300);

    setSwivel(100, 1600);  //raise tower
    wait(1300);
    setSwivel(30, 2800);
    wait(1100);

    setDrive(70,-12,0);   //back up away from stack
    setRoller(-60,500);
    wait(1300);
    setSwivel(70,-10);

    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }

  if(autoOptions == 7){
    /*
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,13.5,0);
    setRoller(100,20000);
    wait(850);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,780,9.2);
    pickUp(1,780,10);
    wait(500);
    setRoller(0,0);

    Drive.drivePID.changePID(5, 0.3125, 1.25);
    setDrive(80,14,-30); //swerve to green cube next to tower
    wait(50);
    setRoller(100,5000);
    wait(1000);

    Drive.drivePID.changePID(8, 0.5, 2);
    setDrive(80,-4.5,0);  //back up
    wait(700);
    setRoller(0,0);

    setDrive(80,0,1); // turn to other cube next to tower
    wait(300);
    wait(300);
    
    setDrive(60,10.5,0);
    setRoller(100,7000);  //start roller
    wait(1200);

    setDrive(80,-12.5,0);
    wait(800);
    setRoller(0,0);

    setDrive(70,0,169);//-175
    wait(1700);

    setRoller(-100,900);
    setDrive(100,30,0);  //move to zone
    wait(500);
    setRoller(100,2300);
    wait(1000);

    setSwivel(100, 1900);  //raise tower
    wait(1300);
    setSwivel(30, 2800);
    wait(900);

    setDrive(70,-12,0);   //back up away from stack
    setRoller(-60,500);
    wait(1300);
    setSwivel(70,-10);*/
    //stop subsystem threads
    DriveControl.interrupt();
    ArmControl.interrupt();
    SwivelControl.interrupt();
    IntakeControl.interrupt();
  }
  
  if(autoOptions == 8){/*
    
    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,12.5,0);
    setRoller(100,20000);
    wait(1000);

    pickUp(3,800,8.9);  //stop and go forward multiple times to pick up cubes
    wait(200);
    setRoller(0,0);

    setDrive(80,12.5,35); //swerve to green cube next to tower
    wait(50);
    setRoller(100,5000);
    wait(1000);

    setDrive(80,-4.5,0);  //back up
    wait(700);
    setRoller(0,0);

    setDrive(80,0,-3); // turn to other cube next to tower
    wait(300);
    wait(300);
    
    setDrive(60,7.9,0);
    setRoller(100,8400);  //start roller
    wait(1200);

    setDrive(80,-14.5,0);
    wait(800);
    setRoller(0,0);*/

    //deploy rollers
    setSwivel(100, 1000);
    wait(500);
    setRoller(100,3000);
    setSwivel(100,-100);
    wait(500);

    //move to first cube
    setDrive(100,13.5,0);
    setRoller(100,20000);
    wait(850);

    pickUp(1,770,8.2);  //stop and go forward multiple times to pick up cubes
    pickUp(1,830,9.2);
    pickUp(1,780,10.3);
    wait(900);
    setRoller(0,0);

    Drive.drivePID.changePID(5, 0.3125, 1.25);
    setDrive(80,14,33); //swerve to green cube next to tower
    wait(300);
    setRoller(100,6300);
    wait(1200);

    setDrive(80,-14,1);
    wait(700);

    Drive.drivePID.changePID(8, 0.5, 2);

    setDrive(80,-8,0);  //back up
    wait(700);

    setDrive(70,0,-144.7);//-175
    wait(1700);

    setRoller(-100,300);
    setDrive(100,26.5,0);  //move to zone
    wait(500);
    //setRoller(100,1500);
    wait(1000);

    setSwivel(100, 1900);  //raise tower
    wait(1300);
    setSwivel(30, 2800);
    wait(1000);

    setDrive(70,-8,0);   //back up away from stack
    setRoller(-60,500);
    wait(1300);
    setSwivel(70,-10);

    setDrive(90,0,-281);   //turn to tower
    wait(2000);

    setDrive(60,-11,0);     //back up 
    wait(1000);

    setDrive(90,48.5,0);      //go to cube
    wait(600);
    setRoller(100,12000);
    wait(2200);

    setArm(90,1500);
    wait(1000);
    setRoller(-100,2300);
    wait(1300);

    setArm(70,600);
    wait(1000);

    setDrive(80,-14,-341);
    wait(1300);

    setArm(70,280);
    wait(1000);

    setDrive(80,14,0);
    setRoller(100,15000);
    wait(1300);

    pickUp(2);  //stop and go forward multiple times to pick up cubes
    wait(500);
    setRoller(0,0);

    setDrive(80,14,-318);
    wait(1200);

    setArm(100, 2200);
    wait(1400);
    setDrive(80,5.5,0);
    wait(700);
    setRoller(-100,2000);
    wait(1900);

    setDrive(60,-40,0);
    wait(500);
    setArm(70,280);
    wait(300);
    setArm(70,900);
    setRoller(70,1100);
    wait(2000);

    setDrive(100,0,-367);
    wait(1000);

    setArm(100,1200);
    wait(1000);
    setDrive(60,20,0);
    wait(700);
    setRoller(-100,2000);
    wait(1500);

    setDrive(60,-20.3,0);
    wait(700);
    setRoller(70,1000);
    setArm(70,300);
    wait(1300);

    setDrive(80,0,-459);
    setArm(80,1200);
    wait(1000);

    Drive.drivePID.changePID(5, 0.3125, 1.25);
    setDrive(100,14,0);
    wait(800);
    wait(1000);

    setRoller(-100,4000);
    wait(900);
    Drive.drivePID.changePID(8, 0.5, 2);
    setDrive(70,-7,0);
    wait(300);
    setArm(70,300);
    wait(400);

    setDrive(90,0,-363);
    wait(1200);
    
    setDrive(90,37,0);
    wait(1000);

    setDrive(100,12,-399);
    setRoller(100,50000);
    wait(500);
    setDrive(100,13,-359);
    wait(500);

    setDrive(100,50,0);
    wait(2000);

    setDrive(90,0,-409);
    wait(800);

    setDrive(100,8,0);
    wait(500);
    setRoller(-70,600);

    setSwivel(100, 1700);  //raise tower
    wait(1400);
    setDrive(10,3,0);
    setSwivel(30, 3000);
    wait(1050);

    setDrive(60,-11,0);   //back up away from stack
    setRoller(-60,500);
    wait(1000);
    setSwivel(70,-10);



    //setDrive(80,0,-445);
    //wait(1000);

    /*setDrive(80,0,-340);
    wait(1500);

    setDrive(100,50,0);
    setRoller(90,300000);
    wait(2800);

    setDrive(80,50,-280);
    wait(3500);

    setRoller(-100, 100000);
    wait(1000);

    setArm(100,700);
    wait(1000);*/

    wait(1000000);
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

  int test;
  int test2;
  int test3;

  Brain.Screen.clearScreen();
  Brain.resetTimer();

  //stop subsystems threads
  DriveControl.interrupt();
  ArmControl.interrupt();
  IntakeControl.interrupt();
  SwivelControl.interrupt();

  Drive.reset();

  while (1){
    test = Intake.trackTopCubes(color::orange);
    test2 = Intake.trackTopCubes(color::green);
    test3 = Intake.trackTopCubes(vex::color::purple);

    rgt = Joystick.Axis2.value()*0.95; 
    lft = Joystick.Axis3.value()*0.95;

    if(Joystick.ButtonDown.pressing()){
      Drive.move_drive(10, 10);
    }
    else{
      Drive.move_drive(lft, rgt);
    }
    
    Brain.Screen.printAt(20, 20, "x: %d", test);
    Brain.Screen.printAt(20, 40, "x: %d", test2);
    Brain.Screen.printAt(20, 60, "x: %d", test3);
    /*Brain.Screen.printAt(200, 140, "p2x: %f", followLine.p2.x);
    Brain.Screen.printAt(200, 160, "p2y: %f", followLine.p2.y);*/

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
      Intake.moveRoller(100);
    }
    else if(Joystick.ButtonR2.pressing()){
      Intake.moveRoller(-100);
    }
    else if(Joystick.ButtonX.pressing()){
      Intake.moveRoller(5);
    }
    else if(Joystick.ButtonB.pressing()){
      Intake.moveRoller(-5);
    }
    else{
      Intake.stopRoller(brakeType::hold);
    }

    //move swivel forward/ back when button is pressed
    if(Joystick.ButtonUp.pressing()){
      Intake.moveSwivel(95);
    }
    else if(Joystick.ButtonRight.pressing()){
      Intake.moveSwivel(30);
    }
    else if(Joystick.ButtonLeft.pressing()){
      Intake.moveSwivel(-80);
    }
    else if(Intake.getSwivelPos() < -10){
      Intake.stopSwivel(brakeType::hold);
    }
    else{
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
