using namespace vex;
using namespace std;

/***********************
 Intake Subsystem
***********************/
class intake{
  public:

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

  //move swivel
  void moveSwivel(int power){
    swivel.spin(directionType::fwd,power,velocityUnits::pct);
  }
  //move roller intake
  void moveRoller(int power){
    RgtRoller.spin(directionType::fwd, power, velocityUnits::pct);
    LftRoller.spin(directionType::fwd, power, velocityUnits::pct);
  }

  bool checkInstalled(){
    return !RgtRoller.installed() || !LftRoller.installed() || !swivel.installed();
  }

  void stopRoller(brakeType brake){
    RgtRoller.stop(brake);
    LftRoller.stop(brake);
  }

  void stopSwivel(brakeType brake){
    swivel.stop(brake);
  }
};