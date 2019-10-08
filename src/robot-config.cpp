#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

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
signature SIG_1 = signature (1, -3019, -2683, -2851, 9577, 10327, 9952, 11, 0);
signature SIG_2 = signature (2, 4117, 4969, 4544, -479, -117, -298, 5.3, 0);
signature SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision = vision (PORT10, 50, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);

/*vex-vision-config:end*/
/*vex-vision-config:begin*/
signature SIG1 = signature (1, -2795, -2333, -2564, 7549, 9203, 8376, 7.4, 0);
signature SIG2 = signature (2, 4059, 6997, 5528, -713, -179, -446, 1.9, 0);
signature SIG3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature SIG7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision2 = vision (PORT1, 50, SIG1, SIG2, SIG3, SIG4, SIG5, SIG6, SIG7);
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