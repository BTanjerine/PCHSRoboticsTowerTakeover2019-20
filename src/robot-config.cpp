#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RgtArm = motor(PORT14, ratio36_1, false);
motor LftArm = motor(PORT15, ratio36_1, true);
motor swivel = motor(PORT6, ratio36_1, false);
motor RgtRoller = motor(PORT19, ratio18_1, false);
motor LftRoller = motor(PORT11, ratio18_1, true);
motor RgtDrive = motor(PORT12, ratio18_1, true);
motor LftDrive = motor(PORT18, ratio18_1, false);
motor MidDrive = motor(PORT16, ratio18_1, false);
pot arm_pot = pot(Brain.ThreeWirePort.A);
gyro roboGyro = gyro(Brain.ThreeWirePort.B);
encoder rgtEnc = encoder(Brain.ThreeWirePort.C);
encoder lftEnc = encoder(Brain.ThreeWirePort.E);
encoder bckEnc = encoder(Brain.ThreeWirePort.G);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
signature Vision__SIG_1 = signature (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision = vision (PORT10, 50, Vision__SIG_1, Vision__SIG_2, Vision__SIG_3, Vision__SIG_4, Vision__SIG_5, Vision__SIG_6, Vision__SIG_7);
/*vex-vision-config:end*/
/*vex-vision-config:begin*/
signature Vision2__SIG_1 = signature (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision2__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision2__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision2__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision2__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision2__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision2__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision2 = vision (PORT1, 50, Vision2__SIG_1, Vision2__SIG_2, Vision2__SIG_3, Vision2__SIG_4, Vision2__SIG_5, Vision2__SIG_6, Vision2__SIG_7);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}