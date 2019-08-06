using namespace vex;
using namespace std;

/***********************
 Intake Subsystem
***********************/
class intake{
  public:

  enum Cubecolr {GRN, ORG, PUR};

  int swiveldesPos;
  int swivelSpeed;

  bool rollerState;
  bool isCoasting;
  int rollerRot;
  int rollerSpeed;

  PID swivelPID = PID(0.15, 0.009375, 0.0375);
  
  //reset swivel variables
  void swivelReset(){
    swivel.resetRotation();
    swiveldesPos = 0;
    swivelSpeed = 0;
  }

  //reset roller values and reset
  void rollerReset(){
    rollerState = false;
    RgtRoller.resetRotation();
    LftRoller.resetRotation();
    rollerRot = 0;
    rollerSpeed = 0;
  }

  //reset robot variables
  void reset(){
    swivelReset();
    rollerReset();
  }

  int getSwivelPos(){
    return swivel.rotation(rotationUnits::raw);
  }

  int getRollerPos(){
    return (RgtRoller.rotation(rotationUnits::raw) + LftRoller.rotation(rotationUnits::raw))/2;
  }

  bool trackTopCubes(vex::color colr){
    bool output = false;

    if(colr == vex::color::green){
      Vision.takeSnapshot(SIG_1);

      if(roboEye.getObjectX(0, roboEye.OG) >= 0 && roboEye.getObjectX(0, roboEye.OG) < 11 && roboEye.isExisting()){output = true;}
      else{output = false;}
    }

    if(colr == vex::color::orange){
      Vision.takeSnapshot(SIG_2);

      if(roboEye.getObjectX(0, roboEye.OG) >= 0 && roboEye.getObjectX(0, roboEye.OG) < 11 && roboEye.isExisting()){output = true;}
      else{output = false;}
    }

    if(colr == vex::color::purple){
      Vision.takeSnapshot(SIG_3);

      if(roboEye.getObjectX(0, roboEye.OG) >= 0 && roboEye.getObjectX(0, roboEye.OG) < 11 && roboEye.isExisting()){output = true;}
      else{output = false;}
    }


    return output;

  }

  //move swivel
  void moveSwivel(int power){
    swivel.spin(directionType::fwd,power,velocityUnits::pct);
  }
  //move roller intake
  void moveRoller(int power){
    RgtRoller.spin(directionType::fwd, power, velocityUnits::pct);
    LftRoller.spin(directionType::fwd, power, velocityUnits::pct);
  }

  void stopRoller(brakeType brake){
    RgtRoller.stop(brake);
    LftRoller.stop(brake);
  }

  void stopSwivel(brakeType brake){
    swivel.stop(brake);
  }
};