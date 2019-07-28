void setDrive(int power, float drivePos, float turnAngle, float rate = 1, bool slowdown = false){
  //- left + right

  //reset enc
  MidDrive.resetRotation();
  //reset PID values
  Drive.drivePID.changePID(8, 0.5, 2);

  if(rate != 1){
    Drive.drivePID.changePID(8/rate, 0.5/rate, 2/rate);
  }

  if(slowdown){
    Drive.drivePID.changePID(5/rate, 0.3125/rate, 1.25/rate);
  }

  Drive.DesPower = power;             //set power
  Drive.desiredAng = turnAngle*1.1;  //convert encoder to angle *8.44
  Drive.desiredPos = drivePos;        //set drive pos
}

void setArm(int power, int pos){
  Arm.DesPower = power;       //set arm powr/ pos
  Arm.desiredPos = pos;
}

void setSwivel(int power, int pos){
  Intake.swivelSpeed = power;
  Intake.swiveldesPos = pos;
}

void setRoller(int power, int pos){
  Intake.rollerReset();
  Intake.rollerSpeed = power;
  Intake.rollerRot = pos;
  Intake.rollerState = true;
}

void pickUp(int times, int frequency = 800, float dist = 8.5){
  int i;
  for(i = 0; i < times; i++){
    setDrive(90, dist, 0);
    wait(frequency);  //900 5.5secs 700 4 secs 800 
  }
}


void setDriveNew(int power, float drivePos, float turnAngle = 0, float rate = 1, bool slowdown = false){
  //- left + right

  //reset enc
  Drive.reset();

  //reset PID values
  Drive.drivePID.changePID(8, 0.5, 2);

  if(rate != 1){
    Drive.drivePID.changePID(8/rate, 0.5/rate, 2/rate);
  }

  if(slowdown){
    Drive.drivePID.changePID(5/rate, 0.3125/rate, 1.25/rate);
  }

  Drive.DesPower = power;             //set power9
  Drive.desiredAng = turnAngle*1.1;  //convert encoder to angle *1.1 *8.44
  Drive.initAng = Drive.sPos.Ang;
  Drive.desiredPos = drivePos;        //set drive pos
}




