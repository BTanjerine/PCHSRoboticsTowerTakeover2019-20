void setDrive(int power, float drivePos, float turnAngle = (Drive.isEncoderTurn==true)?radToDeg(Drive.sPos.Ang):Drive.getRoboAng(),float rate = 1, bool slowdown = false){
  //- left + right

  //reset enc
  Drive.reset();

  //reset PID values
  Drive.drivePID.changePID(8, 0.5, 2);


  //change pid values if sharp swerving
  if(rate != 1 && !slowdown){
    if(drivePos != 0){
      Drive.drivePID.changePID(8*rate, 0.5*rate, 2*rate);
    }
    else if(turnAngle != (Drive.isEncoderTurn==true)?radToDeg(Drive.sPos.Ang):Drive.getRoboAng()){
      Drive.turnPID.changePID(1.45*rate, 0.090625*rate, 0.3625*rate);
    }
    else{
      Drive.drivePID.changePID(8*rate, 0.5*rate, 2*rate);
    }
  }

  //change pid values if slowing down drive
  if(slowdown){
    Drive.drivePID.changePID(5*rate, 0.3125*rate, 1.25*rate);
  }

  Drive.DesPower = power;             //set power
  Drive.desiredAng = turnAngle;  //set angle to face or sweep to
  Drive.initAng = radToDeg(Drive.sPos.Ang); //set initial direction facing
  Drive.initGyroAng = Drive.getRoboAng();
  Drive.desiredPos = drivePos;        //set drive pos
}

void waitDrive(int deadzone = 2){
  //wait for drive motors to slow down
  while((fabs(RgtDrive.velocity(percentUnits::pct)) > deadzone) || (fabs(LftDrive.velocity(percentUnits::pct)) > deadzone)){
    Brain.Screen.clearScreen();
    wait(10);
  }
}

void waitDriveNew(int deadzone = 2, int counterDeadZone = 6){
  int counter = 0;
  while(1){
    if((fabs(RgtDrive.velocity(percentUnits::pct)) < deadzone) && (fabs(LftDrive.velocity(percentUnits::pct)) < deadzone)){
      counter++;  //start counting how long the drive power is set to 0
    }
    else{counter = 0;}
    if(counter > counterDeadZone){break;}
    wait(10);
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

void startCam(bool camState, bool colrMode){
  Drive.camState = camState;
  Drive.colorMode = colrMode;
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
      setDrive(80, dist);
    }
    else{
      setDrive(80, dist);
    }
    wait(frequency);  //900 5.5secs 700 4 secs 800
  }
}







