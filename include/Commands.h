void setDrive(int power, float drivePos, float turnAngle = 0, bool isTurnTo = false, float rate = 1, bool slowdown = false){
  //- left + right

  //reset enc
  Drive.reset();

  Drive.isTurnTo = isTurnTo;

  //reset PID values
  Drive.drivePID.changePID(8, 0.5, 2);


  //change pid values if sharp swerving
  if(rate != 1 && !slowdown){
    Drive.drivePID.changePID(8*rate, 0.5*rate, 2*rate);
  }

  //change pid values if slowing down drive
  if(slowdown){
    Drive.drivePID.changePID(5*rate, 0.3125*rate, 1.25*rate);
  }
  
  //set robot start point
  Drive.initPos.x = Drive.sPos.x;
  Drive.initPos.y = Drive.sPos.y;

  Drive.DesPower = power;             //set power
  Drive.desiredAng = turnAngle;  //convert encoder to angle *1.1 *8.44
  Drive.initAng = Drive.getRoboAng(); //set initial direction facing
  Drive.desiredPos = drivePos;        //set drive pos
}

void waitDrive(){
  //wait for drive motors to slow down
  while((fabs(RgtDrive.velocity(percentUnits::pct)) > 2) || (fabs(LftDrive.velocity(percentUnits::pct)) > 2)){
    Brain.Screen.clearScreen();
  }
}

void setArm(int power, int pos){
  Arm.DesPower = power;       //set arm powr/ pos
  Arm.desiredPos = pos;
}

void setSwivel(int power, int pos){
  //set ramp angle
  Intake.swivelSpeed = power;
  Intake.swiveldesPos = pos;
}

void setRoller(int power, int pos, bool iscoast = false){
  Intake.rollerReset();   //reset robot
  Intake.rollerSpeed = power;   //set speed
  Intake.rollerRot = pos;   //set rotations
  if(power == 0){
    Intake.rollerState = false;   //dont start rollers if power 0
  }
  else{
    Intake.rollerState = true;
  }
  Intake.isCoasting = iscoast;    //set stop mode (hold or loose)
}

void pickUp(int times, int frequency = 800, float dist = 8.5, bool noStr = false){
  int i;

  //twitch drive forward
  for(i = 0; i < times; i++){
    if(noStr){
      setDrive(80, dist, 0.001);
    }
    else{
      setDrive(80, dist, 0);
    }
    wait(frequency);  //900 5.5secs 700 4 secs 800 
  }
}







