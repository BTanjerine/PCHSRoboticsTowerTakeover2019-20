using namespace vex;
using namespace std;

/***********************
 Arm Subsystem
***********************/
class arm{
  public:
  //PID constant Values
  PID armPID = PID(0.14, 0.00875, 0.035);
  
  //desired arm position for auto
  int desiredPos;
  //desird arm power
  int DesPower;
  
  //clear arm values
  void reset(){
    //reset desired positions
    desiredPos = 330;     
    DesPower = 0;
  }    
  
  int getArmPos(){
    return arm_pot.value(analogUnits::mV);
  }
  
  //set arm power
  void move_arm(int power){
    RgtArm.spin(directionType::fwd,power,velocityUnits::pct);
    LftArm.spin(directionType::fwd,power,velocityUnits::pct);
  }

  void Stop(brakeType brake){
    RgtArm.stop(brake);
    LftArm.stop(brake);
  }
};


