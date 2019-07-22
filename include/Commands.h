void setDrive(int power, float drivePos, float turnAngle){
  //- left + right
  MidDrive.resetRotation();
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



