void setDrive(int power, float drivePos, float turnAngle = 0, bool isTurnTo = false, float rate = 1, bool slowdown = false){
  //- left + right

  //reset enc
  Drive.reset();

  Drive.isTurnTo = isTurnTo;

  //reset PID values
  Drive.drivePID.changePID(8, 0.5, 2);

  if(rate != 1){
    Drive.drivePID.changePID(8*rate, 0.5*rate, 2*rate);
  }

  if(slowdown){
    Drive.drivePID.changePID(5*rate, 0.3125*rate, 1.25*rate);
  }

  Drive.initPos.x = Drive.sPos.x;
  Drive.initPos.y = Drive.sPos.y;

  Drive.DesPower = power;             //set power9
  Drive.desiredAng = turnAngle;  //convert encoder to angle *1.1 *8.44
  Drive.initAng = Drive.getRoboAng();
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

void setRoller(int power, int pos, bool iscoast = false){
  Intake.rollerReset();
  Intake.rollerSpeed = power;
  Intake.rollerRot = pos;
  Intake.rollerState = true;
  Intake.isCoasting = iscoast;
}

void pickUp(int times, int frequency = 800, float dist = 8.5){
  int i;
  for(i = 0; i < times; i++){
    setDrive(90, dist, 0);
    wait(frequency);  //900 5.5secs 700 4 secs 800 
  }
}







