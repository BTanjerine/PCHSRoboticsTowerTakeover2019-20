using namespace vex;
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor RgtArm;
extern motor LftArm;
extern motor swivel;
extern motor RgtRoller;
extern motor LftRoller;
extern motor RgtDrive;
extern motor LftDrive;
extern motor MidDrive;
extern pot arm_pot;
extern gyro roboGyro;
extern encoder rgtEnc;
extern encoder lftEnc;
extern encoder bckEnc;
extern controller Controller1;
extern signature SIG_1;
extern signature SIG_2;
extern signature SIG_3;
extern signature SIG_4;
extern signature SIG_5;
extern signature SIG_6;
extern signature SIG_7;
extern vision Vision;
extern signature SIG1;
extern signature SIG2;
extern signature SIG3;
extern signature SIG4;
extern signature SIG5;
extern signature SIG6;
extern signature SIG7;
extern vision Vision2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );