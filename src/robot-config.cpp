#include "robot-config.h"

using namespace vex;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RgtArm = motor(PORT14, ratio36_1, false);
motor LftArm = motor(PORT15, ratio36_1, true);
motor swivel = motor(PORT16, ratio36_1, false);
motor RgtRoller = motor(PORT19, ratio18_1, false);
motor LftRoller = motor(PORT11, ratio18_1, true);
motor RgtDrive = motor(PORT12, ratio18_1, true);
motor LftDrive = motor(PORT18, ratio18_1, false);
motor MidDrive = motor(PORT13, ratio18_1, false);
pot arm_pot = pot(Brain.ThreeWirePort.A);
gyro roboGyro = gyro(Brain.ThreeWirePort.B);
encoder rgtEnc = encoder(Brain.ThreeWirePort.C);
encoder lftEnc = encoder(Brain.ThreeWirePort.E);
sonar bckSon = sonar(Brain.ThreeWirePort.G);
controller Controller1 = controller(primary);
// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}